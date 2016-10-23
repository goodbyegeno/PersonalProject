#include "stdafx.h"
#include "TestStaticModelImporter.h"
#include "TestModelObject.h"
#include "GraphicsDevice.h"
#include "ORBITVertex.h"
#include "RenderEngineCommon.h"
#include "ORBITMeshSubset.h"
TestStaticModelImporter::TestStaticModelImporter()
{

}
TestStaticModelImporter::~TestStaticModelImporter()
{
}

ModelStaticData* TestStaticModelImporter::LoadModel(std::wstring modelName, GraphicsDevice* graphicDevice)
{
	//TODO Load isn't working what i expected. should fix
	ORBITMesh::MeshInitialData initData;
	if (false == TestModelRawData_(graphicDevice, initData))
		return nullptr;

	ORBITMesh** meshs;
	meshs = new ORBITMesh*[1];
	meshs[0] = new ORBITMesh(initData);
	UINT* strides = new UINT[1];
	strides[0] = sizeof(ORBITVertex);
	initData.strides = strides;
	UINT* offsets = new UINT[1];
	offsets[0] = 0;
	initData.offsets = offsets;
	initData.subsetCount = 1;
	ORBITMeshSubset** subsets = new ORBITMeshSubset*[1];
	subsets[0] = new ORBITMeshSubset(3, 0, 0);
	initData.meshSubset = subsets;


	ModelStaticData* tempData = new TestModelObject(std::hash<std::wstring>{}(L"TestModel"), meshs, 1, std::hash<std::wstring>{}(L"ForwardRendering"), RenderEngine::RENDERTYPE::CHARACTER);

	return tempData;
}

bool TestStaticModelImporter::TestModelRawData_(GraphicsDevice* graphicsDevice, ORBITMesh::MeshInitialData& outData)//(ID3D11Device* device)
{
	//from rastertek.com
	ORBITVertex* vertices;
	UINT* indices;
	bool returnValue = false;

	outData.vertexCount = 3;
	outData.indexCount = 3;

	vertices = new ORBITVertex[outData.vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new UINT[outData.indexCount];
	if (!indices)
	{
		delete[] vertices;

		return false;
	}

	// Load the vertex array with data.
	vertices[0].SetPosition(ORBITFLOAT4(-1.0f, -1.0f, 0.0f, 0.0f));  // Bottom left.
	vertices[0].SetColor(ORBITFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));

	vertices[1].SetPosition(ORBITFLOAT4(0.0f, 1.0f, 0.0f, 0.0f));
	vertices[1].SetColor(ORBITFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));

	vertices[2].SetPosition(ORBITFLOAT4(-1.0f, -1.0f, 0.0f, 0.0f));   // Bottom right.
	vertices[2].SetColor(ORBITFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));

	// Load the index array with data.
	indices[0] = 0;  // Bottom left.
	indices[1] = 1;  // Top middle.
	indices[2] = 2;  // Bottom right.

	if (false == CreateBufferDX_(graphicsDevice, outData.vertexCount, outData.indexCount, vertices, indices, &outData))
	{
		delete[] vertices;
		vertices = 0;

		delete[] indices;
		indices = 0;
		return false;
	}
	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;
	return true;
}

bool TestStaticModelImporter::CreateBufferDX_(GraphicsDevice* graphicsDevice, int vertexCount, int indexCount, ORBITVertex* vertices, UINT* indices, ORBITMesh::MeshInitialData* dataOut)
{
	//from rastertek.com
	ID3D11Device* deviceDX = static_cast<ID3D11Device3*>(graphicsDevice->GetBuffer());

	HRESULT result;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(ORBITVertex) * vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

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
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = deviceDX->CreateBuffer(&indexBufferDesc, &indexData, &indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	dataOut->indexBufferFormat = RenderEngine::ORBIT_FORMAT::ORBIT_FORMAT_R32_UINT;
	dataOut->vertexBuffersDX11 = &vertexBuffer;
	dataOut->indexBuffersDX = indexBuffer;

	return true;
}