#pragma once
#include "RenderEngineCommon.h"
class ShaderManager;
class DeviceManager;
class RenderingManager;
#include <vector>
class IRenderMethod
{
public:

	IRenderMethod() {};
	virtual ~IRenderMethod() = 0;

	virtual bool Initialize() = 0;
	virtual bool Reset() = 0;
	virtual void Render(DeviceManager* pDeviceManager, ShaderManager* pShaderManager, std::vector<IRenderedObject>* lstRederRequestObject, float fDeltaTime) = 0;
	virtual RenderEngine::RenderingMode GetRenderingMode() = 0;
};