#pragma once
/*
#include <directxmath.h>
#include <d3d11.h>
*/
#include "ICameraMovement.h"
class CoreSystem;

class CameraBase
{
public:
	CameraBase(CoreSystem* coreSystem);
	CameraBase() = delete;

	virtual ~CameraBase();

	bool Initialize();
	bool Reset();

	void Update(float deltaTime);
	
	GetViewMatrix()	{ return _viewMatrix; }
	GetPosition()		{ return _position; }
	GetDirection()	{ return _direction; }
	GetUpVector()		{ return _upVector; }
	GetRightVector()	{ return _rightVector; }
private:

	CoreSystem* _coreSystem;
	_viewMatrix;
	_position;
	_direction;
	_upVector;
	_rightVector;

	ICameraMovement* cameraMovement;
};