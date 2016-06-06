#include "GraphicsSystem.h"
#include "RenderingManager.h"
#include "DeviceManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
GraphicsSystem::GraphicsSystem()
{
	m_pRenderingMananger	= nullptr;
	m_pDeviceManager		= nullptr;
	m_pModelManager			= nullptr;
	m_pShaderManager		= nullptr;
}
GraphicsSystem::~GraphicsSystem()
{

}

bool GraphicsSystem::Inititalize()
{
	m_pRenderingMananger	= new RenderingManager();
	m_pDeviceManager		= new DeviceManager();
	m_pModelManager			= new ModelManager();
	m_pShaderManager		= new ShaderManager();

	m_pDeviceManager->Initialize();
	m_pRenderingMananger->Initialize();
	m_pModelManager->Initialize();
	m_pShaderManager->Initialize();
}
bool GraphicsSystem::Reset()
{
	m_pDeviceManager->Reset();
	m_pRenderingMananger->Reset();
	m_pModelManager->Reset();
	m_pShaderManager->Reset();
}