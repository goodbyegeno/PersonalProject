#pragma once
#include "RenderEngineCommon.h"
class RenderingOverviewBase;
class RenderingManager;
class IModelImporterImpl;
class GraphicsSystem;

class RenderEngineFactoryBase
{
public:
	RenderEngineFactoryBase();
	virtual ~RenderEngineFactoryBase();

	virtual RenderingOverviewBase* CreateRenderingOverview(RenderEngine::GRAPHICSAPITYPE apiType, RenderingManager* renderingManager);
	virtual bool CreateRenderingMethod(GraphicsSystem* graphicsSystem);
	virtual IModelImporterImpl* CreateModelImporter() = 0;

};