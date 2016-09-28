#include "stdafx.h"
#include "CustomRenderEngineFactory.h"
#include "RenderingOverviewDefault.h"
#include "RenderingManager.h"
#include "DeferredShadingMethod.h"
CustomRenderEngineFactory::CustomRenderEngineFactory()
{
}

CustomRenderEngineFactory::~CustomRenderEngineFactory()
{
}

RenderingOverviewBase* CustomRenderEngineFactory::CreateRenderingOverview(RenderEngine::GRAPHICSAPITYPE apiType, RenderingManager* renderingManager)
{
	switch (apiType)
	{
	case RenderEngine::GRAPHICSAPITYPE::DIRECTX11_4:
		return new RenderingOverviewDefault(renderingManager);

	};

	return nullptr;

}

bool CustomRenderEngineFactory::CreateRenderingMethod(RenderingManager* renderingManager)
{
	renderingManager->AddRenderingMethod(new DeferredShadingMethod(renderingManager));
	return true;
}


