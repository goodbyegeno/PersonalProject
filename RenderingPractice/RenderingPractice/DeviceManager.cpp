#include "stdafx.h"
#include "DeviceManager.h"
#include "GraphicsDevice.h"
#include "GraphicsSystem.h"
#include "DXDevice11_4.h"

DeviceManager::DeviceManager(GraphicsSystem* graphicSystem) :
	_graphicSystem(graphicSystem),
	_device(nullptr)
{
}
DeviceManager::~DeviceManager()
{
	if (nullptr != _device)
		delete _device;
}

bool DeviceManager::Initialize(HWND hwnd)
{
	//create Device 
	switch (_graphicSystem->GetGraphicsAPIType())
	{
	case RenderEngine::GRAPHICSAPITYPE::DIRECTX11_4:
		_device = new DXDevice11_4();
		break;

	case RenderEngine::GRAPHICSAPITYPE::OPENGL:
		break;
	case RenderEngine::GRAPHICSAPITYPE::MAX:
		return false;
		break;
	};
	if (nullptr == _device)
		return false;

	_device->Initialize(hwnd);

	return true;
}

bool DeviceManager::PostInitialize()
{
	return true;
}

bool DeviceManager::Reset()
{
	if (false == _device->Reset())
		return false;

	return true;
}

bool DeviceManager::PostReset() 
{
	return true;
}

void DeviceManager::PreUpdate(float deltaTime)
{
}

void DeviceManager::PostUpdate(float deltaTime)
{
}

void DeviceManager::Update(float deltaTime)
{
}
