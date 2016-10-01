#include "stdafx.h"
#include "GraphicsSystem.h"
#include "RenderingManager.h"
#include "DeviceManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "RenderingSingletonManager.h"
#include "RenderEngineFactoryBase.h"
GraphicsSystem::GraphicsSystem(GraphicsSystemInitialData& data) :
	_graphicsAPIType(data.graphicsAPIType),
	_renderingMananger(nullptr),
	_deviceManager(nullptr),
	_modelManager(nullptr),
	_shaderManager(nullptr),
	_renderEngineFactory(data.renderEngineFactory)
{
	if (nullptr == _renderEngineFactory)
	{
		//TODO create default factory 
	}

	_renderingMananger = new RenderingManager(this);
	_deviceManager = new DeviceManager(this);
	_modelManager = new ModelManager(this, _renderEngineFactory->CreateModelImporter());
	_shaderManager = new ShaderManager(this);
	
}
GraphicsSystem::~GraphicsSystem()
{
	if (_renderingMananger)
		delete _renderingMananger;
	if (_deviceManager)
		delete _deviceManager;

	if (_modelManager)
		delete _modelManager;

	if (_shaderManager)
		delete _shaderManager;

	if (_renderEngineFactory)
		delete _renderEngineFactory;
}

bool GraphicsSystem::Initialize(HWND hwnd)
{
	_renderEngineFactory->CreateRenderingMethod(this);
	_renderEngineFactory->CreateRenderingOverview(this->_graphicsAPIType, _renderingMananger);

	_deviceManager		->Initialize(hwnd);
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
