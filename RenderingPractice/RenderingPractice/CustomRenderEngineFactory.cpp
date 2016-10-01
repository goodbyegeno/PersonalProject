#include "stdafx.h"
#include "CustomRenderEngineFactory.h"
#include "RenderingOverviewDefault.h"
#include "RenderingManager.h"
#include "DeferredShadingMethod.h"
#include "ForwardShadingMethod.h"
#include "GraphicsSystem.h"

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

bool CustomRenderEngineFactory::CreateRenderingMethod(GraphicsSystem* graphicsSystem)
{
	//renderingManager->AddRenderingMethod(new DeferredShadingMethod(renderingManager));
	graphicsSystem->GetRenderingManager()->AddRenderingMethod(new ForwardShadingMethod(graphicsSystem));
	return true;
}


