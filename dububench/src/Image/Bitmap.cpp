#include "Bitmap.h"

#include <iostream>

CBitmap::CBitmap() {
}

CBitmap::~CBitmap() {
}

bool CBitmap::Init(int aWidth, int aHeight) {
	myWidth = aWidth;
	myHeight = aHeight;
	if (!myTexture.Init(aWidth, aHeight)) {
		std::cout << "ERROR: Failed to init CBitmap::myTexture" << std::endl;
		return false;
	}

	return true;
}

bool CBitmap::Save(const char* aFilepath) {
	unsigned char bmpfileheader[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
	unsigned char bmpinfoheader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
	unsigned char bmppad[3] = {0, 0, 0};

	__int32 fileSize = 54 + 3 * myWidth * myHeight;

	bmpfileheader[2] = (unsigned char)(fileSize);
	bmpfileheader[3] = (unsigned char)(fileSize >> 8);
	bmpfileheader[4] = (unsigned char)(fileSize >> 16);
	bmpfileheader[5] = (unsigned char)(fileSize >> 24);

	bmpinfoheader[4] = (unsigned char)(myWidth);
	bmpinfoheader[5] = (unsigned char)(myWidth >> 8);
	bmpinfoheader[6] = (unsigned char)(myWidth >> 16);
	bmpinfoheader[7] = (unsigned char)(myWidth >> 24);
	bmpinfoheader[8] = (unsigned char)(myHeight);
	bmpinfoheader[9] = (unsigned char)(myHeight >> 8);
	bmpinfoheader[10] = (unsigned char)(myHeight >> 16);
	bmpinfoheader[11] = (unsigned char)(myHeight >> 24);

	FILE* fp = NULL;
	fopen_s(&fp, aFilepath, "wb");

	if (fp == NULL) {
		std::cout << "Error: Failed to open file!" << std::endl;
		return false;
	}

	fwrite(bmpfileheader, 1, 14, fp);
	fwrite(bmpinfoheader, 1, 40, fp);
	for (int i = 0; i < myHeight; ++i) {
		fwrite(myTexture.GetData() + (myWidth * (myHeight - i - 1)), 3, myWidth, fp);
		fwrite(bmppad, 1, (4 - (myWidth * 3) % 4) % 4, fp);
	}

	fclose(fp);

	return true;
}

void CBitmap::SetTexture(const CTexture2D& aTexture) {
	myTexture = aTexture;
}
