#include "PostProcessorRGBFlip.h"

CPostProcessorRGBFlip::CPostProcessorRGBFlip() {
}

CPostProcessorRGBFlip::~CPostProcessorRGBFlip() {
}

vec4 CPostProcessorRGBFlip::Render(const vec2& aUV, const CTexture2D& aReadTexture) {
	vec3 color = aReadTexture.SamplePoint(aUV);
	return {color.b, color.g, color.r, 1.f};
}
