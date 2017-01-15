#pragma once
#include "ShaderObjectDX.h"

class ShaderObjIdxDfdGbufferPSDX : public ShaderObjectDX
{
public:
	ShaderObjIdxDfdGbufferPSDX(std::wstring shaderName, ID3D11Device3* deviceDX, ID3DBlob* shaderBuffer, ID3D11DeviceChild* shaderData);
	ShaderObjIdxDfdGbufferPSDX() = delete;
	virtual ~ShaderObjIdxDfdGbufferPSDX();

};