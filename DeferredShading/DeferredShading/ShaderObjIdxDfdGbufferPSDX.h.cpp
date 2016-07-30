#include "ShaderObjIdxDfdGbufferPSDX.h"


ShaderObjIdxDfdGbufferPSDX::ShaderObjIdxDfdGbufferPSDX(std::string shaderName, ID3D11Device* deviceDX, ID3DBlob* shaderBuffer) :
	ShaderObjectDX(shaderName, deviceDX, shaderBuffer)
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