#include "RenderPipeline.h"

#include <execution>
#include <iostream>

CRenderPipeline::CRenderPipeline() {
}

CRenderPipeline::~CRenderPipeline() {
}

bool CRenderPipeline::Init(int aWidth, int aHeight) {
	myWidth = aWidth;
	myHeight = aHeight;

	if (!myTexture1.Init(myWidth, myHeight)) return false;
	if (!myTexture2.Init(myWidth, myHeight)) return false;

	myReadTexture = &myTexture1;
	myWriteTexture = &myTexture2;

	myIndices.resize(myWidth * myHeight);
	auto initIndicesPred = [&](auto& index) {
		int i = (int)(&index - &myIndices[0]);
		index.myIndex = i;
		index.myUV = {(i % myWidth) / (float)myWidth, (i / myWidth) / (float)myHeight};
	};
	std::for_each(std::execution::par_unseq, myIndices.begin(), myIndices.end(), initIndicesPred);

	CRendererSphereTracer sphereTracer;
	sphereTracer.Init(vec2(static_cast<float>(myWidth), static_cast<float>(myHeight)));

	myRenderPipeline.push_back(sphereTracer);
	myRenderPipeline.push_back(CPostProcessorRGBFlip());
	myRenderPipeline.push_back(CPostProcessorChromaticAberration());
	myRenderPipeline.push_back(CPostProcessorFishEye());

	return true;
}

void CRenderPipeline::Render(CTexture2D& aBackbuffer) {
	auto visitorPred = [&](auto&& renderer) {
		auto drawPixelPred = [&](const auto& index) {
			vec4 col = renderer.Render(index.myUV, *myReadTexture);
			myWriteTexture->SetPixelData(index.myIndex, {col.r, col.g, col.b});
		};

		std::for_each(std::execution::par_unseq, myIndices.begin(), myIndices.end(), drawPixelPred);
	};

	for (RendererVariant& rendererVariant : myRenderPipeline) {
		std::visit(visitorPred, rendererVariant);

		SwapTextures();
	}

	aBackbuffer = *myReadTexture;
}

void CRenderPipeline::SwapTextures() {
	if (myReadTexture == &myTexture1) {
		myReadTexture = &myTexture2;
		myWriteTexture = &myTexture1;
	} else {
		myReadTexture = &myTexture1;
		myWriteTexture = &myTexture2;
	}
}
