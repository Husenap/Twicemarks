#include <iostream>

#include "window/MainWindow.h"

int main() {
	MainWindow window;

	if (!window.Create("Momobrot", WS_OVERLAPPEDWINDOW, 0, 0, 0, 500, 500)) {
		std::cout << "Failed to create window" << std::endl;
		return 0;
	}

	ShowWindow(window.Window(), SW_SHOW);

	MSG msg = {};

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
