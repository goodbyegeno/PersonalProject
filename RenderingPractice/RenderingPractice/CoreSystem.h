#pragma once
#include "CoreEngineCommon.h"
#include "CustomMatrix.h"
#include "CustomVector.h"
#include "TempTimer.h"
#include <vector>
#include <unordered_map>
class CameraBase;
class ICameraBase;
class CameraMovementBase;
class IUpdateableObject;
class IRenderableManager;
class SystemConfigureEntity;

class CoreSystem
{
public:
	struct CoreSystemInititalData
	{
	public:
		std::vector<std::vector<IUpdateableObject*>> updateableObjectGroupList;
		std::vector<std::vector<IRenderableManager*>> renderableObjectGroupList;
	};

	CoreSystem(CoreSystemInititalData& data);
	CoreSystem() = delete;
	CoreSystem(const CoreSystem&) = delete;
	virtual ~CoreSystem();

	bool Initialize();
	bool Reset();

	void CoreSystem::UpdateMain();

	const ORBITMATRIX4x4& GetViewMatrix() const;// { return _cameraObject->GetViewMatrix(); }
	const ORBITMATRIX4x4& GetProjMatrix() const;// { return _cameraObject->GetProjMatrix(); }

	//void AddUpdateableObject(IUpdateableObject* updateableObject, UINT group);

	void SetCameraMovement(size_t cameraMovementBaseHash);
	void AddCameraMovement(CameraMovementBase* cameraMovement);
	CameraBase* GetCamera() { return _cameraObject; }
	void SetUpdateRateType(CoreEngine::UPDATERATETYPE updateRateType) { _updateRateType = updateRateType; }
	void SetTimeWindowPerFrame(float minTime, float maxTile) { _minDeltaTimePerFrame = minTime; _maxDeltaTimePerFrame = maxTile; }
	std::unordered_map<size_t, SystemConfigureEntity*>* GetConfigEntityMap() { return &_entityMap; }
	SystemConfigureEntity*	GetConfigValue(size_t hashEntity);

private:
	void PhaseReady_(float deltaTime);

	void PreUpdate_(float deltaTime);
	void Update_(float deltaTime);
	void PostUpdate_(float deltaTime);
	void Render_(float deltaTime);

	void PhaseEnd_(float deltaTime);

	CoreEngine::UPDATERATETYPE _updateRateType;
	float			_tickElapsedTime;
	float			_minDeltaTimePerFrame;
	float			_maxDeltaTimePerFrame;
	CameraBase*		_cameraObject;
	TimerObject		_timeObject;
	std::vector<std::vector<IUpdateableObject*>> _updateableObjectGroupList;
	std::vector<std::vector<IRenderableManager*>> _renderableObjectGroupList;
	//TODO: NeedConfigManager?
	std::unordered_map<size_t, SystemConfigureEntity*> _entityMap;

};

extern CoreSystem* coreSystem;