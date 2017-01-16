#pragma once
#include "RenderEngineFactoryBase.h"
class TestRenderingEngineFactory : public RenderEngineFactoryBase
{
public:
	TestRenderingEngineFactory();
	virtual ~TestRenderingEngineFactory();


	virtual RenderingOverviewBase* CreateRenderingOverview(RenderEngine::GRAPHICSAPITYPE apiType, RenderingManager* renderingManager);
	virtual bool CreateRenderingMethod(GraphicsSystem* graphicsSystem);
	virtual IModelImporterImpl* CreateModelImporter();

};