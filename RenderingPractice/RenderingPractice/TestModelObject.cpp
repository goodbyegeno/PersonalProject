#include "stdafx.h"
#include "TestModelObject.h"
#include <string>
TestModelObject::TestModelObject(size_t hashCode, ORBITMesh** meshDatas, int meshCount, size_t renderingMethodHash, RenderEngine::RENDERTYPE _renderType):
	_isUsePool(false),
	_vertices(nullptr),
	_vertexIndices(nullptr),
	ModelStaticData(hashCode, meshDatas, meshCount, renderingMethodHash, _renderType)
{
	
}
TestModelObject::~TestModelObject()
{
	if (_isUsePool)
	{
		if (nullptr == _vertices)
			delete[] _vertices;
		if (nullptr == _vertexIndices)
			delete[] _vertexIndices;
	}
}

bool TestModelObject::Initialize(DeviceManager* deviceManager)
{
	_vertices = new RenderEngineTest::MeshVertex_Test[3];
	_vertexIndices = new int[3];
	_vertexCount = 3;

	_vertices[0].Position.x = 2.0f;
	_vertices[0].Position.y = 1.0f;
	_vertices[0].Position.z = 1.0f;
	_vertices[0].Position.w = 1.0f;
	
	_vertices[1].Position.x = 1.0f;
	_vertices[1].Position.y = 1.0f;
	_vertices[1].Position.z = 1.0f;
	_vertices[1].Position.w = 1.0f;
	
	_vertices[2].Position.x = 1.5f;
	_vertices[2].Position.y = 2.0f;
	_vertices[2].Position.z = 1.0f;
	_vertices[2].Position.w = 1.0f;

	_vertices[0].Color.x = 1.0f;
	_vertices[0].Color.y = 0.0f;
	_vertices[0].Color.z = 0.0f;
	_vertices[0].Color.w = 1.0f;

	_vertices[1].Color.x = 0.0f;
	_vertices[1].Color.y = 1.0f;
	_vertices[1].Color.z = 0.0f;
	_vertices[1].Color.w = 1.0f;

	_vertices[2].Color.x = 0.0f;
	_vertices[2].Color.y = 0.0f;
	_vertices[2].Color.z = 1.0f;
	_vertices[2].Color.w = 1.0f;

	return true;
}
bool TestModelObject::Reset()
{
	return true;
}

void TestModelObject::FlushRender()
{
	//g_pRenderingManager->AddRenderedObject(this);
}
