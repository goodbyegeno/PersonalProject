#include "stdafx.h"
#include "SceneManager.h"
#include "SceneObject.h"
#include "IGraphicsSystemFacade.h"
#include "ISceneObjectFactory.h"
#include "RenderedObject.h"
SceneManager::SceneManager(IGraphicsSystemFacade* graphicsSystem, ISceneObjectFactory* sceneObjectFactory) :
	_graphicsSystem(graphicsSystem),
	_sceneObjectFactory(sceneObjectFactory)
{
}
SceneManager::~SceneManager()
{
}
void SceneManager::PhaseReady(float deltaTime)
{
	for (size_t sceneIndex = 0; sceneIndex < _sceneObjectList.size(); sceneIndex++)
	{
		if (_sceneObjectList[sceneIndex]->IsAwakeable())
			_sceneObjectList[sceneIndex]->SetAwake();

		if (_sceneObjectList[sceneIndex]->IsStartable())
			_sceneObjectList[sceneIndex]->SetStart();
	}
}

void SceneManager::PreUpdate(float deltaTime)
{
	for (size_t sceneIndex = 0; sceneIndex < _sceneObjectList.size(); sceneIndex++)
		_sceneObjectList[sceneIndex]->PreUpdate(deltaTime);
}

void SceneManager::Update(float deltaTime)
{
	for (size_t sceneIndex = 0; sceneIndex < _sceneObjectList.size(); sceneIndex++)
		_sceneObjectList[sceneIndex]->Update(deltaTime);
}

void SceneManager::PostUpdate(float deltaTime)
{
	//TODO: make thid method to thread safe and parallel
	for (size_t sceneIndex = 0; sceneIndex < _sceneObjectList.size(); sceneIndex++)
	{
		_sceneObjectList[sceneIndex]->PostUpdate(deltaTime);
		//TODO: NEED TO ADD SCENE MANAGEMENT. LIKE OCCLUSION

		//TEST: render all
		_graphicsSystem->AddRenderingRequest(_sceneObjectList[sceneIndex]->GetRenderedObject());
	}
}
void SceneManager::PhaseEnd(float deltaTime)
{
	//UNDONE
	for (int sceneIndex = static_cast<int>(_sceneObjectList.size()) - 1; sceneIndex >= 0; sceneIndex--)
	{
		if (_sceneObjectList[sceneIndex]->IsDeleteable())
		{

		}
	}
}
size_t	SceneManager::CreateSceneObject(size_t objectTypeKey)
{
	_sceneObjectList.push_back(_sceneObjectFactory->CreateSceneObject(objectTypeKey, _graphicsSystem));
	return _sceneObjectList.back()->GetID();
}

bool	SceneManager::AwakeSceneObject(size_t sceneObjectID)
{
	for (size_t sceneIndex = 0; sceneIndex < _sceneObjectList.size(); sceneIndex++)
	{
		if (_sceneObjectList[sceneIndex]->GetID() == sceneObjectID)
		{
			_sceneObjectList[sceneIndex]->SetAwakeable();
			return true;
		}
	}

	return false;
}

bool	SceneManager::StartSceneObject(size_t sceneObjectID)
{
	for (size_t sceneIndex = 0; sceneIndex < _sceneObjectList.size(); sceneIndex++)
	{
		if (_sceneObjectList[sceneIndex]->GetID() == sceneObjectID)
		{
			_sceneObjectList[sceneIndex]->SetStartable();
			return true;
		}
	}
	return false;
}