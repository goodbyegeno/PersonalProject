#pragma once
#include "RenderEngineCommon.h"
#include <vector>

class ShaderManager;
class DeviceManager;
class RenderingManager;
class IRenderedObject;
class RenderMethod
{
public:

	RenderMethod() {};
	virtual ~RenderMethod() {};

	virtual bool Initialize() = 0;
	virtual bool Reset() = 0;
	virtual void Render(DeviceManager* deviceManager, ShaderManager* shaderManager, std::vector<IRenderedObject*>& renderRequestObjects, float deltaTime) = 0;
	virtual RenderEngine::RENDERINGMODE GetRenderingMode() { return RenderEngine::RENDERINGMODE::FORWARD; }
};