#pragma once

#include "../Image/Texture2D.h"

#include <tuple>
#include <variant>
#include <vector>

#include "PostProcessor/PostProcessorChromaticAberration.h"
#include "PostProcessor/PostProcessorFishEye.h"
#include "PostProcessor/PostProcessorRGBFlip.h"
#include "Renderer/RendererSphereTracer.h"

using RendererVariant = std::variant<CRendererSphereTracer,
									 CPostProcessorRGBFlip,
									 CPostProcessorChromaticAberration,
									 CPostProcessorFishEye>;

class CRenderPipeline {
public:
	CRenderPipeline();
	~CRenderPipeline();

	bool Init(int aWidth, int aHeight);

	void Render(CTexture2D& aBackbuffer);

private:
	void SwapTextures();

	struct SIndex {
		int myIndex;
		vec2 myUV;
	};

	int myWidth;
	int myHeight;

	std::vector<RendererVariant> myRenderPipeline;

	std::vector<SIndex> myIndices;

	CTexture2D myTexture1;
	CTexture2D myTexture2;
	const CTexture2D* myReadTexture;
	CTexture2D* myWriteTexture;
};
