#pragma once
#include "CameraMovementBase.h"
class CameraBase;

class TestCamera : public CameraMovementBase
{
public:
	TestCamera() = delete;

	TestCamera(CameraBase* cameraBase);
	virtual ~TestCamera();

	virtual void PreUpdate(float deltaTime) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void PostUpdate(float deltaTime) = 0;
private:

	CameraBase* _cameraBase;

};