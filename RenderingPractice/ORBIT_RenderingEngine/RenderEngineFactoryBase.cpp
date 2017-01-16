#include "stdafx.h"
#include "RenderEngineFactoryBase.h"
#include "GraphicsSystem.h"
RenderEngineFactoryBase::RenderEngineFactoryBase()
{
}
RenderEngineFactoryBase::~RenderEngineFactoryBase()
{
}

RenderingOverviewBase* RenderEngineFactoryBase::CreateRenderingOverview(RenderEngine::GRAPHICSAPITYPE apiType, RenderingManager* renderingManager)
{
	return nullptr;
}

bool RenderEngineFactoryBase::CreateRenderingMethod(GraphicsSystem* graphicsSystem)
{
	return false;
}