#include "ShaderObjectDX.h"

ShaderObjectDX::ShaderObjectDX(std::string shaderName, ID3D11Device3* deviceDX, ID3DBlob* shaderBuffer, ID3D11Device3Child* shaderData) :
	_shaderName(shaderName),
	_shaderData(shaderData),
	_shaderBuffer(shaderBuffer),
	_device(deviceDX)
{
	std::hash<std::string> strHash;
	_shaderNameHash = strHash(_shaderName);
}

ShaderObjectDX::~ShaderObjectDX()
{
	//release buffer and data;
}
