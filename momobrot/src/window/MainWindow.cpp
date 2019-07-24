#include "MainWindow.h"

#include <iostream>
#include <vector>

#pragma comment(lib, "d2d1")

 MainWindow::MainWindow()
	: mFactory(nullptr)
	, mRenderTarget(nullptr)
	, mBitmap(nullptr)
	, mBrush(nullptr)
	, mStroke(nullptr)
	, mEllipse() {
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_CREATE: {
			if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mFactory))) {
				MessageBox(mHwnd, "ERROR!", "Failed to create factory", MB_OK);
				return -1;
			}
			return 0;
		}

		case WM_DESTROY: {
			DiscardGraphicsResources();
			SafeRelease(mFactory);
			PostQuitMessage(0);
			return 0;
		}

		case WM_PAINT: {
			OnPaint();
			return 0;
		}

		case WM_SIZE: {
			Resize();
			return 0;
		}
	}

	return DefWindowProc(mHwnd, uMsg, wParam, lParam);
}

void MainWindow::CalculateLayout() {
	if (mRenderTarget != NULL) {
		D2D1_SIZE_F size = mRenderTarget->GetSize();

		const float x = size.width / 2.f;
		const float y = size.height / 2.f;
		const float radius = min(x, y);

		mEllipse = D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius);
	}
}

HRESULT MainWindow::CreateGraphicsResources() {
	HRESULT hr = S_OK;
	if (mRenderTarget == NULL) {
		RECT rc;
		GetClientRect(mHwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);
		hr = mFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(mHwnd, size), &mRenderTarget);

		if (SUCCEEDED(hr)) {
			hr = mRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 1.0f, 0.0f), &mBrush);
			hr = mRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f), &mStroke);

			mBitmapSize = D2D1_SIZE_U{1920, 1080};
			D2D1_BITMAP_PROPERTIES bitmapProps = {};
			bitmapProps.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
			bitmapProps.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;
			hr = mRenderTarget->CreateBitmap(mBitmapSize, bitmapProps, &mBitmap);

			std::vector<unsigned char> bitmapData;
			bitmapData.resize(mBitmapSize.width * mBitmapSize.height * 4);
			for (int y = 0; y < mBitmapSize.height; ++y) {
				for (int x = 0; x < mBitmapSize.width; ++x) {
					int index = x*4 + y * mBitmapSize.width*4;

					double posX = (double(x) - 0.5*double( mBitmapSize.width)) / double(mBitmapSize.height);
					double posY = (double(y) - 0.5*double(mBitmapSize.height)) / double(mBitmapSize.height);

					double zoom = 0.1;
					double cx = posX * zoom * 3.;
					double cy = posY * zoom * 3.;
					cx += -.69955;
					cy += .37999;

					double zx = cx;
					double zy = cy;

					const double maxIter = 512.;
					double iter = 0.;
					for (; iter < maxIter; ++iter) {
						double qx = zx * zx - zy * zy + cx;
						double qy = zy * zx + zx * zy + cy;
						if (qx * qx + qy * qy > 4.0) break;
						zx = qx;
						zy = qy;
					}

					bitmapData[index + 2] = int(std::cos(iter)*256.);
					bitmapData[index + 1] = int(std::sin(iter)*256.);
					bitmapData[index + 0] = int((iter/maxIter)*256.);
					bitmapData[index + 3] = 0;
				}
			}

			D2D1_RECT_U destRect{0, 0, mBitmapSize.width, mBitmapSize.height};

			mBitmap->CopyFromMemory(&destRect, bitmapData.data(), mBitmapSize.width * 4);

			if (SUCCEEDED(hr)) {
				CalculateLayout();
			} else {
				std::cout << "Failed to create bitmap!"
						  << " " << hr << std::endl;
			}
		}
	}
	return hr;
}

void MainWindow::DiscardGraphicsResources() {
	SafeRelease(mBitmap);
	SafeRelease(mStroke);
	SafeRelease(mBrush);
	SafeRelease(mRenderTarget);
}

void MainWindow::OnPaint() {
	HRESULT hr = CreateGraphicsResources();
	if (SUCCEEDED(hr)) {
		PAINTSTRUCT ps;
		BeginPaint(mHwnd, &ps);

		mRenderTarget->BeginDraw();

		RenderScene();

		hr = mRenderTarget->EndDraw();
		if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET) {
			DiscardGraphicsResources();
		}

		EndPaint(mHwnd, &ps);
	}
}

void MainWindow::Resize() {
	if (mRenderTarget != NULL) {
		RECT rc;
		GetClientRect(mHwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		mRenderTarget->Resize(size);
		CalculateLayout();
		InvalidateRect(mHwnd, NULL, FALSE);
	}
}

void MainWindow::DrawClockHand(float handLength, float angle, float strokeWidth) {
	mRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(angle, mEllipse.point));

	D2D_POINT_2F endPoint =
		D2D1::Point2F(mEllipse.point.x, mEllipse.point.y - (mEllipse.radiusY * handLength));

	mRenderTarget->DrawLine(mEllipse.point, endPoint, mStroke, strokeWidth);
}

void MainWindow::RenderScene() {
	mRenderTarget->Clear(D2D1::ColorF(0x0099ff));
	mRenderTarget->FillEllipse(mEllipse, mBrush);
	mRenderTarget->DrawEllipse(mEllipse, mStroke, 5.0f);

	SYSTEMTIME time;
	GetLocalTime(&time);

	const float hourAngle = (360.f / 12.f) * (time.wHour) + (time.wMinute * 0.5f);
	const float minuteAngle = (360.f / 60.f) * (time.wMinute);

	DrawClockHand(0.6f, hourAngle, 6.0f);
	DrawClockHand(0.8f, minuteAngle, 4.0f);

	mRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

	D2D1_RECT_F bitmapRect;
	bitmapRect.left = 0;
	bitmapRect.top = 0;
	bitmapRect.right = mRenderTarget->GetSize().width;
	bitmapRect.bottom = mRenderTarget->GetSize().height;
	mRenderTarget->DrawBitmap(mBitmap, bitmapRect);
}
