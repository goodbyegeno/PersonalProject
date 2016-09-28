#pragma once
#include "SceneObject.h"
class IRenderableObject;

class TestSceneObject : public SceneObject
{
public:
	TestSceneObject(size_t objectID);
	virtual ~TestSceneObject();

	virtual void PreUpdate(float deltaTime);
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
	
	virtual size_t GetID() { return 0; }

private:



};