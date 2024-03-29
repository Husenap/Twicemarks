#include "Image/Bitmap.h"
#include "Image/Texture2D.h"
#include "Render/RenderPipeline.h"

#include <chrono>
#include <iomanip>
#include <iostream>

int main() {
	srand(static_cast<unsigned int>(time(0)));
	// system("pause");
	auto t1 = std::chrono::high_resolution_clock::now();

	CBitmap bitmap;

	int w = 1920;
	int h = 1080;

	if (!bitmap.Init(w, h)) return 1;

	CTexture2D& backbuffer = bitmap.GetTexture();

	CRenderPipeline renderPipeline;
	if (!renderPipeline.Init(w, h)) return 1;

	renderPipeline.Render(backbuffer);

	if (!bitmap.Save("image.bmp")) return 1;

	auto t2 = std::chrono::high_resolution_clock::now();
	std::cout << "Elapsed Time: " << std::setprecision(9)
			  << static_cast<std::chrono::duration<float>>(t2 - t1).count() * 1000.0 << "ms.\n"
			  << std::endl;

	// system("pause");
	return 0;
}
