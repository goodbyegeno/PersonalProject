#pragma once
#include "RenderEngineCommon.h"
class RenderingManager
{
public:
	RenderingManager();
	virtual ~RenderingManager();

	bool Initialize();
	bool Reset();

	void Render(DeviceManager* pDeviceManager, ShaderManager* pShaderManager, float fDeltaTime);
	bool IsVsyncOn() { return m_bVsync; }
	int	 GetFPS() { return m_nFPS; }
private:
	IRenderMethod* CreateRenderingMethod();

private:

	IRenderMethod* m_pRenderingMethod;

	//settings
	int m_nFPS;
	bool m_bVsync;
	RenderEngine::RenderingMode m_eRenderingMode;


};