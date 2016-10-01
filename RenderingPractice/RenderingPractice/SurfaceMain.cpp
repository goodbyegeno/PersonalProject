#include "stdafx.h"
#include "SurfaceMain.h"
#include "CoreEngineCommon.h"
#include "CoreSystem.h"
#include "GraphicsSystem.h"
#include "IUpdateableObject.h"
#include "IRenderableObject.h"
#include "IRenderableManager.h"
#include "RenderEngineCommon.h"
#include "RenderingMethod.h"
#include "RenderEngineFactoryBase.h"
#include "SceneManager.h"
#include "SystemConfigureFileImporter.h"
#include "TestSystemConfigureFileImporterSuface.h"
#include "TestSceneObjectFactory.h"
#include "TestRenderingEngineFactory.h"
#include "TestCamera.h"

#include <vector>
#include <unordered_map>
//TEST: TEST CLASS!
SurfaceMain::SurfaceMain() :
	_coreSystem(nullptr),
	_graphicsSystem(nullptr)
{
}
SurfaceMain::~SurfaceMain()
{
}
bool SurfaceMain::Initialize(HWND hwnd)
{

	GraphicsSystem::GraphicsSystemInitialData tempGraphicsData;
	tempGraphicsData.graphicsAPIType = RenderEngine::GRAPHICSAPITYPE::DIRECTX11_4;
	tempGraphicsData.renderEngineFactory = new TestRenderingEngineFactory();
	_graphicsSystem = new GraphicsSystem(tempGraphicsData);

	TestSceneObjectFactory* testSceneObjectFactory = new TestSceneObjectFactory();
	_sceneManager = new SceneManager(_graphicsSystem, testSceneObjectFactory);

	CoreSystem::CoreSystemInititalData tempCoreSystemData;
	std::vector<std::vector<IUpdateableObject*>> updateableObjectGroupList;
	std::vector<IUpdateableObject*> tempUpdateableVector2;
	tempUpdateableVector2.clear();
	tempUpdateableVector2.push_back(_graphicsSystem);
	std::vector<IUpdateableObject*> tempUpdateableVector1;
	tempUpdateableVector1.clear();
	tempUpdateableVector1.push_back(_sceneManager);
	tempCoreSystemData.updateableObjectGroupList.push_back(tempUpdateableVector1);
	tempCoreSystemData.updateableObjectGroupList.push_back(tempUpdateableVector2);

	std::vector<IRenderableManager*> tempRenderableVector;
	tempRenderableVector.clear();
	tempRenderableVector.push_back(_graphicsSystem);
	tempCoreSystemData.renderableObjectGroupList.push_back(tempRenderableVector);

	_coreSystem = new CoreSystem(tempCoreSystemData);
	_coreSystem->AddCameraMovement(new TestCamera(_coreSystem->GetCamera()));
	TestSystemConfigureFileImporterSuface* systemConfigureFileImporter = new TestSystemConfigureFileImporterSuface(nullptr, L"", _coreSystem->GetConfigEntityMap());
	systemConfigureFileImporter->FileImport();

	if (false == _coreSystem->Initialize())
		return false;

	if (false == _graphicsSystem->Initialize(hwnd))
		return false;

	TestInitialize_();

	return true;
}
bool SurfaceMain::Reset()
{
	_coreSystem->Reset();
	_graphicsSystem->Reset();
	return true;
}
void SurfaceMain::Update()
{
	_coreSystem->UpdateMain();
}


void SurfaceMain::TestInitialize_()
{
	//TEST: TestCode
	_sceneManager->CreateSceneObject(0);

}