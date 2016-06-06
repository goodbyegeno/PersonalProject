#include "DeferredShadingMethod.h"
#include "RenderingManager.h"

DeferredShadingMethod::DeferredShadingMethod(RenderingManager* pRenderingMnanger)
{
	m_pRenderingMananger = pRenderingMnanger;
	m_bVsync = false;
	m_fMSecPerFrame = 0.0f;
	m_fCurrentMSecPerFrame = 0.0f;
	m_nFPS = 0;
}
DeferredShadingMethod::~DeferredShadingMethod()
{

}

bool DeferredShadingMethod::Initialize()
{
	m_bVsync = m_pRenderingMananger->IsVsyncOn();
	m_nFPS = m_pRenderingMananger->GetFPS();
	m_fMSecPerFrame = 1000 / m_nFPS; 
	m_fCurrentMSecPerFrame = 0.0f;

	return true;
}
bool DeferredShadingMethod::Reset()
{
	m_bVsync = m_pRenderingMananger->IsVsyncOn();
	m_nFPS = m_pRenderingMananger->GetFPS();
	m_fMSecPerFrame = 1000 / m_nFPS;
	m_fCurrentMSecPerFrame = 0.0f;

	return true;
}

void DeferredShadingMethod::Render(DeviceManager* pDeviceManager, ShaderManager* pShaderManager, float fDeltaTime)
{

}
