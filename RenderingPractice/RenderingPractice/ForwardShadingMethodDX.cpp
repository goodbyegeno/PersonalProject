#include "stdafx.h"
#include "ForwardShadingMethodDX.h"
#include "CoreEngineCommon.h"
#include "ShaderManager.h"
#include "RenderTargetManager.h"
#include "IShaderObejct.h"
#include "DeviceManager.h"
#include "GraphicsDevice.h"
#include "CoreSystem.h"
#include "CameraBase.h"
#include "CustomMatrix.h"
#include "CustomVector.h"
#include "ShaderRenderTarget.h"
#include "ShaderRenderTargetDX.h"
#include "IShaderRenderTargetImpl.h"
#include "IRenderableObject.h"
#include "ModelDynamicData.h"
#include "ModelStaticData.h"
#include "ORBITVertex.h"
#include "ORBITMesh.h"
#include "ORBITMeshSubset.h"
#include "ORBITMaterial.h"
#include "DXDevice11_4.h"
#include "DXHelper11.h"
#include "RenderingSingletonManager.h"
#include "ORBITVertex.h"
#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <cstring>

ForwardShadingMethodDX::ForwardShadingMethodDX() : 
	_renderTargetHash(std::hash<std::wstring>{}(L"Albedo"))
{
}
ForwardShadingMethodDX::~ForwardShadingMethodDX()
{
}
bool ForwardShadingMethodDX::Initialize(DeviceManager* deviceManager, ShaderManager* shaderManager, RenderTargetManager* renderTargetManager)
{
	_shaderManager = shaderManager;
	_renderTargetManager = renderTargetManager;

	GraphicsDevice* graDevice = deviceManager->GetDevice();
	if (nullptr == graDevice || RenderEngine::GRAPHICSAPITYPE::DIRECTX11_4 != graDevice->GetGraphicsAPIType())
		return false;

	_deviceWrapper = static_cast<DXDevice11_4*>(graDevice);

	_device = static_cast<ID3D11Device3*>(graDevice->GetBuffer());
	if (nullptr == _device)
		return false;

	_deviceContext = _deviceWrapper->GetDeviceContext();

	_vertexShader = nullptr;
	_pixelShader = nullptr;
	_computeShader = nullptr;

	_vertexShaderHash = 0;
	_pixelShaderHash = 0;
	_computeShaderHash = 0;

	if (false == LoadShader_())
		return false;

	if (false == InitRenderTargets(renderTargetManager))
		return false;
	_depthStencilView = _deviceWrapper->GetDepthStencilView();

	return true;
}
bool ForwardShadingMethodDX::Reset(DeviceManager* deviceManager, ShaderManager* shaderManager)
{
	_shaderManager = shaderManager;
	GraphicsDevice* graDevice = deviceManager->GetDevice();
	if (nullptr == graDevice || RenderEngine::GRAPHICSAPITYPE::DIRECTX11_4 != graDevice->GetGraphicsAPIType())
		return false;

	if (false == InitRenderTargets(_renderTargetManager))
		return false;

	return true;
}
bool ForwardShadingMethodDX::SetWorldMatrix(const ORBITMATRIX4x4* worldMatrix)
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

