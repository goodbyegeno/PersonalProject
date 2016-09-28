#pragma once
#include "ISceneObjectFactory.h"
class TestSceneObjectFactory : public ISceneObjectFactory
{
public:
	TestSceneObjectFactory();
	virtual ~TestSceneObjectFactory();


	//From ISceneObjectFactory
	virtual SceneObject* CreateSceneObject(size_t objectTypeKey, IGraphicsSystemFacade* graphicsSystem);

};