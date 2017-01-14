#include "stdafx.h"
#include "TestStaticModelImporter.h"
#include "TestModelObject.h"
#include "GraphicsDevice.h"
#include "ORBITVertex.h"
#include "RenderEngineCommon.h"
#include "ORBITMeshSubset.h"
#include "RenderingManager.h"
#include "RenderingMethod.h"
TestStaticModelImporter::TestStaticModelImporter()
{

}
TestStaticModelImporter::~TestStaticModelImporter()
{
}

ModelStaticData* TestStaticModelImporter::LoadModel(std::wstring modelName, RenderingManager* renderingManager)
{
	//TODO Load isn't working what i expected. should fix
	ORBITMesh::MeshInitialData initData;
	size_t renderMethodHash = std::hash<std::wstring>{}(L"ForwardRendering");
	RenderMethod* renderMethod = renderingManager->GetRenderingMethod(renderMethodHash);
	

	
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
	initData.subsetIndexMappingType = ORBITMesh::SUBSETINDEXMAPPINGTYPE::LINEAR;

	initData.vertexCount = 3;
	initData.indexCount = 3;

	ORBITMesh** meshs;
	meshs = new ORBITMesh*[1];
	meshs[0] = new ORBITMesh(initData);

	if (false == TestModelRawData_(initData.vertexCount, initData.indexCount, renderMethod, meshs[0]))
		return nullptr;

	ModelStaticData* tempData = new TestModelObject(std::hash<std::wstring>{}(L"TestModel"), meshs, 1, renderMethodHash, RenderEngine::RENDERTYPE::CHARACTER);

	return tempData;
}

bool TestStaticModelImporter::TestModelRawData_(int vertexCount, int indexCount, RenderMethod* renderMethod, ORBITMesh* outData)//(ID3D11Device* device)
{
	//from rastertek.com
	ORBITVertex* vertices;
	UINT* indices;
	bool returnValue = false;

	vertices = new ORBITVertex[vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new UINT[indexCount];
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

	bool result = renderMethod->CreateVertexBuffer(vertexCount, indexCount, vertices, indices, outData);
	
	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;
	return result;
}

