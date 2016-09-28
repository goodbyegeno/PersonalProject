#pragma once
#include "ShaderObjectDX.h"

class ShaderObjIdxDfdGbufferPSDX : public ShaderObjectDX
{
public:
	ShaderObjIdxDfdGbufferPSDX(std::string shaderName, ID3D11Device* deviceDX, ID3DBlob* shaderBuffer);
	ShaderObjIdxDfdGbufferPSDX() = delete;
	virtual ~ShaderObjIdxDfdGbufferPSDX();

};