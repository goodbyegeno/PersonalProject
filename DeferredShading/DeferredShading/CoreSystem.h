#pragma once
#include "CoreEngineCommon.h"
#include "CustomMatrix.h"
#include "CustomVector.h"
#include "TempTimer.h"
class ICameraBase;
class CoreSystem
{
public:
	CoreSystem();
	virtual ~CoreSystem();

	bool Initialzie();
	bool Reset();

	void PreUpdate();
	void Update();
	void PostUpdate();

	const ORBITMATRIX4x4& GetViewMatrix() const;// { return _cameraObject->GetViewMatrix(); }
	const ORBITMATRIX4x4& GetProjMatrix() const;// { return _cameraObject->GetProjMatrix(); }

private:

	ICameraBase*	_cameraObject;
	TimerObject		_timeObject;

};

extern CoreSystem* coreSystem;