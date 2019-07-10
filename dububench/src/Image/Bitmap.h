#pragma once

#include "Texture2D.h"

class CBitmap {
public:
	CBitmap();
	~CBitmap();

	bool Init(int aWidth, int aHeight);
	bool Save(const char* aFilepath);

	void SetTexture(const CTexture2D& aTexture);

	CTexture2D& GetTexture() {
		return myTexture;
	}

private:
	__int32 myWidth;
	__int32 myHeight;
	CTexture2D myTexture;
};
