#include "stdafx.h"
#include "ShaderObjIdxDfdGbufferCSDX.h"


ShaderObjIdxDfdGbufferCSDX::ShaderObjIdxDfdGbufferCSDX(std::wstring shaderName, ID3D11Device3* deviceDX, ID3DBlob* shaderBuffer, ID3D11DeviceChild* shaderData) :
	ShaderObjectDX(shaderName, deviceDX, shaderBuffer, shaderData)
{
	ID3D11ComputeShader* shader = nullptr;

	HRESULT result = deviceDX->CreateComputeShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), nullptr, &shader);
	if (FAILED(result))
	{
		return;	//should off process
	}
	_shaderData = shader;
}
ShaderObjIdxDfdGbufferCSDX::~ShaderObjIdxDfdGbufferCSDX()
{

}