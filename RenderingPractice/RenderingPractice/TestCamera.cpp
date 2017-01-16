#include "stdafx.h"
#include "TestCamera.h"
#include "CameraBase.h"
#include "CoreEngineCommon.h"
#include "GraphicsDevice.h"

TestCamera::TestCamera(CameraBase* cameraBase) :
	CameraMovementBase(std::hash<std::wstring>{}(L"TestCamera"))
{
	RenderEngine::GraphicsDevice* graphicsDevice = cameraBase->GetGraphicsDevice();
	_cameraBase = cameraBase;
	_cameraBase->SetProjectionMode(CoreEngine::PROJECTIONMODE::PERSPECTIVE);

	ORBITFLOAT3 vectorTemp(0.0f, 0.0f, 0.0f);
	DirectX::XMFLOAT4X4 xmMatrixTemp;
	DirectX::XMFLOAT3 upFloat, positionFloat, lookAtFloat;

	//left hand coordination

	//position
	vectorTemp._x = 0.0f; 	vectorTemp._y = 0.0f;	vectorTemp._z = 0.0f;
	positionFloat.x = 0.0f; positionFloat.y = 0.0f; positionFloat.z = 0.0f;
	_cameraBase->SetPosition(vectorTemp);
	
	//direction
	vectorTemp._x = -1.0f; 	vectorTemp._y = -1.0f;	vectorTemp._z = -1.0f;
	lookAtFloat.x = -1.0f;	lookAtFloat.y = -1.0f;	lookAtFloat.z = -1.0f;
	_cameraBase->SetDirection(vectorTemp);
	
	//up
	vectorTemp._x = 0.0f; 	vectorTemp._y = 1.0f;	vectorTemp._z = 0.0f;
	upFloat.x = 0.0f;		upFloat.y = 1.0f;		upFloat.z = 0.0f;
	_cameraBase->SetUpVector(vectorTemp);
	
	//right
	vectorTemp._x = 0.0f; 	vectorTemp._y = 0.0f;	vectorTemp._z = 1.0f;
	_cameraBase->SetRightVector(vectorTemp);

	ORBITMATRIX4x4 matrixTemp;
	//TODO SetMatrix;
	//world to view
	DirectX::XMVECTOR up, position, lookAt;
	up			= DirectX::XMLoadFloat3(&upFloat);
	position	= DirectX::XMLoadFloat3(&positionFloat);
	lookAt		= DirectX::XMLoadFloat3(&lookAtFloat);

	DirectX::XMMATRIX viewMatrix;
	viewMatrix = DirectX::XMMatrixLookAtLH(position, lookAt, up);
	xmMatrixTemp = viewMatrix;
	matrixTemp = xmMatrixTemp;
	_cameraBase->SetViewMatrix(matrixTemp);

	//view to proj
	DirectX::XMMATRIX projMatrix;
	projMatrix = DirectX::XMMatrixPerspectiveFovLH(	graphicsDevice->GetFoV(),
													graphicsDevice->GetScreenAspect(), 
													graphicsDevice->GetFrustumNearDefault(),
													graphicsDevice->GetFrustumFarDefault());

	matrixTemp = projMatrix;
	_cameraBase->SetProjMatrix(matrixTemp);

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
