#include "ShaderObjectDX.h"

ShaderObjectDX::ShaderObjectDX(std::string shaderName, ID3D11Device* deviceDX, ID3DBlob* shaderBuffer) :
	_shaderName(shaderName),
	_shaderData(nullptr),
	_shaderBuffer(shaderBuffer),
	_device(deviceDX),
	_inputLayout(nullptr)
{
	std::hash<std::string> strHash;
	_shaderNameHash = strHash(_shaderName);
}

ShaderObjectDX::~ShaderObjectDX()
{
	//release buffer and data;
}
