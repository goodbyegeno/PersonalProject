#pragma once

class SceneObject;
class IGraphicsSystemFacade;

class ISceneObjectFactory
{
public:
	ISceneObjectFactory() {};
	virtual ~ISceneObjectFactory() {};

	virtual SceneObject* CreateSceneObject(size_t objectTypeKey, IGraphicsSystemFacade* graphicsSystem) = 0;
};