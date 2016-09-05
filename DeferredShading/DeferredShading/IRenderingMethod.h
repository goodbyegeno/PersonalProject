#pragma once
#include "RenderEngineCommon.h"
#include <vector>

class ShaderManager;
class DeviceManager;
class RenderingManager;
class IRenderedObject;
class IRenderMethod
{
public:

	IRenderMethod() {};
	virtual ~IRenderMethod() = 0;

	virtual bool Initialize() = 0;
	virtual bool Reset() = 0;
	virtual void Render(DeviceManager* deviceManager, ShaderManager* shaderManager, std::vector<IRenderedObject*>& renderRequestObjects, float deltaTime) = 0;
	virtual RenderEngine::RENDERINGMODE GetRenderingMode() = 0;
};