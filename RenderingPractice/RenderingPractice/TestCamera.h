#pragma once
#include "CameraMovementBase.h"
class CameraBase;

class TestCamera : public CameraMovementBase
{
public:
	TestCamera() = delete;

	TestCamera(CameraBase* cameraBase);
	virtual ~TestCamera();

	virtual void PreUpdate(float deltaTime);
	virtual void Update(float deltaTime);
	virtual void PostUpdate(float deltaTime);
private:

	CameraBase* _cameraBase;

};