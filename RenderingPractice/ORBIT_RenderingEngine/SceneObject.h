#pragma once
#include "RenderedObject.h"
class IRenderableObject;
class SceneObject 
{
public:
	SceneObject(size_t objectID);
	virtual ~SceneObject();
	size_t GetID() { return _objectID; }

	bool IsAwakeable()	{ return _wakeable; }
	bool IsStartable()	{ return _startable; }
	bool IsDeleteable() { return _deleteable; }
	void SetAwakeable()	{ _wakeable = true; }
	void SetStartable()	{ _startable = true; }
	void SetDeleteable() { _deleteable = true; }

	bool IsAwake()						{ return _wake; }
	bool IsStart()						{ return _start; }
	void SetAwake()						{ _wake = true; }
	void SetStart()						{ _start = true; }

	virtual void PreUpdate(float deltaTime) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void PostUpdate(float deltaTime) = 0;

	virtual RenderedObject* GetRenderedObject() { return &_renderedObject; }

private:
	size_t _objectID;
	bool _wakeable;
	bool _startable;
	bool _deleteable;

	bool _wake;
	bool _start;

	RenderedObject _renderedObject;

};