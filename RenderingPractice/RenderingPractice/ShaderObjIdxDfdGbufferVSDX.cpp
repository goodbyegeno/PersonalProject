#include "ShaderObjIdxDfdGbufferVSDX.h"


ShaderObjIdxDfdGbufferVSDX::ShaderObjIdxDfdGbufferVSDX(std::string shaderName, ID3D11Device* deviceDX, ID3DBlob* shaderBuffer) :
	ShaderObjectDX(shaderName, deviceDX, shaderBuffer)
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

