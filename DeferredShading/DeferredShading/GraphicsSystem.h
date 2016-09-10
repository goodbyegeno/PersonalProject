#pragma once
#include "RenderEngineCommon.h"
class RenderingManager;
class DeviceManager;
class RenderedObjectManager;
class ShaderManager;

class  GraphicsSystem
{
public:
	GraphicsSystem();
	virtual ~GraphicsSystem();

	bool Inititalize();
	bool Reset();
	void PreUpdate	(float deltaTime);
	void Update		(float deltaTime);
	void PostUpdate	(float deltaTime);
	void Render(float deltaTime);
	bool InitializeSingleton_();

	RenderEngine::GRAPHICSAPITYPE GetGraphicsAPIType()			{ return _graphicsAPIType; }
	RenderingManager*		GetRenderingManager()				{ return _renderingMananger; }
	DeviceManager*			GetDeviceManager()					{ return _deviceManager; }
	RenderedObjectManager*	GetRenderedObjectManager()			{ return _renderedObjectManager; }
	ShaderManager*			GetShaderManager()					{ return _shaderManager; }

private:
	
	RenderEngine::GRAPHICSAPITYPE _graphicsAPIType;

	RenderingManager*		_renderingMananger;
	DeviceManager*			_deviceManager;
	RenderedObjectManager*	_renderedObjectManager;
	ShaderManager*			_shaderManager;
};