#include "stdafx.h"
#include "ShaderObjectDX.h"

ShaderObjectDX::ShaderObjectDX(std::wstring shaderName, ID3D11Device3* deviceDX, ID3DBlob* shaderBuffer, ID3D11DeviceChild* shaderData) :
	_shaderName(shaderName),
	_shaderData(shaderData),
	_shaderBuffer(shaderBuffer),
	_device(deviceDX)
{
	std::hash<std::wstring> strHash;
	_shaderNameHash = strHash(_shaderName);
}

ShaderObjectDX::~ShaderObjectDX()
{
	//release buffer and data;
}
