#include "stdafx.h"
#include "CoreSystem.h"
#include "CameraBase.h"
//for test now. TEST CODE
CoreSystem* coreSystem;

CoreSystem::CoreSystem() :
	_cameraObject(nullptr)
{
	coreSystem = this;
}
CoreSystem::~CoreSystem()
{
	if(_cameraObject)
		delete _cameraObject;
}


bool CoreSystem::Initialzie()
{
	_cameraObject = new CameraBase(this);

	_timeObject.Initialize();
	return true;
}
bool CoreSystem::Reset()
{
	_timeObject.Reset();
	return true;
}

void CoreSystem::PreUpdate()
{
	_timeObject.PreUpdate();

}
void CoreSystem::Update()
{
	float deltaTime = _timeObject.GetDeltaTime();
}
void CoreSystem::PostUpdate()
{

}

const ORBITMATRIX4x4& CoreSystem::GetViewMatrix() const { return _cameraObject->GetViewMatrix(); }
const ORBITMATRIX4x4& CoreSystem::GetProjMatrix() const { return _cameraObject->GetProjMatrix(); }
