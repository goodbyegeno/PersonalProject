#pragma once
#include <string>
class ModelStaticData;
class GraphicsDevice;

class IModelImporterImpl
{
public:
	IModelImporterImpl() {}
	virtual ~IModelImporterImpl() {}

	virtual ModelStaticData* LoadModel(std::wstring modelName, GraphicsDevice* graphicsDevice) = 0;

};