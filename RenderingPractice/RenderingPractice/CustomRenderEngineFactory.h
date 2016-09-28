#pragma once
#include "RenderEngineFactoryBase.h"
class CustomRenderEngineFactory : public RenderEngineFactoryBase
{
public:
	CustomRenderEngineFactory();
	virtual ~CustomRenderEngineFactory();

	virtual RenderingOverviewBase* CreateRenderingOverview(RenderEngine::GRAPHICSAPITYPE apiType, RenderingManager* renderingManager);
	virtual bool CreateRenderingMethod(RenderingManager* renderingManager);

};