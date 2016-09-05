#include "stdafx.h"
#include "RenderedObjectManager.h"
RenderedObjectManager::RenderedObjectManager(GraphicsSystem* pGraphicSystem)
{
	m_pGraphicSystem = pGraphicSystem;

}
RenderedObjectManager::~RenderedObjectManager()
{

}

bool RenderedObjectManager::Initialize()
{
	return true;
}
bool RenderedObjectManager::Reset()
{
	return true;
}
void RenderedObjectManager::Update(float fDeltaTime)
{

}

void RenderedObjectManager::Render()
{

}