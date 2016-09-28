#pragma once
#include "RenderEngineCommon.h"
#include <vector>

class ShaderManager;
class DeviceManager;
class RenderingManager;
class IRenderableObject;
class RenderMethod
{
public:
	RenderMethod(std::wstring& methodName) : _methodName(methodName) {}
	RenderMethod(std::wstring&& methodName) : _methodName(methodName) {}
	RenderMethod() = delete;

	virtual ~RenderMethod() {};
	virtual size_t GetHashcode() { return std::hash<std::wstring>{}(_methodName); }

	virtual bool Initialize() = 0;
	virtual bool Reset() = 0;
	virtual void Render(DeviceManager* deviceManager, ShaderManager* shaderManager, std::vector<IRenderableObject*>& renderRequestObjects, float deltaTime) = 0;
	virtual RenderEngine::RENDERINGMODE GetRenderingMode() { return RenderEngine::RENDERINGMODE::FORWARD; }

private:
	std::wstring _methodName;

};