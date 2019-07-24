#pragma once

#include "BaseWindow.h"

#include <d2d1.h>

template <class T>
void SafeRelease(T*& ppT) {
	if (ppT) {
		ppT->Release();
		ppT = NULL;
	}
}

class MainWindow : public BaseWindow<MainWindow> {
public:
	MainWindow();

	virtual LPCSTR ClassName() const override {
		return "Main Window Class";
	}

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

private:
	ID2D1Factory* mFactory;
	ID2D1HwndRenderTarget* mRenderTarget;
	ID2D1Bitmap* mBitmap;

	D2D1_SIZE_U mBitmapSize;

	void CalculateLayout();
	HRESULT CreateGraphicsResources();
	void DiscardGraphicsResources();
	void OnPaint();
	void Resize();

	void RenderScene();
};