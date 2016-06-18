#pragma once
#include "TestHeaderCommon.h"
#include "RenderEngineCommon.h"
#include "CharacterRenderedObject.h"

class DeviceManager;

class TestModelObject : public CharacterRenderedObject
{
public:
	TestModelObject();
	virtual ~TestModelObject();

	void Initialize(DeviceManager* pDeviceManager);
	void Reset();

	virtual void FlushRender();
	RenderEngineTest::MeshVertex_Test* GetMesh()	{ return m_lstVertex; }
	int* GetVerticesIndex()							{ return m_lstVerticesIndex; }
	int	 GetVerticesCount()							{ return m_nNumVertices;  }

private:

	RenderEngineTest::MeshVertex_Test*	m_lstVertex;
	void*								m_pVertexBuffer;
	void*								m_pIndexBuffer;
	int*								m_lstVerticesIndex;
	int									m_nNumVertices;

	bool								m_bIsUsePool;

};