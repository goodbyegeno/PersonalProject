#include "stdafx.h"
#include "RenderEngineFactoryManager.h"
#include "CustomRenderEngineFactory.h"
#include "RenderEngineFactoryBase.h"
RenderEngineFactoryManager::RenderEngineFactoryManager() :
	_renderEngineFactoryImpl(nullptr)
{
	CreateRenderEngineFactoryImpl_();
}

RenderEngineFactoryManager::~RenderEngineFactoryManager()
{
	delete _renderEngineFactoryImpl;
}

void RenderEngineFactoryManager::CreateRenderEngineFactoryImpl_()
{
	//change when RenderEngineFactory added;
	_renderEngineFactoryImpl = new CustomRenderEngineFactory();

}

RenderingOverviewBase* RenderEngineFactoryManager::CreateRenderingOverview(RenderEngine::GRAPHICSAPITYPE apiType, RenderingManager* renderingManager)
{
	return _renderEngineFactoryImpl->CreateRenderingOverview(apiType, renderingManager);
}
bool RenderEngineFactoryManager::CreateRenderingMethod(RenderingManager* renderingManager)
{
	return _renderEngineFactoryImpl->CreateRenderingMethod(renderingManager);
}