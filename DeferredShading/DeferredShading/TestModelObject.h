#pragma once
#include "TestHeaderCommon.h"
#include "RenderEngineCommon.h"
class TestModelObject : public IModelObject
{
public:
	TestModelObject();
	virtual ~TestModelObject();

	void Initialize();
	void Reset();

	void Render();

private:

	RenderEngineTest::MeshVertex_Test*	m_lstVertex;
	int*						m_lstVeticesIndex;
	int							m_nNumVertices;

	bool						m_bIsUsePool;
};