#pragma once
#include "IModelImporterImpl.h"
#include "ORBITMesh.h"
class GraphicsDevice;

class TestStaticModelImporter : public IModelImporterImpl
{
public:
	TestStaticModelImporter();
	virtual ~TestStaticModelImporter();

	virtual ModelStaticData* LoadModel(std::wstring modelName, GraphicsDevice* graphicsDevice);

private:
	bool TestModelRawData_(GraphicsDevice* graphicsDevice, ORBITMesh::MeshInitialData& outData);
	bool CreateBufferDX_(GraphicsDevice* graphicsDevice, int vertexCount, int indexCount, ORBITVertex* vertices, UINT* indices, ORBITMesh::MeshInitialData* dataOut);

};