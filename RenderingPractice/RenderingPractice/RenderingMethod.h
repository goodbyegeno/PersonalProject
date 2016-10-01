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
	RenderMethod(size_t methodHash) : _methodHash(methodHash) {}
	RenderMethod() = delete;

	virtual ~RenderMethod() {};
	virtual size_t GetHashcode() { return _methodHash; }

	virtual bool Initialize() = 0;
	virtual bool Reset() = 0;
	virtual void Render(DeviceManager* deviceManager, ShaderManager* shaderManager, std::vector<IRenderableObject*>& renderRequestObjects, float deltaTime) = 0;
	//virtual RenderEngine::RENDERINGMODE GetRenderingMode() { return RenderEngine::RENDERINGMODE::FORWARD; }
private:
	size_t _methodHash;

};