#pragma once
#include "RenderEngineCommon.h"
#include <vector>
#include <unordered_map>

class GraphicsSystem;
class DeviceManager;
class IRenderableObject;
class RenderMethod;
class ShaderManager;
class RenderingOverviewBase;

class RenderingManager
{
public:
	RenderingManager(GraphicsSystem* graphicSystem);
	RenderingManager() = delete;

	virtual ~RenderingManager();

	bool Initialize();
	bool Reset();

	void Render(DeviceManager* deviceManager, ShaderManager* shaderManager, float deltaTime);
	bool IsVsyncOn() { return _vSync; }
	int	 GetTargetFPS() { return _targetFPS; }
	void PreUpdate(float deltaTime);
	void Update(float deltaTime);
	void PostUpdate(float deltaTime);
	bool RequestRender(IRenderableObject* target);
	std::vector<IRenderableObject*>* GetRenderRequestObject(size_t hashCode);
	std::unordered_map<size_t, RenderMethod*>* GetRenderingMethodMap() { return &_renderingMethodMap; }	
	DeviceManager* GetDeviceManager() { return _deviceManager; }

	bool AddRenderingMethod(RenderMethod* renderingMethod);

private:
	RenderEngine::FPSMODE ConvertToFPSMode_(int mode);

	RenderingOverviewBase*						_renderingOverview;
	std::unordered_map<size_t, RenderMethod*>	_renderingMethodMap;
	std::unordered_map<size_t, std::vector<IRenderableObject*>> _requestRenderListMap;

	GraphicsSystem*					_graphicsSystem;
	DeviceManager*					_deviceManager;

//settings
	RenderEngine::FPSMODE			_FPSMode;
	int								_targetFPS;
	bool							_vSync;
	bool							_initialized;


};