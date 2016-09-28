#pragma once
#include "IUpdateableObject.h"

class CameraMovementBase
{
public:

	CameraMovementBase() {}
	virtual ~CameraMovementBase() {}

	virtual size_t GetHash() { return _hashCode; }

private:
	size_t _hashCode;

};