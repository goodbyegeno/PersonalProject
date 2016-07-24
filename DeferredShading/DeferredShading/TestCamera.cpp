#include "TestCamera.h"
#include "CameraBase.h"
#include "CoreEngineCommon.h"
TestCamera::TestCamera(CameraBase* cameraBase)
{

	_cameraBase = cameraBase;
	_cameraBase->SetProjectionMode(CoreEngine::PROJECTIONMODE::PERSPECTIVE);

	_cameraBase->SetViewMatrix();
	_cameraBase->SetProjMatrix();
	_cameraBase->SetPosition();
	_cameraBase->SetDirection();
	_cameraBase->SetUpVector();
	_cameraBase->SetRightVector();
	_cameraBase->SetProjectionMode();
}
TestCamera::~TestCamera()
{

}
void TestCamera::Update(float deltaTime)
{

}
