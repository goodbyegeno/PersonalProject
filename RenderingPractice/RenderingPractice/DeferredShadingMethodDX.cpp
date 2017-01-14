#include "stdafx.h"
#include "DeferredShadingMethodDX.h"
#include "CoreEngineCommon.h"
#include "ShaderManager.h"
#include "IShaderObejct.h"
#include "DeviceManager.h"
#include "GraphicsDevice.h"
#include "CoreSystem.h"
#include "CameraBase.h"
#include "ShaderRenderTarget.h"
#include "ShaderRenderTargetDX.h"
#include "IShaderRenderTargetImpl.h"
#include "IRenderableObject.h"
#include "ModelDynamicData.h"
#include "ModelStaticData.h"
#include "ORBITMesh.h"
#include "ORBITMeshSubset.h"
#include "ORBITMaterial.h"
#include "DXDevice11_4.h"
#include "DXHelper11.h"
#include "RenderingSingletonManager.h"
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <cstring>

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
	GraphicsDevice* graDevice = deviceManager->GetDevice();
	if (nullptr == graDevice || RenderEngine::GRAPHICSAPITYPE::DIRECTX11_4 != graDevice->GetGraphicsAPIType())
		return false;

	_deviceWrapper = static_cast<DXDevice11_4*>(graDevice);

	_device = static_cast<ID3D11Device3*>(graDevice->GetBuffer());
	if (_device == nullptr)
		return false;

	_deviceContext			= nullptr;
	
	_vertexShader			= nullptr;
	_pixelShader			= nullptr;
	_computeShader			= nullptr;
	
	_vertexShaderHash		= 0;
	_pixelShaderHash		= 0;
	_computeShaderHash		= 0;

	if (LoadShader_() == false)
		return false;

	return true;
}
bool DeferredShadingMethodDX::Reset(DeviceManager* deviceManager, ShaderManager* shaderManager)
{
	_shaderManager = shaderManager;
	GraphicsDevice* graDevice = deviceManager->GetDevice();
	if (nullptr == graDevice || RenderEngine::GRAPHICSAPITYPE::DIRECTX11_4 != graDevice->GetGraphicsAPIType())
		return false;

	/*
	_device = static_cast<ID3D11Device3*>(graDevice->GetBuffer());
	
	_vertexShader			= nullptr;
	_pixelShader			= nullptr;
	_computeShader			= nullptr;
	
	_vertexShaderHash		= 0;
	_pixelShaderHash		= 0;
	_computeShaderHash		= 0;

	SetShader_(shaderManager, _device);
	*/
	return true;
}
bool DeferredShadingMethodDX::SetShader_(ID3D11Device3* deviceDX, ID3DBlob* psShaderBuffer, ID3DBlob* vsShaderBuffer, ID3DBlob* csShaderBuffer)
{
	ID3DBlob* vertexShaderBuffer = vsShaderBuffer;
	HRESULT resultValue;
	
	resultValue = deviceDX->CreateVertexShader(vsShaderBuffer->GetBufferPointer(), vsShaderBuffer->GetBufferSize(), NULL, &_vertexShader);
	if (FAILED(resultValue))
		return false;
	
	D3D11_INPUT_ELEMENT_DESC polygonLayout[3];
	UINT numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "NORMAL";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = 12;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	polygonLayout[2].SemanticName = "TEXCOORD";
	polygonLayout[2].SemanticIndex = 0;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[2].InputSlot = 0;
	polygonLayout[2].AlignedByteOffset = 24;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[2].InstanceDataStepRate = 0;

	resultValue = deviceDX->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), &_inputLayout);
	if (FAILED(resultValue))
		return false;

	resultValue = deviceDX->CreatePixelShader(psShaderBuffer->GetBufferPointer(), psShaderBuffer->GetBufferSize(), NULL, &_pixelShader);
	if (FAILED(resultValue))
		return false;

	resultValue = deviceDX->CreateComputeShader(csShaderBuffer->GetBufferPointer(), csShaderBuffer->GetBufferSize(), NULL, &_computeShader);
	if (FAILED(resultValue))
		return false;

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

	return true;
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

	return true;
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

	ShaderConstVariables* constantsVS = static_cast<ShaderConstVariables*>(mappedResource.pData);
	//set vs const variables
	*constantsVS = _vsConstVariables;

	_deviceContext->Unmap(_vsConstVariableBuffer, 0);

	_deviceContext->Map(_psConstVariableBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	ShaderConstVariables* constantsPS = static_cast<ShaderConstVariables*>(mappedResource.pData);
	//set vs const variables 
	*constantsPS = _psConstVariables;

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
bool DeferredShadingMethodDX::SetVertexBuffer(const ORBITMesh* mesh) const
{
	ID3D11Buffer* vertexBuffers = mesh->GetVertexBuffersDX11();

	_deviceContext->IASetVertexBuffers(0, mesh->GetVertexBufferCount(), &vertexBuffers, mesh->GetStrides(), mesh->GetOffsets());
	_deviceContext->IASetIndexBuffer(mesh->GetIndexBufferDX11(), RenderingSingletonManager::GetInstance()->GetDXHelper11()->GetIndexBufferFormat(mesh->GetIndexBufferFormat()), 0);
	//_deviceWrapper->RenderMesh(meshData[meshIndex]));

	return true;
}
bool DeferredShadingMethodDX::SetSubsetVBIndicesInfo(const ORBITMeshSubset* subsetData)
{
	_drawVariables.SetIndexData(subsetData->GetIndexCount(), subsetData->GetIndexStart(), subsetData->GetVertexStart());
	return true;

}
bool DeferredShadingMethodDX::SetMaterial(const ORBITMaterial* material)
{
	ID3D11ShaderResourceView * const diffuseRVDX11		= material->GetDiffuseRVDX11();
	ID3D11ShaderResourceView * const specularRVDX11		= material->GetSpecularRVDX11();
	ID3D11ShaderResourceView * const normalRVDX11		= material->GetNormalRVDX11();

	_deviceContext->PSSetShaderResources(_srDiffuseSlot,	1,	&diffuseRVDX11);
	_deviceContext->PSSetShaderResources(_srSpecularSlot,	1,	&specularRVDX11);
	_deviceContext->PSSetShaderResources(_srNormalSlot,		1,	&normalRVDX11);

	return true;
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
	//TODO: Chane DrawIndexedInstancedIndirect
	_deviceContext->DrawIndexed(_drawVariables.GetIndexCount(), _drawVariables.GetIndexStart(), _drawVariables.GetVertexStart());

	return true;
}



bool DeferredShadingMethodDX::RenderLighting(std::vector<IRenderableObject*>& renderRequestObjects)
{
	for (int objectsIndex = 0; objectsIndex < renderRequestObjects.size(); objectsIndex++)
	{
		renderRequestObjects[objectsIndex];
	}
	return true;
}
bool DeferredShadingMethodDX::CreateVertexBuffer(int vertexCount, int indexCount, ORBITVertex* verticesOrigin, UINT* indicesOrigin, ORBITMesh* outMeshData)
{
	return false;
}

bool DeferredShadingMethodDX::ResetRenderTarget()
{
	_deviceContext->OMSetRenderTargets(0, nullptr, nullptr);
	return true;
}


DeferredShadingMethodDX::DrawVariables::DrawVariables() :
	_indexCount(0),
	_indexStart(0),
	_vertexStart(0)
{

}

bool DeferredShadingMethodDX::SetWorldMatrix(const ORBITMATRIX4x4* worldMatrix)
{
	DirectX::XMFLOAT4X4 tempFloat4x4;

	//copy view
	for (int width = 0; width < 4; width++)
	{
		for (int height = 0; height < 4; height++)
		{
			tempFloat4x4.m[width][height] = worldMatrix->m[width][height];
		}
	}
	_vsConstVariables._worldMatrix = DirectX::XMLoadFloat4x4(&tempFloat4x4);
	_psConstVariables._worldMatrix = _vsConstVariables._viewMatrix;

	return true;
}



bool DeferredShadingMethodDX::LoadShader_()
{
	//UNDONE: LOAD SHADER FROM OBJECT FILE(binary), NOT hlsl Code
	HRESULT result;
	ID3DBlob* errorMessage;
	ID3DBlob* tempPSShaderBuffer;
	ID3DBlob* tempVSShaderBuffer;
	ID3DBlob* tempCSShaderBuffer;

	//Load PS
	_pixelShaderHash = std::hash<std::wstring>{}(L"Render_PS.hlsl");
	result = D3DCompileFromFile(L"Render_PS.hlsl", NULL, NULL, "main", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&tempPSShaderBuffer, &errorMessage);

	if (FAILED(result))
		return false;

	//Load VS
	_vertexShaderHash = std::hash<std::wstring>{}(L"Render_VS.hlsl");
	result = D3DCompileFromFile(L"Render_VS.hlsl", NULL, NULL, "main", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&tempVSShaderBuffer, &errorMessage);
	if (FAILED(result))
		return false;

	//Load CS
	_computeShaderHash = std::hash<std::wstring>{}(L"ComputeShader_Composite.hlsl");
	result = D3DCompileFromFile(L"ComputeShader_Composite", NULL, NULL, "main", "cs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&tempCSShaderBuffer, &errorMessage);
	
	if (FAILED(result))
		return false;

	if (false == SetShader_(_device, tempPSShaderBuffer, tempVSShaderBuffer, tempCSShaderBuffer))
		return false;

	tempPSShaderBuffer->Release();
	tempPSShaderBuffer = nullptr;

	tempVSShaderBuffer->Release();
	tempVSShaderBuffer = nullptr;

	tempCSShaderBuffer->Release();
	tempCSShaderBuffer = nullptr;


	return true;
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