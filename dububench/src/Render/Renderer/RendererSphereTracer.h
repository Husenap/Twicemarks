#pragma once

#include "../../Image/Texture2D.h"
#include "../../Utils/Shadermath.h"

#include "../SDF/RenderCommands.h"

class CRendererSphereTracer {
public:
	CRendererSphereTracer();
	~CRendererSphereTracer();

	bool Init(const vec2& aResolution);

	vec4 Render(const vec2& aUV, const CTexture2D& aReadTexture);

private:
	enum EColors { RED, BLUE, GREEN };

	vec3 CalculateNormal(const vec3& aPosition);
	void Raymarch(
		const vec3& aPosition, const vec3& aDirection, int& aIteration, float& aTime, int& aMaterial);
	omni::HitInfo SceneHitInfo(const vec3& pos);

	omni::CommandList myCommandList;

	vec2 myResolution;

	const vec3 g_forward = vec3(0.f, 0.f, 1.f);
	const vec3 g_right = vec3(1.f, 0.f, 0.f);
	const vec3 g_up = vec3(0.f, 1.f, 0.f);
	const float g_focalLength = 0.5f;  // Distance between the eye and the image plane
	const int g_steps = 256;
	const float g_epsilon = 1e-3f;
	const float g_far = 250.f;
};
