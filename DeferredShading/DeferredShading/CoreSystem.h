#pragma once
#include "CoreEngineCommon.h"
class CoreSystem
{
public:
	CoreSystem();
	virtual ~CoreSystem();

	CoreEngine::GRAPHICSAPITYPE GetCurrentGraphicsAPIType() { return _currentGraphicsAPIType; }
private:

	CoreEngine::GRAPHICSAPITYPE SetCurrentGraphicsAPIType_(CoreEngine::GRAPHICSAPITYPE graphicsAPIType) { _currentGraphicsAPIType = graphicsAPIType; }
	CoreEngine::GRAPHICSAPITYPE _currentGraphicsAPIType;

};