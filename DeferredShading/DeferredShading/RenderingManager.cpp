#include "RenderingManager.h"
#include "DeferredShadingMethod.h"
RenderingManager::RenderingManager()
{
	m_nFPS = 60;
	m_bVsync = false;
	m_eRenderingMode = RenderEngine::RenderingMode::indexed_Deferred;
}
RenderingManager::~RenderingManager()
{
	
}

bool RenderingManager::Initialize()
{
	m_nFPS = 60;
	m_bVsync = false;
	m_eRenderingMode = RenderEngine::RenderingMode::indexed_Deferred;
	m_pRenderingMethod = CreateRenderingMethod();
}
bool RenderingManager::Reset()
{
	m_nFPS = 60;
	m_bVsync = false;
}

void RenderingManager::Render(DeviceManager* pDeviceManager, ShaderManager* pShaderManager, float fDeltaTime)
{
	m_pRenderingMethod->Render(pDeviceManager, pShaderManager, fDeltaTime);
}

IRenderMethod* RenderingManager::CreateRenderingMethod()
{
	IRenderMethod* pRenderingMethod = nullptr;
	switch (m_eRenderingMode)
	{
	case RenderEngine::RenderingMode::Deferred:
		break;

	case RenderEngine::RenderingMode::indexed_Deferred:
		pRenderingMethod = new DeferredShadingMethod(this);
		pRenderingMethod->Initialize();

		break;
	case RenderEngine::RenderingMode::Forward:
		break;
	};

	return pRenderingMethod;

}