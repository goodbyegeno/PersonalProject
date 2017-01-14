#include "stdafx.h"
#include "CoreSystem.h"
//#include "CameraBase.h"
#include "IUpdateableObject.h"
#include "IRenderableObject.h"
#include "IRenderableManager.h"
//for test now. TEST CODE

CoreSystem::CoreSystem(CoreSystemInititalData& data) :
	_updateRateType(CoreEngine::UPDATERATETYPE::CUSTOM_FIXED),
	_minDeltaTimePerFrame(0.0f),
	_maxDeltaTimePerFrame(0.0f),
	_updateableObjectGroupList(data.updateableObjectGroupList),
	_renderableObjectGroupList(data.renderableObjectGroupList)
{
	_entityMap.clear();
}
CoreSystem::~CoreSystem()
{
}


bool CoreSystem::Initialize()
{

	if (false == _timeObject.Initialize())
		return false;

	return true;
}
bool CoreSystem::Reset()
{
	_timeObject.Reset();
	return true;
}
void CoreSystem::UpdateMain()
{
	_timeObject.PreUpdate();
	float deltaTime = _timeObject.GetDeltaTime();

	_tickElapsedTime += deltaTime;
	float minDeltaTimePerFrame = _minDeltaTimePerFrame;

	switch (_updateRateType)
	{
	case CoreEngine::UPDATERATETYPE::CUSTOM_DYNAMIC:
	break;
	case CoreEngine::UPDATERATETYPE::CUSTOM_FIXED:
	break;
	case CoreEngine::UPDATERATETYPE::FREE:
		minDeltaTimePerFrame = 0.0f;
	break;
	};

	if (_tickElapsedTime >= _minDeltaTimePerFrame)
	{
		PhaseReady_(deltaTime);

		PreUpdate_(deltaTime);
		Update_(deltaTime);
		PostUpdate_(deltaTime);
		Render_(deltaTime);

		PhaseEnd_(deltaTime);
		_tickElapsedTime = 0.0f;
	}
}
void CoreSystem::PreUpdate_(float deltaTime)
{
	for (int groupIndex = 0; groupIndex < _updateableObjectGroupList.size(); groupIndex++)
	{
		for (int objectIndex = 0; objectIndex < _updateableObjectGroupList[groupIndex].size(); objectIndex++)
		{
			_updateableObjectGroupList[groupIndex][objectIndex]->PreUpdate(deltaTime);
		}
	}
}
void CoreSystem::Update_(float deltaTime)
{
	for (int groupIndex = 0; groupIndex < _updateableObjectGroupList.size(); groupIndex++)
	{
		for (int objectIndex = 0; objectIndex < _updateableObjectGroupList[groupIndex].size(); objectIndex++)
		{
			_updateableObjectGroupList[groupIndex][objectIndex]->Update(deltaTime);
		}
	}
}
void CoreSystem::PostUpdate_(float deltaTime)
{
	for (int groupIndex = 0; groupIndex < _updateableObjectGroupList.size(); groupIndex++)
	{
		for (int objectIndex = 0; objectIndex < _updateableObjectGroupList[groupIndex].size(); objectIndex++)
		{
			_updateableObjectGroupList[groupIndex][objectIndex]->PostUpdate(deltaTime);
		}
	}
}
void CoreSystem::Render_(float deltaTime)
{
	for (int groupIndex = 0; groupIndex < _renderableObjectGroupList.size(); groupIndex++)
	{
		for (int objectIndex = 0; objectIndex < _renderableObjectGroupList[groupIndex].size(); objectIndex++)
		{
			_renderableObjectGroupList[groupIndex][objectIndex]->Render(deltaTime);
		}
	}
}
void CoreSystem::PhaseReady_(float deltaTime)
{
	for (int groupIndex = 0; groupIndex < _updateableObjectGroupList.size(); groupIndex++)
	{
		for (int objectIndex = 0; objectIndex < _updateableObjectGroupList[groupIndex].size(); objectIndex++)
		{
			_updateableObjectGroupList[groupIndex][objectIndex]->PhaseReady(deltaTime);
		}
	}
}
void CoreSystem::PhaseEnd_(float deltaTime)
{
	for (int groupIndex = 0; groupIndex < _updateableObjectGroupList.size(); groupIndex++)
	{
		for (int objectIndex = 0; objectIndex < _updateableObjectGroupList[groupIndex].size(); objectIndex++)
		{
			_updateableObjectGroupList[groupIndex][objectIndex]->PhaseEnd(deltaTime);
		}
	}
}
/*
void CoreSystem::AddUpdateableObject(IUpdateableObject* updateableObject, UINT group)
{
	size_t addGroupCount = static_cast<size_t>(group) - _updateableObjectGroupList.size();
	for (size_t addedCount = 0; addedCount < addGroupCount; addedCount++)
	{
		_updateableObjectGroupList.push_back(std::vector<IUpdateableObject*>());
	}

	_updateableObjectGroupList[group].push_back(updateableObject);
}
*/
SystemConfigureEntity*	CoreSystem::GetConfigValue(size_t hashEntity)
{
	std::unordered_map<size_t, SystemConfigureEntity*>::iterator itor = _entityMap.find(hashEntity);
	if (itor != _entityMap.end())
	{
		return itor->second;
	}
	return nullptr;

}
//
//const ORBITMATRIX4x4& CoreSystem::GetViewMatrix() const { return _cameraObject->GetViewMatrix(); }
//const ORBITMATRIX4x4& CoreSystem::GetProjMatrix() const { return _cameraObject->GetProjMatrix(); }
