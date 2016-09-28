#include "stdafx.h"
#include "GraphicsSystem.h"
#include "RenderingManager.h"
#include "DeviceManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "RenderingSingletonManager.h"
#include "RenderEngineFactoryManager.h"
GraphicsSystem::GraphicsSystem(GraphicsSystemInitialData& data) :
	_graphicsAPIType(data.graphicsAPIType),
	_renderingMananger(nullptr),
	_deviceManager(nullptr),
	_modelManager(nullptr),
	_shaderManager(nullptr)
{
	_renderingMananger = new RenderingManager(this);
	_deviceManager = new DeviceManager(this);
	_modelManager = new ModelManager(this);
	_shaderManager = new ShaderManager(this);
	_renderEngineFactory = new RenderEngineFactoryManager();
}
GraphicsSystem::~GraphicsSystem()
{
}

bool GraphicsSystem::Initialize()
{
	_renderEngineFactory->CreateRenderingMethod(_renderingMananger);
	_renderEngineFactory->CreateRenderingOverview(this->_graphicsAPIType, _renderingMananger);

	_deviceManager		->Initialize();
	_renderingMananger	->Initialize();
	_modelManager		->Initialize();
	_shaderManager		->Initialize();

	return true;
}
bool GraphicsSystem::Reset()
{
	_deviceManager			->Reset();
	_renderingMananger		->Reset();
	_modelManager			->Reset();
	_shaderManager			->Reset();

	return true;
}
bool GraphicsSystem::InitializeSingleton_()
{
	RenderingSingletonManager::GetInstance();

	return true;

}

void GraphicsSystem::PreUpdate(float deltaTime)
{
	_deviceManager		->PreUpdate(deltaTime);
	_renderingMananger	->PreUpdate(deltaTime);
	_modelManager		->PreUpdate(deltaTime);
	_shaderManager		->PreUpdate(deltaTime);

}

void GraphicsSystem::PostUpdate(float deltaTime)
{
	_deviceManager		->PostUpdate(deltaTime);
	_renderingMananger	->PostUpdate(deltaTime);
	_modelManager		->PostUpdate(deltaTime);
	_shaderManager		->PostUpdate(deltaTime);
}
void GraphicsSystem::Update(float deltaTime)
{
	_deviceManager		->Update(deltaTime);
	_renderingMananger	->Update(deltaTime);
	_modelManager		->Update(deltaTime);
	_shaderManager		->Update(deltaTime);
}
void GraphicsSystem::Render(float deltaTime)
{
	_renderingMananger->Render(_deviceManager, _shaderManager, deltaTime);

}

void GraphicsSystem::PhaseReady(float deltaTime)
{
}
void GraphicsSystem::PhaseEnd(float deltaTime)
{
}

bool GraphicsSystem::AddRenderingRequest(IRenderableObject* renderObject)
{
	return _renderingMananger->RequestRender(renderObject);
}
ModelStaticData* GraphicsSystem::GetStaticModel(size_t modelHashCode)
{
	return _modelManager->GetModelData(modelHashCode);
}
