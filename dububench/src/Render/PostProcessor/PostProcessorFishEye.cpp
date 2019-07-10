#include "PostProcessorFishEye.h"

CPostProcessorFishEye::CPostProcessorFishEye() {
}

CPostProcessorFishEye::~CPostProcessorFishEye() {
}

vec4 CPostProcessorFishEye::Render(const vec2& aUV, const CTexture2D& aReadTexture) {
	vec2 uv = aUV;

	uv = uv * 2.f - 1.f;
	uv *= (length(uv) * 0.4f + 0.6f) / Sqrt(2.f);
	uv = (uv + 1.f) * 0.5f;

	vec3 color = aReadTexture.SampleLinear(uv);
	return {color.r, color.g, color.b, 1.f};
}