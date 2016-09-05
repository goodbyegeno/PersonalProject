#include "stdafx.h"
#include "RenderedObjectManager.h"
RenderedObjectManager::RenderedObjectManager(GraphicsSystem* graphicSystem)
{
	_graphicSystem = graphicSystem;

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
void RenderedObjectManager::Update(float deltaTime)
{

}

void RenderedObjectManager::Render()
{

}