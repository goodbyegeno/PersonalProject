#pragma once
#include "RenderEngineCommon.h"
class IShaderObject
{
public:
	IShaderObject() {};
	virtual ~IShaderObject() = 0;

	virtual RenderEngine::MIDDLEWARETYPE GetMiddlewareType() = 0;
	virtual void* GetShader() = 0;
	virtual void* GetBuffer() = 0;
	virtual size_t GetHashcode() = 0;

};