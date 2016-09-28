#include "ShaderObjIdxDfdGbufferCSDX.h"


ShaderObjIdxDfdGbufferCSDX::ShaderObjIdxDfdGbufferCSDX(std::string shaderName, ID3D11Device* deviceDX, ID3DBlob* shaderBuffer) :
	ShaderObjectDX(shaderName, deviceDX, shaderBuffer)
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