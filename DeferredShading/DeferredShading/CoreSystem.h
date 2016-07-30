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

	CoreEngine::GRAPHICSAPITYPE GetCurrentGraphicsAPIType() { return _currentGraphicsAPIType; }

	const ORBITMATRIX4x4& GetViewMatrix() { return _cameraObject->GetViewMatrix(); }
	const ORBITMATRIX4x4& GetProjMatrix() { return _cameraObject->GetProjMatrix(); }

	
private:

	CoreEngine::GRAPHICSAPITYPE SetCurrentGraphicsAPIType_(CoreEngine::GRAPHICSAPITYPE graphicsAPIType) { _currentGraphicsAPIType = graphicsAPIType; }
	CoreEngine::GRAPHICSAPITYPE _currentGraphicsAPIType;

	ICameraBase*	_cameraObject;
	TimerObject		_timeObject;
};

CoreSystem* coreSystem;