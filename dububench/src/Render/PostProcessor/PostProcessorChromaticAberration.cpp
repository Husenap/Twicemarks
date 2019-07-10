#include "PostProcessorChromaticAberration.h"

CPostProcessorChromaticAberration::CPostProcessorChromaticAberration() {
}

CPostProcessorChromaticAberration::~CPostProcessorChromaticAberration() {
}

vec4 CPostProcessorChromaticAberration::Render(const vec2& aUV, const CTexture2D& aReadTexture) {
	const static vec2 rOffset = {0.142f, 0.0948f};
	const static vec2 gOffset = {0.0943f, 0.05829f};
	const static vec2 bOffset = {0.042f, 0.0624f};

	vec3 color = {aReadTexture.SampleLinear({aUV.x - rOffset.x * 0.015f, aUV.y - rOffset.y * 0.015f}).r,
				  aReadTexture.SampleLinear({aUV.x + gOffset.x * 0.015f, aUV.y - gOffset.y * 0.015f}).g,
				  aReadTexture.SampleLinear({aUV.x - bOffset.x * 0.015f, aUV.y + bOffset.y * 0.015f}).b};

	return {color.r, color.g, color.b, 1.f};
}
