#include "stdafx.h"
#include "ModelManager.h"
#include "ModelStaticData.h"
#include "GraphicsSystem.h"
#include "TestModelObject.h"
#include "IModelImporterImpl.h"
#include "DeviceManager.h"
ModelManager::ModelManager(GraphicsSystem* graphicSystem, IModelImporterImpl*	modelImporter) :
	_graphicSystem(graphicSystem),
	_modelImporter(modelImporter)
{
	if (nullptr == _modelImporter)
	{
		//TODO: default importer
	}
} 
ModelManager::~ModelManager()
{
	if (_modelImporter)
		delete _modelImporter;
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

	if (_modelDataMap.end() == itor)
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
	ModelStaticData* tempData;
	tempData = _modelImporter->LoadModel(fileName, _graphicSystem->GetRenderingManager());

	//TODO: temp 데이터가 변조됨. 쉘로우 카피?
	if (tempData)
		_modelDataMap.insert(std::unordered_map<size_t, ModelStaticData*>::value_type(tempData->GetHashCode(), tempData));

	return tempData;

}
