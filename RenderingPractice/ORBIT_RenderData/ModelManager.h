#pragma once


class ModelStaticData;
class IModelImporterImpl;
class GraphicsDevice;
class ModelManager
{
public:
	ModelManager(IModelImporterImpl*	modelImporter);
	virtual ~ModelManager();

	bool Initialize();
	bool Reset();

	void Render();
	void PreUpdate(float deltaTime);
	void PostUpdate(float deltaTime);

	void Update(float deltaTime);
	ModelStaticData* GetModelData(size_t hashCode);

private:
	ModelStaticData* LoadModel_(std::wstring& fileName);

	//UNDONE modeldata should contained multi layer container? ex) double vector
	std::unordered_map<size_t, ModelStaticData*>	_modelDataMap; //<modelHashCode, data>
	IModelImporterImpl*								_modelImporter;
	GraphicsDevice*									_graDevice;
};