bool ForwardShadingMethodDX::InitRenderTargets(RenderTargetManager* renderTargetManager)
{
	ShaderRenderTarget*	shaderRenderTarget = renderTargetManager->GetRenderTarget(_renderTargetHash);
	ShaderRenderTargetDX * shaderRenderTargetDX = nullptr;
	if (nullptr == shaderRenderTarget)
	{
		D3D11_TEXTURE2D_DESC AlbedoRTTexDesc;
		AlbedoRTTexDesc.Width = _deviceWrapper->GetRenderingResolutionWidth();
		AlbedoRTTexDesc.Height = _deviceWrapper->GetRenderingResolutionHeight();
		AlbedoRTTexDesc.MipLevels = 1;
		AlbedoRTTexDesc.ArraySize = 1;
		AlbedoRTTexDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		AlbedoRTTexDesc.SampleDesc.Count = 1;
		AlbedoRTTexDesc.SampleDesc.Quality = 0;
		AlbedoRTTexDesc.Usage = D3D11_USAGE_DEFAULT;
		AlbedoRTTexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		AlbedoRTTexDesc.CPUAccessFlags = 0;
		AlbedoRTTexDesc.MiscFlags = 0;

		HRESULT result;
		ID3D11Texture2D* renderTargetTex;
		result = _device->CreateTexture2D(&AlbedoRTTexDesc, nullptr, &renderTargetTex);
		if (FAILED(result))
			return false;

		ID3D11RenderTargetView*	renderingTargetView;
		result = _device->CreateRenderTargetView(renderTargetTex,
			nullptr,
			&renderingTargetView);
		if (FAILED(result))
			return false;

		ID3D11ShaderResourceView* shaderResourceView;
		result = _device->CreateShaderResourceView(renderTargetTex,
			nullptr,
			&shaderResourceView);
		if (FAILED(result))
			return false;

		shaderRenderTarget = new ShaderRenderTarget(new ShaderRenderTargetDX(renderTargetTex, shaderResourceView, renderingTargetView));
	}
	shaderRenderTargetDX = static_cast<ShaderRenderTargetDX*>(shaderRenderTarget->GetData());
	_renderTargetCount = 1;

	_renderTargets[static_cast<int>(FORWARDSHADINGRT::DIFFUSE)] = shaderRenderTargetDX;
	_renderTargetTex[static_cast<int>(FORWARDSHADINGRT::DIFFUSE)] = shaderRenderTargetDX->GetTexture();
	_shaderResourceView[static_cast<int>(FORWARDSHADINGRT::DIFFUSE)] = shaderRenderTargetDX->GetShaderResourceView();
	_renderingTargetView[static_cast<int>(FORWARDSHADINGRT::DIFFUSE)] = shaderRenderTargetDX->GetRenderTargetView();

	return true;
}
bool ForwardShadingMethodDX::SetCameraMatrix()
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
bool ForwardShadingMethodDX::SettingShaderOptions()
{
	_deviceContext->IASetInputLayout(_inputLayout);

	_deviceContext->VSSetShader(_vertexShader, nullptr, 0);
	_deviceContext->PSSetShader(_pixelShader, nullptr, 0);
	_deviceContext->GSSetShader(nullptr, nullptr, 0);

	//_deviceContext->RSSetViewports(1, _viewPort);
	//_deviceContext->OMSetDepthStencilState(_depthStencilState, 0);

	//set shaderResources

	//set samplers

	return false;
}
bool ForwardShadingMethodDX::SetConstVariables()
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

	_deviceContext->VSSetConstantBuffers(0, 1, &_vsConstVariableBuffer);
	_deviceContext->PSSetConstantBuffers(0, 1, &_psConstVariableBuffer);

	return true;
}
bool ForwardShadingMethodDX::SetRenderTarget()
{
	const float zeros[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	for (int renderTargetIndex = 0; renderTargetIndex < static_cast<int>(FORWARDSHADINGRT::MAX); renderTargetIndex++)
	{
		_deviceContext->ClearRenderTargetView(_renderingTargetView[renderTargetIndex], zeros);
	}
	_deviceContext->ClearDepthStencilView(_depthStencilView, D3D10_CLEAR_DEPTH, 0.0f, 0);

	_deviceContext->OMSetRenderTargets(_renderTargetCount, _renderingTargetView, _depthStencilView);
	ID3D11BlendState* blendState = _deviceWrapper->GetBlendState();
	_deviceContext->OMSetBlendState(blendState, nullptr, 0xffffffff);

	return true;
}

bool ForwardShadingMethodDX::SetVertexBuffer(const ORBITMesh* mesh) const
{
	ID3D11Buffer* const* vertexBuffers = mesh->GetVertexBuffersDX11();
	int bufferCount = mesh->GetVertexBufferCount();
	const UINT* strides = mesh->GetStrides();
	const UINT* offsets = mesh->GetOffsets();

	_deviceContext->IASetVertexBuffers(0, bufferCount, vertexBuffers, strides, offsets);
	_deviceContext->IASetIndexBuffer(mesh->GetIndexBufferDX11(), RenderingSingletonManager::GetInstance()->GetDXHelper11()->GetIndexBufferFormat(mesh->GetIndexBufferFormat()), 0);
	//_deviceWrapper->RenderMesh(meshData[meshIndex]));

	return true;
}
bool ForwardShadingMethodDX::SetSubsetVBIndicesInfo(const ORBITMeshSubset* subsetData)
{
	_drawVariables.SetIndexData(subsetData->GetIndexCount(), subsetData->GetIndexStart(), subsetData->GetVertexStart());
	return true;

}
bool ForwardShadingMethodDX::SetMaterial(const ORBITMaterial* material)
{
	ID3D11ShaderResourceView * const diffuseRVDX11 = material->GetDiffuseRVDX11();
	ID3D11ShaderResourceView * const specularRVDX11 = material->GetSpecularRVDX11();
	ID3D11ShaderResourceView * const normalRVDX11 = material->GetNormalRVDX11();

	_deviceContext->PSSetShaderResources(_srDiffuseSlot, 1, &diffuseRVDX11);
	_deviceContext->PSSetShaderResources(_srSpecularSlot, 1, &specularRVDX11);
	_deviceContext->PSSetShaderResources(_srNormalSlot, 1, &normalRVDX11);

	return true;
}
bool ForwardShadingMethodDX::RenderMesh()
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
	_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	_deviceContext->DrawIndexed(_drawVariables.GetIndexCount(), _drawVariables.GetIndexStart(), _drawVariables.GetVertexStart());

	return true;
}
bool ForwardShadingMethodDX::LoadShader_()
{
	//UNDONE: LOAD SHADER FROM OBJECT FILE(binary), NOT hlsl Code or debug directory
	HRESULT result;
	ID3DBlob* tempPSShaderBuffer;
	ID3DBlob* tempVSShaderBuffer;

	//Load PS
	_pixelShaderHash = std::hash<std::wstring>{}(L"ForwardRender_PS");
	result = D3DReadFileToBlob(L"..\\x64\\Debug\\ForwardRender_PS.cso", &tempPSShaderBuffer);
	/*result = D3DCompileFromFile(L"ForwardRender_PS.hlsl", NULL, NULL, "main", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&tempPSShaderBuffer, &errorMessage);
		*/
	if (FAILED(result))
		return false;

	//Load VS
	_vertexShaderHash = std::hash<std::wstring>{}(L"ForwardRender_VS.hlsl");
	result = D3DReadFileToBlob(L"..\\x64\\Debug\\ForwardRender_VS.cso", &tempVSShaderBuffer);
	/*
	result = D3DCompileFromFile(L"ForwardRender_VS.hlsl", NULL, NULL, "main", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&tempVSShaderBuffer, &errorMessage);
		*/
	if (FAILED(result))
		return false;

	if (false == SetShader_(_device, tempPSShaderBuffer, tempVSShaderBuffer))
		return false;

	tempPSShaderBuffer->Release();
	tempPSShaderBuffer = nullptr;

	tempVSShaderBuffer->Release();
	tempVSShaderBuffer = nullptr;

	return true;
}
bool ForwardShadingMethodDX::SetShader_(ID3D11Device3* deviceDX, ID3DBlob* psShaderBuffer, ID3DBlob* vsShaderBuffer)
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

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = 12;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	polygonLayout[2].SemanticName = "NORMAL";
	polygonLayout[2].SemanticIndex = 0;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[2].InputSlot = 0;
	polygonLayout[2].AlignedByteOffset = 20;
	polygonLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[2].InstanceDataStepRate = 0;



	resultValue = deviceDX->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), &_inputLayout);
	if (FAILED(resultValue))
		return false;

	resultValue = deviceDX->CreatePixelShader(psShaderBuffer->GetBufferPointer(), psShaderBuffer->GetBufferSize(), NULL, &_pixelShader);
	if (FAILED(resultValue))
		return false;

	CD3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(ShaderConstVariables);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	resultValue = _device->CreateBuffer(&bufferDesc, 0, &_vsConstVariableBuffer);
	if (FAILED(resultValue))
		return false;

	bufferDesc.ByteWidth = sizeof(ShaderConstVariables);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	resultValue = _device->CreateBuffer(&bufferDesc, 0, &_psConstVariableBuffer);
	if (FAILED(resultValue))
		return false;
	return true;
}
bool ForwardShadingMethodDX::ResetRenderTarget()
{
	_deviceContext->OMSetRenderTargets(0, nullptr, nullptr);
	return true;
}
bool ForwardShadingMethodDX::CreateVertexBuffer(int vertexCount, int indexCount, ORBITVertex* verticesOrigin, UINT* indicesOrigin, ORBITMesh* outMeshData)
{
	ID3D11Device* deviceDX = _device;

	HRESULT result;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(ShaderVertexInput) * vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	
	ShaderVertexInput* vertices = new ShaderVertexInput[vertexCount];
	for (int verticesIndex = 0; verticesIndex < vertexCount; verticesIndex++)
	{
		vertices[verticesIndex]._position.x = verticesOrigin[verticesIndex].GetPosition()._x;
		vertices[verticesIndex]._position.y = verticesOrigin[verticesIndex].GetPosition()._y;
		vertices[verticesIndex]._position.z = verticesOrigin[verticesIndex].GetPosition()._z;

		vertices[verticesIndex]._normal.x = verticesOrigin[verticesIndex].GetNormal()._x;
		vertices[verticesIndex]._normal.y = verticesOrigin[verticesIndex].GetNormal()._y;
		vertices[verticesIndex]._normal.z = verticesOrigin[verticesIndex].GetNormal()._z;
		
		vertices[verticesIndex]._texcoord.x = verticesOrigin[verticesIndex].GetUV()._x;
		vertices[verticesIndex]._texcoord.y = verticesOrigin[verticesIndex].GetUV()._y;
	}
	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	ID3D11Buffer *vertexBuffer, *indexBuffer;

	// Now create the vertex buffer.
	result = deviceDX->CreateBuffer(&vertexBufferDesc, &vertexData, &vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(UINT) * indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indicesOrigin;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = deviceDX->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	outMeshData->SetVertexBufferDX11(&vertexBuffer);
	outMeshData->SetIndexBufferDX11(indexBuffer);
	outMeshData->SetIndexBufferFormat(RenderEngine::ORBIT_FORMAT::ORBIT_FORMAT_R32_UINT);
	outMeshData->SetVertexBufferCount(1);

	delete[] vertices;

	return true;
}



ForwardShadingMethodDX::DrawVariables::DrawVariables()
{
}
ForwardShadingMethodDX::DrawVariables::~DrawVariables()
{
}

void ForwardShadingMethodDX::DrawVariables::SetIndexData(int indexCount, int indexStart, int vertexStart)
{
	_indexCount = indexCount;
	_indexStart = indexStart;
	_vertexStart = vertexStart;
}