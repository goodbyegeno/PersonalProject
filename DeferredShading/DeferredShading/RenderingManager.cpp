#include "stdafx.h"
#include "IRenderedObject.h"
#include "RenderingManager.h"
#include "DeferredShadingMethod.h"
#include "DeviceManager.h"
#include "GraphicsSystem.h"

RenderingManager::RenderingManager(GraphicsSystem* graphicSystem)
{
	_graphicsSystem = graphicSystem;
	_deviceManager = nullptr;
	_FPS = 60;
	_vSync = false;
	for (int RenderMethod = 0; RenderMethod < static_cast<int>(RenderEngine::RENDERINGMODE::MAX); RenderMethod++)
	{
		_renderingMethod[RenderMethod] = nullptr;
		_requestRender[RenderMethod].clear();
		_requestRender[RenderMethod].resize(100);
	}
	
}
RenderingManager::~RenderingManager()
{
	_graphicsSystem = nullptr;

	for (int RenderMethod = 0; RenderMethod < static_cast<int>(RenderEngine::RENDERINGMODE::MAX); RenderMethod++)
	{
		if (_renderingMethod[RenderMethod])
		{
			delete _renderingMethod[RenderMethod];
		}
	}
}

bool RenderingManager::Initialize()
{
	_FPS = 60;
	_vSync = false;
	_deviceManager = nullptr;

	if (_graphicsSystem)
	{
		_deviceManager = _graphicsSystem->GetDeviceManager();
	}
	//test code
	_renderingMethod[static_cast<int>(RenderEngine::RENDERINGMODE::INDEXED_DEFERRED_SHADING)] = CreateRenderingMethod(RenderEngine::RENDERINGMODE::INDEXED_DEFERRED_SHADING);

	return true;
}
bool RenderingManager::Reset()
{
	_FPS = 60;
	_vSync = false;
	return true;
}
bool RenderingManager::RequestRender(IRenderedObject* target)
{
	int renderMethodIndex = static_cast<int>(target->GetRenderedMode());
	_requestRender[renderMethodIndex].push_back(target);
	return true;
}

void RenderingManager::Render(DeviceManager* deviceManager, ShaderManager* shaderManager, float deltaTime)
{
	for (int RenderMethod = 0; RenderMethod < static_cast<int>(RenderEngine::RENDERINGMODE::MAX); RenderMethod++)
	{
		if (_renderingMethod[RenderMethod])
		{
			_renderingMethod[RenderMethod]->Render(deviceManager, shaderManager, _requestRender[RenderMethod], deltaTime);
		}
	}
}
void RenderingManager::PreUpdate(float deltaTime)
{
	for (int RenderMethod = 0; RenderMethod < static_cast<int>(RenderEngine::RENDERINGMODE::MAX); RenderMethod++)
	{
		_requestRender[RenderMethod].clear();
	}
}

void RenderingManager::Update(float deltaTime)
{
	
}
void RenderingManager::PostUpdate(float deltaTime)
{
	//sorting
}
RenderMethod* RenderingManager::CreateRenderingMethod(RenderEngine::RENDERINGMODE renderMode)
{
	RenderMethod* renderingMethod = nullptr;

	switch (renderMode)
	{
	case RenderEngine::RENDERINGMODE::DEFERRED_SHADING:
		break;

	case RenderEngine::RENDERINGMODE::INDEXED_DEFERRED_SHADING:
		renderingMethod = new DeferredShadingMethod(this);
		renderingMethod->Initialize();

		break;
	case RenderEngine::RENDERINGMODE::FORWARD:
		break;
	};

	return renderingMethod;

}

std::vector<IRenderedObject*>& RenderingManager::GetRenderRequestObject(RenderEngine::RENDERINGMODE renderMode)
{
	return _requestRender[static_cast<int>(renderMode)];
}
