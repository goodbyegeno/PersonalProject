#pragma once
#include "ShaderObjectDX.h"

class ShaderObjIdxDfdGbufferCSDX : public ShaderObjectDX
{
public:
	ShaderObjIdxDfdGbufferCSDX(std::string shaderName, ID3D11Device* deviceDX, ID3DBlob* shaderBuffer);
	ShaderObjIdxDfdGbufferCSDX() = delete;
	virtual ~ShaderObjIdxDfdGbufferCSDX();

	virtual RenderEngine::SHADERTYPE GetShaderType() { return RenderEngine::SHADERTYPE::COMPUTESHADER; }

};