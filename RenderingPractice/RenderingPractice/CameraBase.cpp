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

}

void CameraBase::Update(float deltaTime)
{

}
void CameraBase::PostUpdate(float deltaTime)
{

}

void CameraBase::SetCameraMovementBase(size_t cameraMovementBaseHash)
{
	std::unordered_map<size_t, CameraMovementBase*>::iterator cameraMapItor;
	
	cameraMapItor = _cameraMovementBaseMap.find(cameraMovementBaseHash);

	if (cameraMapItor != _cameraMovementBaseMap.end())
		_currentCameraMovementBase = cameraMapItor->second;
}

void CameraBase::AddCameraMovementBase(CameraMovementBase* cameraMovementBase)
{
	_cameraMovementBaseMap.insert(std::unordered_map<size_t, CameraMovementBase*>::value_type(cameraMovementBase->GetHash(), cameraMovementBase));
}
