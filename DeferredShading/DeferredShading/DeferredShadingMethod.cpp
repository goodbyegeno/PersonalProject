#include "DeferredShadingMethod.h"
#include "RenderingManager.h"
#include "IDeferredShadingMethodImpl.h"

DeferredShadingMethod::DeferredShadingMethod(RenderingManager* pRenderingMnanger)
{
	m_pRenderingMananger = pRenderingMnanger;
	m_pRendingMethodImpl = nullptr;
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

void DeferredShadingMethod::Render(DeviceManager* pDeviceManager, ShaderManager* pShaderManager, std::vector<IRenderedObject>* lstRederRequestObject, float fDeltaTime)
{
	m_pRendingMethodImpl->SetMatrix();

	RenderGBuffer_	(pDeviceManager, pShaderManager, lstRederRequestObject, fDeltaTime);
	RenderLighting_	(pDeviceManager, pShaderManager, lstRederRequestObject, fDeltaTime);

}

void DeferredShadingMethod::RenderGBuffer_(DeviceManager* pDeviceManager, ShaderManager* pShaderManager, std::vector<IRenderedObject>* lstRederRequestObject, float fDeltaTime)
{
	m_pRendingMethodImpl->SetShader();
	m_pRendingMethodImpl->SetConstVariables();
	m_pRendingMethodImpl->SetRenderTarget();
	m_pRendingMethodImpl->RenderMesh();
}
void DeferredShadingMethod::RenderLighting_(DeviceManager* pDeviceManager, ShaderManager* pShaderManager, std::vector<IRenderedObject>* lstRederRequestObject, float fDeltaTime)
{
	m_pRendingMethodImpl->RenderLighting();
}
