#pragma once
class RenderingManager;
class DeviceManager;
class ModelManager;
class ShaderManager;

class  GraphicsSystem
{
public:
	GraphicsSystem();
	virtual ~GraphicsSystem();

	bool Inititalize();
	bool Reset();

private:
	RenderingManager*	m_pRenderingMananger;
	DeviceManager*		m_pDeviceManager;
	ModelManager*		m_pModelManager;
	ShaderManager*		m_pShaderManager;
};