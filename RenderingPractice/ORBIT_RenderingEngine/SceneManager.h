#pragma once
#include "IUpdateableObject.h"

class SceneObject;
class IGraphicsSystemFacade;
class ISceneObjectFactory;

class SceneManager : public IUpdateableObject
{
public:
	SceneManager(IGraphicsSystemFacade* graphicsSystem, ISceneObjectFactory* sceneObjectFactory);
	virtual ~SceneManager();

	//TODO: thread safe
	virtual void PreUpdate(float deltaTime);
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	
	// DONT NEED TO BE THREAD SAFE
	virtual void PhaseReady(float deltaTime);
	virtual void PhaseEnd(float deltaTime);

	size_t	CreateSceneObject(size_t objectTypeKey);
	bool	AwakeSceneObject(size_t sceneObjectID);
	bool	StartSceneObject(size_t sceneObjectID);

private:
	std::vector<SceneObject*> _sceneObjectList;
	IGraphicsSystemFacade* _graphicsSystem;
	ISceneObjectFactory* _sceneObjectFactory;

};