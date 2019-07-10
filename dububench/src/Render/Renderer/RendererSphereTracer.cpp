#include "RendererSphereTracer.h"

CRendererSphereTracer::CRendererSphereTracer() {
}

CRendererSphereTracer::~CRendererSphereTracer() {
}

bool CRendererSphereTracer::Init(const vec2& aResolution) {
	myResolution = aResolution;

	myCommandList.AddCommand(std::make_shared<omni::Mod1>(2, 10.f));
	myCommandList.AddCommand(std::make_shared<omni::Mod1>(0, 10.f));
	myCommandList.AddCommand(std::make_shared<omni::Mod1>(1, 20.f));
	myCommandList.AddCommand(std::make_shared<omni::OpUnionColumns>(
		std::make_shared<omni::OpUnionColumns>(
			std::make_shared<omni::FSphere>(vec3(-2.5f, 0.f, 0.f), 1.5f, RED),
			std::make_shared<omni::FBoxRound>(vec3zero, vec3(3.f, 0.5f, 1.f), 0.15f, BLUE),
			0.2f,
			4.f),
		std::make_shared<omni::FSphere>(vec3(2.5f, 0.f, 0.f), 1.5f, GREEN),
		0.2f,
		4.f));

	return true;
}

vec4 CRendererSphereTracer::Render(const vec2& aUV, const CTexture2D& aReadTexture) {
	aReadTexture;

	vec2 uv = aUV;
	uv.y = 1.f - uv.y;
	uv = 2.f * uv - 1.f;
	uv.x *= myResolution.x / myResolution.y;

	vec3 pos = {0.f, 10.0f, -8.f};
	vec3 dir = normalize(g_forward * g_focalLength + g_right * uv.x + g_up * uv.y);

	float depth;
	int numIterations;
	int material;

	Raymarch(pos, dir, numIterations, depth, material);

	if (depth >= g_far) {
		return {0.f, 0.f, 0.f, 1.f};
	}

	vec3 p = pos + dir * depth;
	vec3 n = CalculateNormal(p);

	float f = Smoothstep(0.0f, 1.f, dot(n, g_up)) * 0.9f + 0.1f;

	vec4 col(f, f, f, 1.0f);

	if (material == RED) {
		col *= vec4(1.f, 0.5f, 0.5f, 1.f);
	} else if (material == BLUE) {
		col *= vec4(0.5f, 0.5f, 1.0f, 1.f);
	} else {
		col *= vec4(0.5f, 1.0f, 0.5f, 1.f);
	}

	float fog = 1.f - (depth / g_far);

	col *= fog;

	/*
	float cost = (numIterations) / (float) g_steps;
	if (cost < 0.5f)
	{
		col = Lerp(
			vec4(0.f, 0.f, 1.f, 1.f),
			vec4(0.f, 1.f, 0.f, 1.f),
			cost*2.f
		);
	}
	else
	{
		col = Lerp(
			vec4(0.f, 1.f, 0.f, 1.f),
			vec4(1.f, 0.f, 0.f, 1.f),
			(cost-0.5f)*2.f
		);
	}
	*/

	return col;
}

vec3 CRendererSphereTracer::CalculateNormal(const vec3& aPosition) {
	const static vec2 h(1e-4f, 0.f);

	return normalize(vec3(SceneHitInfo(aPosition + vec3(h.x, h.y, h.y)).myDepth -
							  SceneHitInfo(aPosition - vec3(h.x, h.y, h.y)).myDepth,
						  SceneHitInfo(aPosition + vec3(h.y, h.x, h.y)).myDepth -
							  SceneHitInfo(aPosition - vec3(h.y, h.x, h.y)).myDepth,
						  SceneHitInfo(aPosition + vec3(h.y, h.y, h.x)).myDepth -
							  SceneHitInfo(aPosition - vec3(h.y, h.y, h.x)).myDepth));
}

void CRendererSphereTracer::Raymarch(
	const vec3& aPosition, const vec3& aDirection, int& aIteration, float& aTime, int& aMaterial) {
	aTime = 0.f;

	vec3 p = aPosition;
	omni::HitInfo hitInfo = {FLT_MAX, 0};

	for (int i = 0; i < g_steps; ++i) {
		p = aPosition + aDirection * aTime;

		hitInfo = SceneHitInfo(p);

		if (hitInfo.myDepth < g_epsilon) {
			aIteration = i;
			aMaterial = hitInfo.myMaterialID;
			return;
		}

		aTime += hitInfo.myDepth;

		if (aTime >= g_far) {
			aIteration = i;
			aMaterial = hitInfo.myMaterialID;
			return;
		}
	}

	aIteration = g_steps;
	aMaterial = hitInfo.myMaterialID;
}

omni::HitInfo CRendererSphereTracer::SceneHitInfo(const vec3& pos) {
	return myCommandList.ApplyCommands(pos);
}
