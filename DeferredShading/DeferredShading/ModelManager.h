#pragma once
#include <cstring>
#include <unordered_map>

class GraphicsSystem;
class ModelStaticData;

class ModelManager
{
public:
	ModelManager(GraphicsSystem* graphicSystem);
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

	GraphicsSystem* _graphicSystem;

	//UNDONE modeldata should contained multi layer container? ex) double vector
	std::unordered_map<size_t, ModelStaticData*> _modelDataMap;

};