#pragma once
#include "TestHeaderCommon.h"
#include "RenderEngineCommon.h"
#include "ModelStaticData.h"

class DeviceManager;

class TestModelObject : public ModelStaticData
{
public:
	TestModelObject(size_t hashCode, ORBITMesh** meshDatas, int meshCount, size_t renderingMethodHash, RenderEngine::RENDERTYPE _renderType);
	virtual ~TestModelObject();

	bool Initialize(DeviceManager* deviceManager);
	bool Reset();

	virtual void FlushRender();
	RenderEngineTest::MeshVertex_Test* GetMesh()	{ return _vertices; }
	int* GetVerticesIndex()							{ return _vertexIndices; }
	int	 GetVerticesCount()							{ return _vertexCount;  }

private:

	RenderEngineTest::MeshVertex_Test*	_vertices;
	void*								_vertexBuffer;
	void*								_indexBuffer;
	int*								_vertexIndices;
	int									_vertexCount;

	bool								_isUsePool;

};