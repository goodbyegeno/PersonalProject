#include "TestModelObject.h"

TestModelObject::TestModelObject():
	m_bIsUsePool(false),
	m_lstVertex(nullptr),
	m_lstVeticesIndex(nullptr)
{
	
}
TestModelObject::~TestModelObject()
{

	if (m_bIsUsePool)
	{
		if (nullptr == m_lstVertex)
			delete[] m_lstVertex;
		if (nullptr == m_lstVeticesIndex)
			delete[] m_lstVeticesIndex;
	}
}

void TestModelObject::Initialize(DeviceManager* pDeviceManager)
{


	m_lstVertex = new RenderEngineTest::MeshVertex_Test[3];
	m_lstVeticesIndex = new int[3];
	m_nNumVertices = 3;

	m_lstVertex[0].Position.x = 2.0f;
	m_lstVertex[0].Position.y = 1.0f;
	m_lstVertex[0].Position.z = 1.0f;
	m_lstVertex[0].Position.w = 1.0f;
	
	m_lstVertex[1].Position.x = 1.0f;
	m_lstVertex[1].Position.y = 1.0f;
	m_lstVertex[1].Position.z = 1.0f;
	m_lstVertex[1].Position.w = 1.0f;
	
	m_lstVertex[2].Position.x = 1.5f;
	m_lstVertex[2].Position.y = 2.0f;
	m_lstVertex[2].Position.z = 1.0f;
	m_lstVertex[2].Position.w = 1.0f;

	m_lstVertex[0].Color.x = 1.0f;
	m_lstVertex[0].Color.y = 0.0f;
	m_lstVertex[0].Color.z = 0.0f;
	m_lstVertex[0].Color.w = 1.0f;

	m_lstVertex[1].Color.x = 0.0f;
	m_lstVertex[1].Color.y = 1.0f;
	m_lstVertex[1].Color.z = 0.0f;
	m_lstVertex[1].Color.w = 1.0f;

	m_lstVertex[2].Color.x = 0.0f;
	m_lstVertex[2].Color.y = 0.0f;
	m_lstVertex[2].Color.z = 1.0f;
	m_lstVertex[2].Color.w = 1.0f;

}
void TestModelObject::Reset()
{

}

void TestModelObject::FlushRender()
{
	g_pRenderingManager->AddRenderedObject(this);
}

void TestModelObject::Render()
{


	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;


}