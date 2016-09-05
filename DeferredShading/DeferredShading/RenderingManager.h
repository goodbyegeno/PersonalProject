#pragma once
#include "RenderEngineCommon.h"
#include <vector>
class GraphicsSystem;
class DeviceManager;
class IRenderedObject;
class IRenderMethod;
class ShaderManager;

class RenderingManager
{
public:
	RenderingManager(GraphicsSystem* graphicSystem);
	virtual ~RenderingManager();

	bool Initialize();
	bool Reset();

	void Render(DeviceManager* deviceManager, ShaderManager* shaderManager, float deltaTime);
	bool IsVsyncOn() { return _vSync; }
	int	 GetFPS() { return _FPS; }
	void PreUpdate(float deltaTime);
	void Update(float deltaTime);
	void PostUpdate(float deltaTime);
	bool RequestRender(IRenderedObject* target);
	std::vector<IRenderedObject*>& GetRenderRequestObject(RenderEngine::RENDERINGMODE renderMode);
	DeviceManager* GetDeviceManager() { return _deviceManager; }
private:
	IRenderMethod* CreateRenderingMethod(RenderEngine::RENDERINGMODE renderMode);

private:

	IRenderMethod*					_renderingMethod[static_cast<int>(RenderEngine::RENDERINGMODE::MAX)];
	std::vector<IRenderedObject*>	_requestRender	[static_cast<int>(RenderEngine::RENDERINGMODE::MAX)];

	GraphicsSystem*					_graphicsSystem;
	DeviceManager*					_deviceManager;

	//settings
	int								_FPS;
	bool							_vSync;


};