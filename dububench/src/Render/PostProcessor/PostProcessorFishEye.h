#pragma once

#include "../../Image/Texture2D.h"
#include "../../Utils/Shadermath.h"

class CPostProcessorFishEye {
public:
	CPostProcessorFishEye();
	~CPostProcessorFishEye();

	vec4 Render(const vec2& aUV, const CTexture2D& aReadTexture);
};
