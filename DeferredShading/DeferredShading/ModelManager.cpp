#include "stdafx.h"
#include "ModelManager.h"
#include "ModelStaticData.h"
#include "GraphicsSystem.h"
ModelManager::ModelManager(GraphicsSystem* graphicSystem)
{
	_graphicSystem = graphicSystem;

}
ModelManager::~ModelManager()
{

}

bool ModelManager::Initialize()
{
	return true;
}
bool ModelManager::Reset()
{
	return true;
}
void ModelManager::Update(float deltaTime)
{

}
void ModelManager::PreUpdate(float deltaTime)
{

}void ModelManager::PostUpdate(float deltaTime)
{

}
void ModelManager::Render()
{

}

ModelStaticData* ModelManager::GetModelData(size_t hashCode)
{
	std::unordered_map<size_t, ModelStaticData*>::iterator itor = _modelDataMap.find(hashCode);
	ModelStaticData* resultModelData = nullptr;

	if (itor == _modelDataMap.end())
	{
		std::wstring fileName;

		resultModelData = LoadModel_(fileName);
	}
	else
	{
		resultModelData = itor->second;
	}
	return resultModelData;

}

ModelStaticData* ModelManager::LoadModel_(std::wstring& fileName)
{
	//TEST: just temp fuction blahblah
	//ModelStaticData* tempData = new ModelStaticData(0, nullptr, 0, RenderEngine::RENDERINGMODE::DEFERRED_SHADING, RenderEngine::RENDERTYPE::CHARACTER);
	ModelStaticData* tempData = new ModelStaticData(0, nullptr, 0, RenderEngine::RENDERINGMODE::FORWARD, RenderEngine::RENDERTYPE::CHARACTER);
	_modelDataMap.insert(std::unordered_map<size_t, ModelStaticData*>::value_type(tempData->GetHashCode(), tempData));

	return tempData;

}
