#include "stdafx.h"
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
#include "IRenderedObject.h"
#include "ModelDynamicData.h"
#include "ModelStaticData.h"
#include "ORBITMesh.h"
#include "ORBITMeshSubset.h"
#include "ORBITMaterial.h"
#include "DXDevice.h"
#include <d3d11_4.h>
#include <DirectXMath.h>
#include <Psapi.h>

DeferredShadingMethodDX::DeferredShadingMethodDX() :
	_device(nullptr),
	_deviceContext(nullptr),
	_inputLayout(nullptr),
	_vertexShader(nullptr),
	_pixelShader(nullptr),
	_computeShader(nullptr),
	_vertexShaderHash(0),
	_pixelShaderHash(0),
	_computeShaderHash(0),
	_psConstVariableBuffer(nullptr),
	_vsConstVariableBuffer(nullptr),
	_depthStencilView(nullptr),
	_renderTargetCount(0),
	_viewPort(nullptr),
	_blendState(nullptr),
	_srDiffuseSlot(0),
	_srSpecularSlot(0),
	_srNormalSlot(0)
{

}
DeferredShadingMethodDX::~DeferredShadingMethodDX()
{

}
bool DeferredShadingMethodDX::Initialize(DeviceManager* deviceManager, ShaderManager* shaderManager)
{
	_shaderManager = shaderManager;
	IGraphcisDevice* graDevice = deviceManager->GetDevice();
	if (graDevice == nullptr || graDevice->GetGraphicsAPIType() != CoreEngine::GRAPHICSAPITYPE::DIRECTX11_2)
		return false;

	_deviceWrapper = static_cast<DXDevice*>(graDevice);

	_device = static_cast<ID3D11Device3*>(graDevice->GetBuffer());
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
	if (graDevice == nullptr || graDevice->GetGraphicsAPIType() != CoreEngine::GRAPHICSAPITYPE::DIRECTX11_2)
		return false;

	_device = static_cast<ID3D11Device3*>(graDevice->GetBuffer());
	
	_vertexShader			= nullptr;
	_pixelShader			= nullptr;
	_computeShader			= nullptr;
	
	_vertexShaderHash		= 0;
	_pixelShaderHash		= 0;
	_computeShaderHash		= 0;

	SetShader_(shaderManager, _device);
}
bool DeferredShadingMethodDX::SetShader_(ShaderManager* shaderManager, ID3D11Device3* deviceDX)
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
	if (tempShaderObject->GetMiddlewareType() != CoreEngine::GRAPHICSAPITYPE::DIRECTX11_2)
		return false;

	_pixelShader = static_cast<ID3D11PixelShader*>(tempShaderObject->GetShader());
	tempShaderObject = nullptr;

	tempShaderObject = shaderManager->GetShaderObject(_computeShaderHash);
	if (tempShaderObject == nullptr)
		return false;
	if (tempShaderObject->GetMiddlewareType() != CoreEngine::GRAPHICSAPITYPE::DIRECTX11_2)
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

	_device->CreateBuffer(&bufferDesc, 0, &_vsConstVariableBuffer);
	
	bufferDesc.ByteWidth = sizeof(ShaderConstVariables);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;
	bufferDesc.CPUAccessFlags = 0;

	_device->CreateBuffer(&bufferDesc, 0, &_psConstVariableBuffer);
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
	_vsConstVariables._viewMatrix = DirectX::XMLoadFloat4x4(&tempFloat4x4);
	_psConstVariables._viewMatrix = _vsConstVariables._viewMatrix;

	//copy proj
	for (int width = 0; width < 4; width++)
	{								
		for (int height = 0; height < 4; height++)
		{
			tempFloat4x4.m[width][height] = tempOrbitProjMatrix.m[width][height];
		}
	}
	_vsConstVariables._projMatrix = DirectX::XMLoadFloat4x4(&tempFloat4x4);
	_psConstVariables._projMatrix = _vsConstVariables._projMatrix;

	_vsConstVariables._viewProjMatrix = DirectX::XMMatrixMultiply(_vsConstVariables._viewMatrix, _vsConstVariables._projMatrix);
	_psConstVariables._viewProjMatrix = _vsConstVariables._viewProjMatrix;
	return true;
}
bool DeferredShadingMethodDX::SettingShaderOptions()
{
	_deviceContext->IASetInputLayout(_inputLayout);

	_deviceContext->VSSetShader(_vertexShader, nullptr, 0);
	_deviceContext->PSSetShader(_pixelShader, nullptr, 0);
	_deviceContext->GSSetShader(nullptr, nullptr, 0);

	_deviceContext->RSSetViewports(1, _viewPort);
	_deviceContext->VSSetConstantBuffers(0, 1, &_vsConstVariableBuffer);
	_deviceContext->PSSetConstantBuffers(0, 1, &_psConstVariableBuffer);
	_deviceContext->OMSetDepthStencilState(_depthStencilState, 0);

	//set shaderResources

	//set samplers

	return false;
}
bool DeferredShadingMethodDX::SetConstVariables()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	_deviceContext->Map(_vsConstVariableBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	ShaderConstVariables* constants = static_cast<ShaderConstVariables*>(mappedResource.pData);
	//set vs const variables 
	_vsConstVariables = ;
	*constants = _vsConstVariables;

	_deviceContext->Unmap(_vsConstVariableBuffer, 0);

	_deviceContext->Map(_psConstVariableBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	ShaderConstVariables* constants = static_cast<ShaderConstVariables*>(mappedResource.pData);
	//set vs const variables 
	_psConstVariables = ;
	*constants = _psConstVariables;

	_deviceContext->Unmap(_psConstVariableBuffer, 0);

	return true;
}
bool DeferredShadingMethodDX::SetRenderTarget()
{
	const float zeros[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	for (int renderTargetIndex = 0; renderTargetIndex < static_cast<int>(INDEXEDDEFERREDSHADINGRT::MAX); renderTargetIndex++)
	{
		_deviceContext->ClearRenderTargetView(_renderingTargetView[renderTargetIndex], zeros);
	}
	_deviceContext->ClearDepthStencilView(_depthStencilView, D3D10_CLEAR_DEPTH, 0.0f, 0);

	_deviceContext->OMSetRenderTargets(_renderTargetCount, _renderingTargetView, _depthStencilView);
	_deviceContext->OMSetBlendState(_blendState, nullptr, 0xFFFFFFFF);

	return true;
}
bool DeferredShadingMethodDX::SetVertexBuffer(ORBITMesh* mesh)
{
	ID3D11Buffer* const* vertexBuffers = mesh->GetVertexBuffersDX11();

	_deviceContext->IASetVertexBuffers(0, mesh->GetVertexBufferCount(), vertexBuffers, mesh->GetStrides(), mesh->GetOffsets());
	_deviceContext->IASetIndexBuffer(mesh->GetIndexBufferDX11(), _dxHelper->GetIndexBufferFormat(mesh->GetIndexBufferFormat()), 0);
	//_deviceWrapper->RenderMesh(meshData[meshIndex]));
}
bool DeferredShadingMethodDX::SetSubsetVBIndicesInfo(const ORBITMeshSubset* subsetData)
{
	_drawVariables.SetIndexData(subsetData->GetIndexCount(), subsetData->GetIndexStart(), subsetData->GetVertexStart());
}
bool DeferredShadingMethodDX::SetMaterial(const ORBITMaterial* material)
{
	ID3D11ShaderResourceView * const diffuseRVDX11		= material->GetDiffuseRVDX11();
	ID3D11ShaderResourceView * const specularRVDX11		= material->GetSpecularRVDX11();
	ID3D11ShaderResourceView * const normalRVDX11		= material->GetNormalRVDX11();

	_deviceContext->PSSetShaderResources(_srDiffuseSlot,	1,	&diffuseRVDX11);
	_deviceContext->PSSetShaderResources(_srSpecularSlot,	1,	&specularRVDX11);
	_deviceContext->PSSetShaderResources(_srNormalSlot,		1,	&normalRVDX11);
}
bool DeferredShadingMethodDX::RenderMesh()
{
	
	//for (int objectsIndex = 0; objectsIndex < renderRequestObjects.size(); objectsIndex++)
	//{
	//	const ModelDynamicData* modelDaynamicData = renderRequestObjects[objectsIndex]->GetModelDynamicData();
	//	const ModelStaticData* modelStaticData	= renderRequestObjects[objectsIndex]->GetModelStaticData(); 

	//	const ORBITMesh* const* meshData = modelStaticData->GetMeshDatas();

	//	DirectX::XMMATRIX worldMatrix = ;

	//	_vsConstVariables._worldMatrix = worldMatrix;
	//	_psConstVariables._worldMatrix = worldMatrix;

	//	SetConstVariables();

	//	for (int meshIndex = 0; meshIndex < modelStaticData->GetMeshCount(); meshIndex++)
	//	{

	//		ID3D11Buffer*  vertexBuffer = static_cast<ID3D11Buffer*>(meshData[meshIndex]->GetVertexBuffer());
	//		ID3D11Buffer* const* ppVertexBuffer = &vertexBuffer;

	//		_deviceContext->IASetVertexBuffers(0, , ppVertexBuffer, , );
	//		_deviceContext->IASetIndexBuffer(meshData[meshIndex]->GetIndexBuffer(), _dxHelper->GetIndexBufferFormat(meshData[meshIndex]->GetIndexBufferFormat()), 0);
	//		//_deviceWrapper->RenderMesh(meshData[meshIndex]));
	//	}

	//}

	_deviceContext->DrawIndexed(_drawVariables.GetIndexCount(), _drawVariables.GetIndexStart(), _drawVariables.GetVertexStart());

	return false;
}



bool DeferredShadingMethodDX::RenderLighting(std::vector<IRenderedObject*>& renderRequestObjects)
{
	for (int objectsIndex = 0; objectsIndex < renderRequestObjects.size(); objectsIndex++)
	{
		renderRequestObjects[objectsIndex];


	}
	return false;
}
bool DeferredShadingMethodDX::ResetRenderTarget()
{
	_deviceContext->OMSetRenderTargets(0, nullptr, nullptr);
}


DeferredShadingMethodDX::DrawVariables::DrawVariables() :
	_indexCount(0),
	_indexStart(0),
	_vertexStart(0)
{

}
DeferredShadingMethodDX::DrawVariables::~DrawVariables()
{

}

void DeferredShadingMethodDX::DrawVariables::SetIndexData(int indexCount, int indexStart, int vertexStart)
{
	_indexCount = indexCount;
	_indexStart = indexStart;
	_vertexStart = vertexStart;

}
