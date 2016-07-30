#include "DeferredShadingMethodDX.h"
#include "CoreEngineCommon.h"
#include "ShaderManager.h"
#include "IShaderObejct.h"
#include "DeviceManager.h"
#include "IGraphicsDevice.h"
#include "CoreSystem.h"
#include "CustomMatrix.h"
#include "CustomVector.h"
#include "ShaderRenderTarget.h"
#include "ShaderRenderTargetDX.h"
#include "IShaderRenderTargetImpl.h"

#include <d3d11_2.h>
#include <DirectXMath.h>
#include <Psapi.h>

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
	_shaderConstVariableBuffer	= nullptr;
	_depthStencilView		= nullptr;
	_renderTargetCount		= 0;
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
}
bool DeferredShadingMethodDX::Reset(DeviceManager* deviceManager, ShaderManager* shaderManager)
{
	_shaderManager = shaderManager;
	IGraphcisDevice* graDevice = deviceManager->GetDevice();
	if (graDevice == nullptr || graDevice->GetMiddlewareType() != CoreEngine::GRAPHICSAPITYPE::DIRECTX11_2)
		return false;

	_device = static_cast<ID3D11Device*>(graDevice->GetBuffer());
	
	_vertexShader			= nullptr;
	_pixelShader			= nullptr;
	_computeShader			= nullptr;
	
	_vertexShaderHash		= 0;
	_pixelShaderHash		= 0;
	_computeShaderHash		= 0;

	SetShader_(shaderManager, _device);
}
bool DeferredShadingMethodDX::SetShader_(ShaderManager* shaderManager, ID3D11Device* deviceDX)
{
	IShaderObject* tempShaderObject = nullptr;
	tempShaderObject = shaderManager->GetShaderObject(_vertexShaderHash);
	if (tempShaderObject == nullptr)
		return false;
	if (tempShaderObject->GetMiddlewareType() != CoreEngine::GRAPHICSAPITYPE::DIRECTX11_2)
		return false;

	_vertexShader = static_cast<ID3D11VertexShader*>(tempShaderObject->GetShader());
	ID3DBlob* vertexShaderBuffer = static_cast<ID3DBlob*>(tempShaderObject->GetBuffer());
	HRESULT resultValue;
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

	CD3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(ShaderConstVariables);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;
	bufferDesc.CPUAccessFlags = 0;

	_device->CreateBuffer(&bufferDesc, 0, &_shaderConstVariableBuffer);
}
bool DeferredShadingMethodDX::InitRenderTargets(ShaderRenderTarget** renderTargets, int renderTargetNum)
{
	if (renderTargetNum < static_cast<int>(INDEXEDDEFERREDSHADINGRT::MAX))
	{
		for (int index = 0; index < renderTargetNum; index++)
		{
			_renderTargets[index] = static_cast<ShaderRenderTargetDX*>(renderTargets[index]->GetData());
			_renderTargetTex[index]		= _renderTargets[index]->GetTexture();
			_shaderRenderView[index]	= _renderTargets[index]->GetShaderResourceView();
			_renderingTargetView[index] = _renderTargets[index]->GetRenderTargetView();
		}
		_renderTargetCount = renderTargetNum;
	}
}

bool DeferredShadingMethodDX::SetCameraMatrix()
{
	const ORBITMATRIX4x4 tempOrbitViewMatrix = coreSystem->GetViewMatrix();
	const ORBITMATRIX4x4 tempOrbitProjMatrix = coreSystem->GetProjMatrix();
	DirectX::XMFLOAT4X4 tempFloat4x4;

	//copy view
	for (int width = 0; width < 4; width++)
	{
		for (int height = 0; height < 4; height++)
		{
			tempFloat4x4.m[width][height] = tempOrbitViewMatrix.m[width][height];
		}
	}
	_shaderConstVariables._viewMatrix = DirectX::XMLoadFloat4x4(&tempFloat4x4);

	//copy proj
	for (int width = 0; width < 4; width++)
	{
		for (int height = 0; height < 4; height++)
		{
			tempFloat4x4.m[width][height] = tempOrbitProjMatrix.m[width][height];
		}
	}
	_shaderConstVariables._projMatrix = DirectX::XMLoadFloat4x4(&tempFloat4x4);

	_shaderConstVariables._viewProjMatrix = DirectX::XMMatrixMultiply(_shaderConstVariables._viewMatrix, _shaderConstVariables._projMatrix);
	return true;
}
bool DeferredShadingMethodDX::SettingShaderOptions()
{
	_deviceContext->VSSetShader(_vertexShader, 0, 0);

	return false;
}
bool DeferredShadingMethodDX::SetConstVariables()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	_deviceContext->Map(_shaderConstVariableBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	ShaderConstVariables* constants = static_cast<ShaderConstVariables*>(mappedResource.pData);

	*constants = _shaderConstVariables;

	_deviceContext->Unmap(_shaderConstVariableBuffer, 0);

	return false;
}
bool DeferredShadingMethodDX::SetRenderTarget()
{
	_deviceContext->OMSetRenderTargets(_renderTargetCount, _renderingTargetView, _depthStencilView);

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