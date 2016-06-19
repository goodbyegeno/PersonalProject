#include "RenderingManager.h"
#include "DeferredShadingMethod.h"
#include "DeviceManager.h"
#include "GraphicsSystem.h"

RenderingManager::RenderingManager(GraphicsSystem* pGraphicSystem)
{
	m_pGraphicsSystem = pGraphicSystem;
	m_pDeviceManager = nullptr;
	m_nFPS = 60;
	m_bVsync = false;
	for (int iRenderMethod = 0; iRenderMethod < static_cast<int>(RenderEngine::RenderingMode::MAX); iRenderMethod++)
	{
		m_lstRenderingMethod[iRenderMethod] = nullptr;
		m_lstRequestRender[iRenderMethod].clear();
		m_lstRequestRender[iRenderMethod].resize(100);
	}
	
}
RenderingManager::~RenderingManager()
{
	m_pGraphicsSystem = nullptr;

	for (int iRenderMethod = 0; iRenderMethod < static_cast<int>(RenderEngine::RenderingMode::MAX); iRenderMethod++)
	{
		if (m_lstRenderingMethod[iRenderMethod])
		{
			delete m_lstRenderingMethod[iRenderMethod];
		}
	}
}

bool RenderingManager::Initialize()
{
	m_nFPS = 60;
	m_bVsync = false;
	m_pDeviceManager = nullptr;

	if (m_pGraphicsSystem)
	{
		m_pDeviceManager = m_pGraphicsSystem->GetDeviceManager();
	}
	//test code
	m_lstRenderingMethod[static_cast<int>(RenderEngine::RenderingMode::Indexed_Deferred)] = CreateRenderingMethod(RenderEngine::RenderingMode::Indexed_Deferred);
}
bool RenderingManager::Reset()
{
	m_nFPS = 60;
	m_bVsync = false;
}
bool RenderingManager::RequestRender(IRenderedObject* pTarget)
{
	int nRenderMethod = static_cast<int>(pTarget->GetRenderedMode());
	m_lstRequestRender[nRenderMethod].push_back(pTarget);
}

void RenderingManager::Render(DeviceManager* pDeviceManager, ShaderManager* pShaderManager, float fDeltaTime)
{
	for (int iRenderMethod = 0; iRenderMethod < static_cast<int>(RenderEngine::RenderingMode::MAX); iRenderMethod++)
	{
		if (m_lstRenderingMethod[iRenderMethod])
		{
			m_lstRenderingMethod[iRenderMethod]->Render(pDeviceManager, pShaderManager, &(m_lstRequestRender[iRenderMethod]), fDeltaTime);
		}
	}
}
void RenderingManager::PreUpdate(float fDeltaTime)
{
	for (int iRenderMethod = 0; iRenderMethod < static_cast<int>(RenderEngine::RenderingMode::MAX); iRenderMethod++)
	{
		m_lstRequestRender[iRenderMethod].clear();
	}
}

void RenderingManager::Update(float fDeltaTime)
{
	
}
void RenderingManager::PostUpdate(float fDeltaTime)
{
	//sorting
}
IRenderMethod* RenderingManager::CreateRenderingMethod(RenderEngine::RenderingMode eRenderMode)
{
	IRenderMethod* pRenderingMethod = nullptr;

	switch (eRenderMode)
	{
	case RenderEngine::RenderingMode::Deferred_Shading:
		break;

	case RenderEngine::RenderingMode::Indexed_Deferred:
		pRenderingMethod = new DeferredShadingMethod(this);
		pRenderingMethod->Initialize();

		break;
	case RenderEngine::RenderingMode::Forward:
		break;
	};

	return pRenderingMethod;

}

std::vector<IRenderedObject*>& RenderingManager::GetRenderRequestObject(RenderEngine::RenderingMode eRenderMode)
{
	return m_lstRequestRender[static_cast<int>(eRenderMode)];
}
