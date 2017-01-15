#include "stdafx.h"
#include "ShaderObjIdxDfdGbufferPSDX.h"


ShaderObjIdxDfdGbufferPSDX::ShaderObjIdxDfdGbufferPSDX(std::wstring shaderName, ID3D11Device3* deviceDX, ID3DBlob* shaderBuffer, ID3D11DeviceChild* shaderData) :
	ShaderObjectDX(shaderName, deviceDX, shaderBuffer, shaderData)
{
	ID3D11PixelShader* shader = nullptr;

	HRESULT result = deviceDX->CreatePixelShader(shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), nullptr, &shader);
	if (FAILED(result))
	{
		return;	//should off process
	}
	_shaderData = shader;
}
ShaderObjIdxDfdGbufferPSDX::~ShaderObjIdxDfdGbufferPSDX()
{

}