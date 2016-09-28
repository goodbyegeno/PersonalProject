#include "stdafx.h"
#include "SceneObject.h"

SceneObject::SceneObject(size_t objectID):
	_objectID(objectID),
	_wakeable(false),
	_startable(false),
	_deleteable(false),
	_wake(false),
	_start(false)
{
}
SceneObject::~SceneObject()
{
}