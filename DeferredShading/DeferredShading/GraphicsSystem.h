#pragma once
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

	RenderingManager*		GetRenderingManager()				{ return _renderingMananger; }
	DeviceManager*			GetDeviceManager()					{ return _deviceManager; }
	RenderedObjectManager*	GetRenderedObjectManager()			{ return _renderedObjectManager; }
	ShaderManager*			GetShaderManager()					{ return _shaderManager; }
private:
	RenderingManager*		_renderingMananger;
	DeviceManager*			_deviceManager;
	RenderedObjectManager*	_renderedObjectManager;
	ShaderManager*			_shaderManager;
};