#include "Texture2D.h"

#include <iostream>

#include "../Utils/Shadermath.h"

CTexture2D::CTexture2D() {
	myWidth = myHeight = 0;
	myData = nullptr;
}

CTexture2D::~CTexture2D() {
	delete[] myData;
	myData = nullptr;
}

bool CTexture2D::Init(int aWidth, int aHeight) {
	myWidth = aWidth;
	myHeight = aHeight;
	myData = new SPixel[myWidth * myHeight];

	if (myData == nullptr) {
		std::cout << "Error: Failed to allocate CTexture2D::myData" << std::endl;
		return false;
	}

	memset(myData, 0, sizeof(SPixel) * myWidth * myHeight);

	return true;
}

const vec3 CTexture2D::SamplePoint(const vec2& aUV) const {
	vec2 uv = Saturate(aUV);
	int x = static_cast<int>((myWidth)*uv.x) % myWidth;
	int y = static_cast<int>((myHeight)*uv.y) % myHeight;
	const SPixel& pixel = myData[x + y * myWidth];
	return vec3((float)pixel.r, (float)pixel.g, (float)pixel.b) / 255.f;
}

const vec3 CTexture2D::SampleLinear(const vec2& aUV) const {
	const vec2 res = vec2((float)myWidth, (float)myHeight);
	vec2 uv = Mod(aUV, vec2(1.f));

	vec2 p = uv * res;
	vec2 f = p - Floor(p);

	const int x1 = static_cast<int>((myWidth)*uv.x) % myWidth;
	const int y1 = static_cast<int>((myHeight)*uv.y) % myHeight;
	const int x2 = (static_cast<int>((myWidth)*uv.x) + 1) % myWidth;
	const int y2 = (static_cast<int>((myHeight)*uv.y) + 1) % myHeight;
	const SPixel& pixel1 = myData[x1 + y1 * myWidth];
	const SPixel& pixel2 = myData[x2 + y1 * myWidth];
	const SPixel& pixel3 = myData[x1 + y2 * myWidth];
	const SPixel& pixel4 = myData[x2 + y2 * myWidth];

	return (vec3((float)pixel4.r, (float)pixel4.g, (float)pixel4.b) / 255.f * f.x * f.y +
			vec3((float)pixel3.r, (float)pixel3.g, (float)pixel3.b) / 255.f * (1.f - f.x) * f.y +
			vec3((float)pixel2.r, (float)pixel2.g, (float)pixel2.b) / 255.f * f.x * (1.f - f.y) +
			vec3((float)pixel1.r, (float)pixel1.g, (float)pixel1.b) / 255.f * (1.f - f.x) * (1.f - f.y));
}
