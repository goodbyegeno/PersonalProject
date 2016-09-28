#pragma once
#include "RenderEngineCommon.h"
class RenderingOverviewBase;
class RenderingManager;

class RenderEngineFactoryBase
{
public:
	RenderEngineFactoryBase();
	virtual ~RenderEngineFactoryBase();

	virtual RenderingOverviewBase* CreateRenderingOverview(RenderEngine::GRAPHICSAPITYPE apiType, RenderingManager* renderingManager);
	virtual bool CreateRenderingMethod(RenderingManager* renderingManager);

};