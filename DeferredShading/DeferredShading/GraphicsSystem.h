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
	void PreUpdate	(float fDeltaTime);
	void Update		(float fDeltaTime);
	void PostUpdate	(float fDeltaTime);
	void Render(float fDeltaTime);

	RenderingManager*		GetRenderingManager()				{ return m_pRenderingMananger; }
	DeviceManager*			GetDeviceManager()					{ return m_pDeviceManager; }
	RenderedObjectManager*	GetRenderedObjectManager()			{ return m_pRenderedObjectManager; }
	ShaderManager*			GetShaderManager()					{ return m_pShaderManager; }
private:
	RenderingManager*		m_pRenderingMananger;
	DeviceManager*			m_pDeviceManager;
	RenderedObjectManager*	m_pRenderedObjectManager;
	ShaderManager*			m_pShaderManager;
};