#pragma once

#include "../Utils/Vec.h"
#include "Pixel.h"

#include <string>

class CTexture2D {
public:
	CTexture2D();
	~CTexture2D();

	CTexture2D(const CTexture2D& aTexture2D) {
		this->operator=(aTexture2D);
	}
	__forceinline void operator=(const CTexture2D& aTexture2D) {
		if (myWidth == aTexture2D.myWidth && myHeight == aTexture2D.myHeight) {
			int size = sizeof(SPixel) * myWidth * myHeight;
			std::memcpy(myData, aTexture2D.myData, size);
		}
	}

	bool Init(int aWidth, int aHeight);
	SPixel const* GetData() const {
		return myData;
	}

	__forceinline void SetPixelData(int aIndex, const vec3& aColor) {
		myData[aIndex].r =
			(unsigned __int8)((aColor.x < 0.f ? 0.f : aColor.x > 1.f ? 1.f : aColor.x) * 255.f);
		myData[aIndex].g =
			(unsigned __int8)((aColor.y < 0.f ? 0.f : aColor.y > 1.f ? 1.f : aColor.y) * 255.f);
		myData[aIndex].b =
			(unsigned __int8)((aColor.z < 0.f ? 0.f : aColor.z > 1.f ? 1.f : aColor.z) * 255.f);
	}

	__forceinline int GetWidth() const {
		return myWidth;
	}
	__forceinline int GetHeight() const {
		return myHeight;
	}

	const vec3 SamplePoint(const vec2& aUV) const;
	const vec3 SampleLinear(const vec2& aUV) const;

private:
	int myWidth = 0;
	int myHeight = 0;

	SPixel* myData = nullptr;
};
