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
	for (int iRenderMethod = 0; iRenderMethod < static_cast<int>(RenderEngine::RENDERINGMODE::MAX); iRenderMethod++)
	{
		_renderingMethod[iRenderMethod] = nullptr;
		_requestRender[iRenderMethod].clear();
		_requestRender[iRenderMethod].resize(100);
	}
	
}
RenderingManager::~RenderingManager()
{
	_graphicsSystem = nullptr;

	for (int iRenderMethod = 0; iRenderMethod < static_cast<int>(RenderEngine::RENDERINGMODE::MAX); iRenderMethod++)
	{
		if (_renderingMethod[iRenderMethod])
		{
			delete _renderingMethod[iRenderMethod];
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
	for (int iRenderMethod = 0; iRenderMethod < static_cast<int>(RenderEngine::RENDERINGMODE::MAX); iRenderMethod++)
	{
		if (_renderingMethod[iRenderMethod])
		{
			_renderingMethod[iRenderMethod]->Render(deviceManager, shaderManager, _requestRender[iRenderMethod], deltaTime);
		}
	}
}
void RenderingManager::PreUpdate(float deltaTime)
{
	for (int iRenderMethod = 0; iRenderMethod < static_cast<int>(RenderEngine::RENDERINGMODE::MAX); iRenderMethod++)
	{
		_requestRender[iRenderMethod].clear();
	}
}

void RenderingManager::Update(float deltaTime)
{
	
}
void RenderingManager::PostUpdate(float deltaTime)
{
	//sorting
}
IRenderMethod* RenderingManager::CreateRenderingMethod(RenderEngine::RENDERINGMODE renderMode)
{
	IRenderMethod* renderingMethod = nullptr;

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
