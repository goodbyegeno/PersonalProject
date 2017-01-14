#pragma once
/*
#include <directxmath.h>
#include <d3d11_4.h>
*/
#include "CoreEngineCommon.h"
//#include "CameraMovementBase.h"
class CameraMovementBase;
class GraphicsDevice;

class ICameraBase
{
public:
	ICameraBase() {}
	virtual ~ICameraBase() {}

	virtual const ORBITMATRIX4x4& GetViewMatrix() const = 0;
	virtual const ORBITMATRIX4x4& GetProjMatrix() const = 0;
	virtual const ORBITFLOAT3& GetPosition() const = 0;
	virtual const ORBITFLOAT3& GetDirection() const = 0;
	virtual const ORBITFLOAT3& GetUpVector() const = 0;
	virtual const ORBITFLOAT3& GetRightVector() const = 0;
	virtual CoreEngine::PROJECTIONMODE GetProjectionMode() const = 0;
};

class CameraBase : public ICameraBase
{
public:
	CameraBase(RenderEngine::GraphicsDevice* graphicsDevice);
	CameraBase() = delete;
	CameraBase(const CameraBase&) = delete;

	virtual ~CameraBase();

	bool Initialize();
	bool Reset();
	void PreUpdate(float deltaTime);
	void Update(float deltaTime);
	void PostUpdate(float deltaTime);

	virtual const ORBITMATRIX4x4& GetViewMatrix() const		{ return _viewMatrix; }
	virtual const ORBITMATRIX4x4& GetProjMatrix() const		{ return _projectionMatrix; }
	virtual const ORBITFLOAT3& GetPosition() const			{ return _position; }
	virtual const ORBITFLOAT3& GetDirection() const			{ return _direction; }
	virtual const ORBITFLOAT3& GetUpVector() const			{ return _upVector; }
	virtual const ORBITFLOAT3& GetRightVector() const		{ return _rightVector; }
	virtual CoreEngine::PROJECTIONMODE GetProjectionMode()	const { return _projectionMode; }
	
	RenderEngine::GraphicsDevice* GetGraphicsDevice()		{ return _graphicsDevice; }
	void SetCameraMovementBase(size_t cameraMovementBaseHash);		//{ _CameraMovementBase = CameraMovementBase; }
	void AddCameraMovementBase(CameraMovementBase* cameraMovementBase); //{ _CameraMovementBase = CameraMovementBase; }

	void SetViewMatrix(ORBITMATRIX4x4& viewMatrix)			{ _viewMatrix = viewMatrix; }
	void SetProjMatrix(ORBITMATRIX4x4& projectionMatrix)	{ _projectionMatrix = projectionMatrix; }
	void SetPosition(ORBITFLOAT3& position)					{ _position = position; }
	void SetDirection(ORBITFLOAT3& direction)				{ _direction = direction; }
	void SetUpVector(ORBITFLOAT3& upVector)					{ _upVector = upVector; }
	void SetRightVector(ORBITFLOAT3& rightVector)			{ _rightVector = rightVector; }
	void SetProjectionMode(CoreEngine::PROJECTIONMODE projectionMode) { _projectionMode = projectionMode; }

private:

	ORBITMATRIX4x4	_viewMatrix;
	ORBITMATRIX4x4	_projectionMatrix;
	ORBITFLOAT3		_position;
	ORBITFLOAT3		_direction;
	ORBITFLOAT3		_upVector;
	ORBITFLOAT3		_rightVector;
	CoreEngine::PROJECTIONMODE _projectionMode;

	RenderEngine::GraphicsDevice* _graphicsDevice;

	std::unordered_map<size_t, CameraMovementBase*> _cameraMovementBaseMap;
	CameraMovementBase*								_currentCameraMovementBase;

};