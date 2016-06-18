#pragma once
#include "RenderEngineCommon.h"
#include <vector>
class GraphicsSystem;
class DeviceManager;

class RenderingManager
{
public:
	RenderingManager(GraphicsSystem* pGraphicSystem);
	virtual ~RenderingManager();

	bool Initialize();
	bool Reset();

	void Render(DeviceManager* pDeviceManager, ShaderManager* pShaderManager, float fDeltaTime);
	bool IsVsyncOn() { return m_bVsync; }
	int	 GetFPS() { return m_nFPS; }
	bool RequestRender(IRenderedObject* pTarget);
	void PreUpdate(float fDeltaTime);
	void Update(float fDeltaTime);
	void PostUpdate(float fDeltaTime);

private:
	IRenderMethod* CreateRenderingMethod(RenderEngine::RenderingMode eRenderMode);

private:

	IRenderMethod*					m_lstRenderingMethod[static_cast<int>(RenderEngine::RenderingMode::MAX)];
	std::vector<IRenderedObject*>	m_lstRequestRender	[static_cast<int>(RenderEngine::RenderingMode::MAX)];

	GraphicsSystem*					m_pGraphicsSystem;
	DeviceManager*					m_pDeviceManager;

	//settings
	int m_nFPS;
	bool m_bVsync;


};