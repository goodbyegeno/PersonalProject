#include "stdafx.h"
#include "TestCamera.h"
#include "CameraBase.h"
#include "CoreEngineCommon.h"
#include <string>
TestCamera::TestCamera(CameraBase* cameraBase) :
	CameraMovementBase(std::hash<std::wstring>{}(L"TestCamera"))
{
	_cameraBase = cameraBase;
	_cameraBase->SetProjectionMode(CoreEngine::PROJECTIONMODE::PERSPECTIVE);

	ORBITFLOAT3 vectorTemp(0.0f, 0.0f, 0.0f);
	ORBITMATRIX4x4 matrixTemp;

	_cameraBase->SetViewMatrix(matrixTemp);
	_cameraBase->SetProjMatrix(matrixTemp);
	
	vectorTemp._x = 0.0f; 	vectorTemp._y = 0.0f;	vectorTemp._z = 0.0f;
	_cameraBase->SetPosition(vectorTemp);
	
	vectorTemp._x = -1.0f; 	vectorTemp._y = -1.0f;	vectorTemp._z = -1.0f;
	_cameraBase->SetDirection(vectorTemp);
	
	vectorTemp._x = 0.0f; 	vectorTemp._y = 1.0f;	vectorTemp._z = 0.0f;
	_cameraBase->SetUpVector(vectorTemp);
	
	vectorTemp._x = 0.0f; 	vectorTemp._y = 0.0f;	vectorTemp._z = 1.0f;
	_cameraBase->SetRightVector(vectorTemp);

	_cameraBase->SetProjectionMode(CoreEngine::PROJECTIONMODE::PERSPECTIVE);
}
TestCamera::~TestCamera()
{

}
void TestCamera::Update(float deltaTime)
{

}

void TestCamera::PreUpdate(float deltaTime)
{

}
void TestCamera::PostUpdate(float deltaTime)
{

}
