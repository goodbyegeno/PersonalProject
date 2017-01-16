#include "stdafx.h"
#include "ShaderObjIdxDfdGbufferVSDX.h"


ShaderObjIdxDfdGbufferVSDX::ShaderObjIdxDfdGbufferVSDX(std::wstring shaderName, ID3D11Device3* deviceDX, ID3DBlob* shaderBuffer, ID3D11DeviceChild* shaderData) :
	ShaderObjectDX(shaderName, deviceDX, shaderBuffer, shaderData)
{
	ID3D11VertexShader* shader = nullptr;

	HRESULT result = deviceDX->CreateVertexShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), nullptr, &shader);
	if (FAILED(result))
	{
		return;	//should off process
	}
	_shaderData = shader;
}
ShaderObjIdxDfdGbufferVSDX::~ShaderObjIdxDfdGbufferVSDX()
{

}
bool ShaderObjIdxDfdGbufferVSDX::Initialize()
{

	return true;

}
bool ShaderObjIdxDfdGbufferVSDX::Reset() 
{
	return false;
}

