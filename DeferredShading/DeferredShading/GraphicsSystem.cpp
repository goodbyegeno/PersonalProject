#include "stdafx.h"
#include "GraphicsSystem.h"
#include "RenderingManager.h"
#include "DeviceManager.h"
#include "RenderedObjectManager.h"
#include "ShaderManager.h"
GraphicsSystem::GraphicsSystem()
{
	_renderingMananger		= nullptr;
	_deviceManager			= nullptr;
	_renderedObjectManager	= nullptr;
	_shaderManager			= nullptr;
}
GraphicsSystem::~GraphicsSystem()
{

}

bool GraphicsSystem::Inititalize()
{
	_renderingMananger		= new RenderingManager(this);
	_deviceManager			= new DeviceManager(this);
	_renderedObjectManager	= new RenderedObjectManager(this);
	_shaderManager			= new ShaderManager(this);

	_deviceManager		->Initialize();
	_renderingMananger	->Initialize();
	_renderedObjectManager->Initialize();
	_shaderManager		->Initialize();
	return true;

}
bool GraphicsSystem::Reset()
{
	_deviceManager			->Reset();
	_renderingMananger		->Reset();
	_renderedObjectManager	->Reset();
	_shaderManager			->Reset();

	return true;
}
void GraphicsSystem::PreUpdate(float deltaTime)
{
	_deviceManager		->PreUpdate(deltaTime);
	_renderingMananger	->PreUpdate(deltaTime);
	_renderedObjectManager->PreUpdate(deltaTime);
	_shaderManager		->PreUpdate(deltaTime);

}

void GraphicsSystem::PostUpdate(float deltaTime)
{
	_deviceManager		->PostUpdate(deltaTime);
	_renderingMananger	->PostUpdate(deltaTime);
	_renderedObjectManager->PostUpdate(deltaTime);
	_shaderManager		->PostUpdate(deltaTime);
}
void GraphicsSystem::Update(float deltaTime)
{
	_deviceManager		->Update(deltaTime);
	_renderingMananger	->Update(deltaTime);
	_renderedObjectManager->Update(deltaTime);
	_shaderManager		->Update(deltaTime);
}
void GraphicsSystem::Render(float deltaTime)
{
	_renderingMananger->Render(_deviceManager, _shaderManager, deltaTime);

}