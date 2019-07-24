#include "MainWindow.h"

#pragma comment(lib, "d2d1")

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
			const D2D1_COLOR_F color = D2D1::ColorF(1.0f, 1.0f, 0.0f);
			hr = mRenderTarget->CreateSolidColorBrush(color, &mBrush);

			if (SUCCEEDED(hr)) {
				CalculateLayout();
			}
		}
	}
	return hr;
}

void MainWindow::DiscardGraphicsResources() {
	SafeRelease(mRenderTarget);
	SafeRelease(mBrush);
}

void MainWindow::OnPaint() {
	HRESULT hr = CreateGraphicsResources();
	if (SUCCEEDED(hr)) {
		PAINTSTRUCT ps;
		BeginPaint(mHwnd, &ps);

		mRenderTarget->BeginDraw();

		mRenderTarget->Clear(D2D1::ColorF(0x0099ff));
		mRenderTarget->FillEllipse(mEllipse, mBrush);

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
