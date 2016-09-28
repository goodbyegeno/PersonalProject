#pragma once
#include "RenderEngineCommon.h"
class RenderEngineFactoryBase;
class RenderingOverviewBase;
class RenderingManager;

class RenderEngineFactoryManager
{
public:
	RenderEngineFactoryManager();
	virtual ~RenderEngineFactoryManager();

	RenderingOverviewBase* CreateRenderingOverview(RenderEngine::GRAPHICSAPITYPE apiType, RenderingManager* renderingManager);
	bool CreateRenderingMethod(RenderingManager* renderingManager);

private:
	void CreateRenderEngineFactoryImpl_();

	RenderEngineFactoryBase* _renderEngineFactoryImpl;
};