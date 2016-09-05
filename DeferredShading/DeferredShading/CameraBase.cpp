#include "stdafx.h"
#include "CameraBase.h" 
#include "CoreSystem.h"
CameraBase::CameraBase(CoreSystem* coreSystem) :
	_coreSystem(coreSystem)
{

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
