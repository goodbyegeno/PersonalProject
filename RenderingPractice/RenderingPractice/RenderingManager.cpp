#include "stdafx.h"
#include <cstring>
#include "IRenderableObject.h"
#include "RenderingManager.h"
#include "DeferredShadingMethod.h"
#include "DeviceManager.h"
#include "GraphicsSystem.h"
#include "RenderingMethod.h"
#include "RenderingOverviewBase.h"
#include "RenderingOverviewDefault.h"
#include "CoreSystem.h"
#include "SystemConfigureFileImporter.h"
#include "RenderEngineFactoryBase.h"
RenderingManager::RenderingManager(GraphicsSystem* graphicSystem) :
	_graphicsSystem(graphicSystem),
	_deviceManager(nullptr),
	_targetFPS(60),
	_vSync(false),
	_renderingOverview(nullptr),
	_initialized(false)
{
	_renderingMethodMap.clear();
}

RenderingManager::~RenderingManager()
{
	_graphicsSystem = nullptr;
	if (_renderingOverview)
		delete _renderingOverview;

	for (std::unordered_map<size_t, RenderMethod*>::iterator itorMethodMap = _renderingMethodMap.begin(); itorMethodMap != _renderingMethodMap.end(); itorMethodMap++)
	{
		delete itorMethodMap->second;
	}
	_renderingMethodMap.clear();
	_initialized = false;

}

bool RenderingManager::Initialize()
{

	_renderingOverview = _graphicsSystem->GetRenderEngineFactory()->CreateRenderingOverview(_graphicsSystem->GetGraphicsAPIType(), this);
	SystemConfigureEntity* tempEntity = coreSystem->GetConfigValue(std::hash<std::wstring>{}(L"FPSMode"));
	if (nullptr != tempEntity)
		_FPSMode = ConvertToFPSMode_(static_cast<int>(tempEntity->GetValue()));
	else
		_FPSMode = RenderEngine::FPSMODE::FLEXIBLE60;

	tempEntity = nullptr;
	tempEntity = coreSystem->GetConfigValue(std::hash<std::wstring>{}(L"TargetFPS"));
	if (nullptr != tempEntity)
		_targetFPS = static_cast<int>(tempEntity->GetValue());
	else
		_targetFPS = 60;
	
	tempEntity = nullptr;
	tempEntity = coreSystem->GetConfigValue(std::hash<std::wstring>{}(L"VSync"));
	
	_vSync = false;
	if (nullptr != tempEntity) 
	{
		if (tempEntity->GetValue() == 0.0f)
			_vSync = false;
		else
			_vSync = true;
	}

	_deviceManager = nullptr;

	if (_graphicsSystem)
	{
		_deviceManager = _graphicsSystem->GetDeviceManager();
	}

	for (std::unordered_map<size_t, RenderMethod*>::iterator itorMethodMap = _renderingMethodMap.begin(); itorMethodMap != _renderingMethodMap.end(); itorMethodMap++)
	{
		if (false == itorMethodMap->second->Initialize())
			return false;
	}
	//TEST: test code

	if (false == _renderingOverview->Initialize())
		return false;
	_initialized = true;

	return true;
}
bool RenderingManager::Reset()
{
	if (false == _initialized)
		return false;

	SystemConfigureEntity* tempEntity = coreSystem->GetConfigValue(std::hash<std::wstring>{}(L"FPSMode"));
	if (nullptr != tempEntity)
		_FPSMode = ConvertToFPSMode_(static_cast<int>(tempEntity->GetValue()));
	else
		_FPSMode = RenderEngine::FPSMODE::FLEXIBLE60;

	tempEntity = nullptr;
	tempEntity = coreSystem->GetConfigValue(std::hash<std::wstring>{}(L"TargetFPS"));
	if (nullptr != tempEntity)
		_targetFPS = static_cast<int>(tempEntity->GetValue());
	else
		_targetFPS = 60;

	tempEntity = nullptr;
	tempEntity = coreSystem->GetConfigValue(std::hash<std::wstring>{}(L"VSync"));

	_vSync = false;
	if (nullptr != tempEntity)
	{
		if (0.0f == tempEntity->GetValue())
			_vSync = false;
		else
			_vSync = true;
	}

	for (std::unordered_map<size_t, RenderMethod*>::iterator itorMethodMap = _renderingMethodMap.begin(); itorMethodMap != _renderingMethodMap.end(); itorMethodMap++)
	{
		if (false == itorMethodMap->second->Reset())
			return false;
	}
	if (false == _renderingOverview->Reset())
		return false;

	return true;
}
bool RenderingManager::RequestRender(IRenderableObject* target)
{
	//need to be thread-safety

	std::unordered_map<size_t, std::vector<IRenderableObject*>>::iterator itor = _requestRenderListMap.find(target->GetRenderMethodHashCode());
	if (_requestRenderListMap.end() == itor)
		return false;

	itor->second.push_back(target);
	
	return true;
}

void RenderingManager::Render(DeviceManager* deviceManager, ShaderManager* shaderManager, float deltaTime)
{
	if (false == _initialized)
		return;

	if (_renderingOverview)
		_renderingOverview->Render(deviceManager, shaderManager, &_requestRenderListMap, &_renderingMethodMap);
}
void RenderingManager::PreUpdate(float deltaTime)
{
	if (false == _initialized)
		return;

	for (std::unordered_map<size_t, std::vector<IRenderableObject*>>::iterator itor = _requestRenderListMap.begin(); itor != _requestRenderListMap.end(); itor++)
		itor->second.clear();
}

void RenderingManager::Update(float deltaTime)
{
	if (false == _initialized)
		return;

}
void RenderingManager::PostUpdate(float deltaTime)
{
	//sorting
	if (false == _initialized)
		return;

}

std::vector<IRenderableObject*>* RenderingManager::GetRenderRequestObject(size_t hashCode)
{
	std::unordered_map<size_t, std::vector<IRenderableObject*>>::iterator itor = _requestRenderListMap.find(hashCode);
	
	if (_requestRenderListMap.end() == itor)
		return nullptr;

	return &(itor->second);
}

bool RenderingManager::AddRenderingMethod(RenderMethod* renderingMethod)
{
	std::unordered_map<size_t, RenderMethod*>::iterator itorMethodMap = _renderingMethodMap.find(renderingMethod->GetHashcode());
	if (_renderingMethodMap.end() != itorMethodMap)
		return false;

	_requestRenderListMap.insert(std::unordered_map<size_t, std::vector<IRenderableObject*>>::value_type(renderingMethod->GetHashcode(), std::vector<IRenderableObject*>()));
	_renderingMethodMap.insert(std::unordered_map<size_t, RenderMethod*>::value_type(renderingMethod->GetHashcode(), renderingMethod));
	return true;
}

RenderEngine::FPSMODE RenderingManager::ConvertToFPSMode_(int mode)
{

	switch (static_cast<RenderEngine::FPSMODE>(mode))
	{
	case RenderEngine::FPSMODE::FLEXIBLE30:
		return RenderEngine::FPSMODE::FLEXIBLE30;
	case RenderEngine::FPSMODE::FLEXIBLE60:
		return RenderEngine::FPSMODE::FLEXIBLE60;
	case RenderEngine::FPSMODE::FIXED60:
		return RenderEngine::FPSMODE::FIXED60;
	case RenderEngine::FPSMODE::MONITOR:
		return RenderEngine::FPSMODE::MONITOR;
	case RenderEngine::FPSMODE::MAX:
		return RenderEngine::FPSMODE::MAX;
	};
	return RenderEngine::FPSMODE::MAX;
}