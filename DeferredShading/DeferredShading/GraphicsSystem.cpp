#include "GraphicsSystem.h"
#include "RenderingManager.h"
#include "DeviceManager.h"
#include "RenderedObjectManager.h"
#include "ShaderManager.h"
GraphicsSystem::GraphicsSystem()
{
	m_pRenderingMananger		= nullptr;
	m_pDeviceManager			= nullptr;
	m_pRenderedObjectManager	= nullptr;
	m_pShaderManager			= nullptr;
}
GraphicsSystem::~GraphicsSystem()
{

}

bool GraphicsSystem::Inititalize()
{
	m_pRenderingMananger		= new RenderingManager(this);
	m_pDeviceManager			= new DeviceManager(this);
	m_pRenderedObjectManager	= new RenderedObjectManager(this);
	m_pShaderManager			= new ShaderManager(this);

	m_pDeviceManager		->Initialize();
	m_pRenderingMananger	->Initialize();
	m_pRenderedObjectManager->Initialize();
	m_pShaderManager		->Initialize();
}
bool GraphicsSystem::Reset()
{
	m_pDeviceManager			->Reset();
	m_pRenderingMananger		->Reset();
	m_pRenderedObjectManager	->Reset();
	m_pShaderManager			->Reset();
}
void GraphicsSystem::PreUpdate(float fDeltaTime)
{
	m_pDeviceManager		->PreUpdate(fDeltaTime);
	m_pRenderingMananger	->PreUpdate(fDeltaTime);
	m_pRenderedObjectManager->PreUpdate(fDeltaTime);
	m_pShaderManager		->PreUpdate(fDeltaTime);
}

void GraphicsSystem::PostUpdate(float fDeltaTime)
{
	m_pDeviceManager		->PostUpdate(fDeltaTime);
	m_pRenderingMananger	->PostUpdate(fDeltaTime);
	m_pRenderedObjectManager->PostUpdate(fDeltaTime);
	m_pShaderManager		->PostUpdate(fDeltaTime);
}
void GraphicsSystem::Update(float fDeltaTime)
{
	m_pDeviceManager		->Update(fDeltaTime);
	m_pRenderingMananger	->Update(fDeltaTime);
	m_pRenderedObjectManager->Update(fDeltaTime);
	m_pShaderManager		->Update(fDeltaTime);
}
void GraphicsSystem::Render(float fDeltaTime)
{
	m_pRenderingMananger->Render(m_pDeviceManager, m_pShaderManager, fDeltaTime);

}