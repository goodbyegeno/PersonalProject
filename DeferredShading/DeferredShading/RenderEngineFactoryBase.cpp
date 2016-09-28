#include "stdafx.h"
#include "RenderEngineFactoryBase.h"

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

bool RenderEngineFactoryBase::CreateRenderingMethod(RenderingManager* renderingManager)
{
	return false;
}