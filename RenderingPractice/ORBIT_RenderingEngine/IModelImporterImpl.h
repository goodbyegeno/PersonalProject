#pragma once
class ModelStaticData;
class GraphicsDevice;
class RenderingManager;

class IModelImporterImpl
{
public:
	IModelImporterImpl() {}
	virtual ~IModelImporterImpl() {}

	virtual ModelStaticData* LoadModel(std::wstring modelName, RenderingManager* renderingManager) = 0;

};