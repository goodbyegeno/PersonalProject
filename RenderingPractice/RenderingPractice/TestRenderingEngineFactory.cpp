#include "stdafx.h"
#include "TestRenderingEngineFactory.h"
#include "RenderingManager.h"
#include "RenderingOverviewDefault.h"
#include "ForwardShadingMethod.h"
#include "TestStaticModelImporter.h"
#include "GraphicsSystem.h"
TestRenderingEngineFactory::TestRenderingEngineFactory()
{

}

TestRenderingEngineFactory::~TestRenderingEngineFactory()
{
}


RenderingOverviewBase* TestRenderingEngineFactory::CreateRenderingOverview(RenderEngine::GRAPHICSAPITYPE apiType, RenderingManager* renderingManager)
{
	return new RenderingOverviewDefault(renderingManager);
}

bool TestRenderingEngineFactory::CreateRenderingMethod(GraphicsSystem* graphicsSystem)
{
	graphicsSystem->GetRenderingManager()->AddRenderingMethod(new ForwardShadingMethod(graphicsSystem));

	return true;
}
IModelImporterImpl* TestRenderingEngineFactory::CreateModelImporter()
{
	return new TestStaticModelImporter();
}
