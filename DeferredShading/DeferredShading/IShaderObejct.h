#pragma once
#include "RenderEngineCommon.h"
#include "CoreEngineCommon.h"
class IShaderObject
{
public:
	IShaderObject() {};
	virtual ~IShaderObject() {};

	virtual bool Initialize() = 0;
	virtual bool Reset() = 0;
	virtual RenderEngine::GRAPHICSAPITYPE GetMiddlewareType() = 0;
	virtual void* GetShader() = 0;
	virtual void* GetBuffer() = 0;
	virtual size_t GetHashcode() = 0;
	virtual RenderEngine::SHADERTYPE GetShaderType() = 0;
	virtual const std::string& GetName() = 0;

};