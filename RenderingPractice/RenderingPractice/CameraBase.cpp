#include "stdafx.h"
#include "CameraBase.h" 
#include "CoreSystem.h"
CameraBase::CameraBase(CoreSystem* coreSystem) :
	_coreSystem(coreSystem),
	_currentCameraMovementBase(nullptr)
{
	_cameraMovementBaseMap.clear();
	_cameraMovementBaseMap.reserve(3);
}
CameraBase::~CameraBase()
{

}

bool CameraBase::Initialize()
{
	return true;
}
bool CameraBase::Reset()
{
	return true;
}
void CameraBase::PreUpdate(float deltaTime)
{
	if (_currentCameraMovementBase)
		_currentCameraMovementBase->PreUpdate(deltaTime);
}

void CameraBase::Update(float deltaTime)
{
	if (_currentCameraMovementBase)
		_currentCameraMovementBase->Update(deltaTime);
}
void CameraBase::PostUpdate(float deltaTime)
{
	if (_currentCameraMovementBase)
		_currentCameraMovementBase->PostUpdate(deltaTime);
}

void CameraBase::SetCameraMovementBase(size_t cameraMovementBaseHash)
{
	std::unordered_map<size_t, CameraMovementBase*>::iterator cameraMapItor;
	
	cameraMapItor = _cameraMovementBaseMap.find(cameraMovementBaseHash);

	if (_cameraMovementBaseMap.end() != cameraMapItor)
		_currentCameraMovementBase = cameraMapItor->second;
}

void CameraBase::AddCameraMovementBase(CameraMovementBase* cameraMovementBase)
{
	_cameraMovementBaseMap.insert(std::unordered_map<size_t, CameraMovementBase*>::value_type(cameraMovementBase->GetHash(), cameraMovementBase));
}
