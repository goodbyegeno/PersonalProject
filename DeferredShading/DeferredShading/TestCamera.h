#pragma once
#include "ICameraMovement.h"
class CameraBase;

class TestCamera : public ICameraMovement
{
public:
	TestCamera() = delete;

	TestCamera(CameraBase* cameraBase);
	virtual ~TestCamera();

	virtual void Update(float deltaTime);
private:

	CameraBase* _cameraBase;

};