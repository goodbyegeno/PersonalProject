#pragma once
#include "ShaderObjectDX.h"

class ShaderObjIdxDfdGbufferCSDX : public ShaderObjectDX
{
public:
	ShaderObjIdxDfdGbufferCSDX(std::wstring shaderName, ID3D11Device3* deviceDX, ID3DBlob* shaderBuffer, ID3D11DeviceChild* shaderData);
	ShaderObjIdxDfdGbufferCSDX() = delete;
	virtual ~ShaderObjIdxDfdGbufferCSDX();

	virtual RenderEngine::SHADERTYPE GetShaderType() { return RenderEngine::SHADERTYPE::COMPUTESHADER; }

};