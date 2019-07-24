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
	MainWindow()
		: mFactory(NULL)
		, mRenderTarget(NULL)
		, mBrush(NULL)
		, mEllipse() {
	}

	virtual LPCSTR ClassName() const override {
		return "Main Window Class";
	}

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

private:
	ID2D1Factory* mFactory;
	ID2D1HwndRenderTarget* mRenderTarget;
	ID2D1SolidColorBrush* mBrush;
	D2D1_ELLIPSE mEllipse;

	void CalculateLayout();
	HRESULT CreateGraphicsResources();
	void DiscardGraphicsResources();
	void OnPaint();
	void Resize();
};