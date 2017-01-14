#pragma once
#include "IUpdateableObject.h"

class CameraMovementBase
{
public:

	CameraMovementBase(size_t hashCode) : _hashCode(hashCode) {}
	virtual ~CameraMovementBase() {}

	virtual size_t GetHash() { return _hashCode; }

	virtual void PreUpdate(float deltaTime) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void PostUpdate(float deltaTime) = 0;
private:
	size_t _hashCode;

};