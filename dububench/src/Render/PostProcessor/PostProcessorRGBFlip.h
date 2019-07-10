#pragma once

#include "../../Image/Texture2D.h"
#include "../../Utils/Shadermath.h"

class CPostProcessorRGBFlip {
public:
	CPostProcessorRGBFlip();
	~CPostProcessorRGBFlip();

	vec4 Render(const vec2& aUV, const CTexture2D& aReadTexture);

private:
};
