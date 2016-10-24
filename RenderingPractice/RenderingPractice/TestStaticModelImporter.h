#pragma once
#include "IModelImporterImpl.h"
#include "ORBITMesh.h"
class GraphicsDevice;
class RenderMethod;

class TestStaticModelImporter : public IModelImporterImpl
{
public:
	TestStaticModelImporter();
	virtual ~TestStaticModelImporter();

	virtual ModelStaticData* LoadModel(std::wstring modelName, RenderingManager* renderingManager);

private:
	bool TestModelRawData_(int vertexCount, int indexCount, RenderMethod* renderMethod, ORBITMesh* outData);

};