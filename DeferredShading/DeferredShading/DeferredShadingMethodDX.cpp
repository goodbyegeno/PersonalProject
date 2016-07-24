#include "DeferredShadingMethodDX.h"
#include "CoreEngineCommon.h"
#include "ShaderManager.h"
#include "IShaderObejct.h"
#include "DeviceManager.h"
#include "IGraphicsDevice.h"
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

DeferredShadingMethodDX::DeferredShadingMethodDX()
{
	_device					= nullptr;
	_deviceContext			= nullptr;

	_vertexShader			= nullptr;
	_pixelShader			= nullptr;
	_computeShader			= nullptr;
	_vertexShaderHash		= 0;
	_pixelShaderHash		= 0;
	_computeShaderHash		= 0;

}
DeferredShadingMethodDX::~DeferredShadingMethodDX()
{

}
bool DeferredShadingMethodDX::Initialize(DeviceManager* deviceManager, ShaderManager* shaderManager)
{
	_shaderManager = shaderManager;
	IGraphcisDevice* graDevice = deviceManager->GetDevice();
	if (graDevice == nullptr || graDevice->GetMiddlewareType() != CoreEngine::GRAPHICSAPITYPE::DIRECTX)
		return false;

	_device = static_cast<ID3D11Device*>(graDevice->GetBuffer());
	if (_device == nullptr)
	{
		return false;
	}
	_deviceContext			= nullptr;
	
	_vertexShader			= nullptr;
	_pixelShader			= nullptr;
	_computeShader			= nullptr;
	
	_vertexShaderHash		= 0;
	_pixelShaderHash		= 0;
	_computeShaderHash		= 0;

	if (SetShader_(shaderManager, _device) == false)
		return false;

	XMMATRIX matTest, matTest2;
	matTest = matTest2;
	XMFLOAT4X4 mat1, mat2;
	mat1 = mat2;



}
bool DeferredShadingMethodDX::Reset(DeviceManager* deviceManager, ShaderManager* shaderManager)
{
	_shaderManager = shaderManager;
	IGraphcisDevice* graDevice = deviceManager->GetDevice();
	if (graDevice == nullptr || graDevice->GetMiddlewareType() != CoreEngine::GRAPHICSAPITYPE::DIRECTX)
		return false;

	_device = static_cast<ID3D11Device*>(graDevice->GetBuffer());
	
	_vertexShader			= nullptr;
	_pixelShader			= nullptr;
	_computeShader			= nullptr;
	
	_vertexShaderHash		= 0;
	_pixelShaderHash		= 0;
	_computeShaderHash	= 0;

	SetShader_(shaderManager, _device);
}
bool DeferredShadingMethodDX::SetShader_(ShaderManager* shaderManager, ID3D11Device* deviceDX)
{
	IShaderObject* tempShaderObject = nullptr;
	tempShaderObject = shaderManager->GetShaderObject(_vertexShaderHash);
	if (tempShaderObject == nullptr)
		return false;
	if (tempShaderObject->GetMiddlewareType() != CoreEngine::GRAPHICSAPITYPE::DIRECTX)
		return false;

	_vertexShader = static_cast<ID3D11VertexShader*>(tempShaderObject->GetShader());
	ID3DBlob* vertexShaderBuffer = static_cast<ID3DBlob*>(tempShaderObject->GetBuffer());
	HRESULT resultValue;
	D3D11_INPUT_ELEMENT_DESC polygonLayout[4];
	UINT numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);
	polygonLayout[0].AlignedByteOffset;
	polygonLayout[0].Format;
	polygonLayout[0].InputSlot;
	polygonLayout[0].InputSlotClass;
	polygonLayout[0].InstanceDataStepRate;
	polygonLayout[0].SemanticIndex;
	polygonLayout[0].SemanticName =;

	resultValue = deviceDX->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), &_inputLayout);

	if (FAILED(resultValue))
	{
		return false;
	}
	tempShaderObject = nullptr;

	tempShaderObject = shaderManager->GetShaderObject(_pixelShaderHash);
	if (tempShaderObject == nullptr)
		return false;
	if (tempShaderObject->GetMiddlewareType() != CoreEngine::GRAPHICSAPITYPE::DIRECTX)
		return false;

	_pixelShader = static_cast<ID3D11PixelShader*>(tempShaderObject->GetShader());
	tempShaderObject = nullptr;

	tempShaderObject = shaderManager->GetShaderObject(_computeShaderHash);
	if (tempShaderObject == nullptr)
		return false;
	if (tempShaderObject->GetMiddlewareType() != CoreEngine::GRAPHICSAPITYPE::DIRECTX)
		return false;

	_computeShader = static_cast<ID3D11ComputeShader*>(tempShaderObject->GetShader());
	tempShaderObject = nullptr;
}
bool DeferredShadingMethodDX::SetMatrix()
{
	return false;
}
bool DeferredShadingMethodDX::SetShader()
{
	return false;
}
bool DeferredShadingMethodDX::SetConstVariables()
{
	return false;
}
bool DeferredShadingMethodDX::SetRenderTarget()
{
	return false;
}
bool DeferredShadingMethodDX::RenderMesh()
{
	return false;
}
bool DeferredShadingMethodDX::RenderLighting()
{
	return false;
}