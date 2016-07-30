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
	if (false == InitInputLayout_)
		return false;


	return true;

}
bool ShaderObjIdxDfdGbufferVSDX::Reset() 
{
	return false;
}

bool ShaderObjIdxDfdGbufferVSDX::InitInputLayout_()
{
	HRESULT reuslt;

	D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
	UINT numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	polygonLayout[0].SemanticName = "position";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "normal";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = 12;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	polygonLayout[2].SemanticName = "texcoord";
	polygonLayout[2].SemanticIndex = 0;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[2].InputSlot = 0;
	polygonLayout[2].AlignedByteOffset = 24;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[2].InstanceDataStepRate = 0;

	reuslt = _device->CreateInputLayout(polygonLayout, numElements, _shaderBuffer->GetBufferPointer(),
		_shaderBuffer->GetBufferSize(), &_inputLayout);

	if (FAILED(reuslt))
	{
		return false;
	}
	return true;

}