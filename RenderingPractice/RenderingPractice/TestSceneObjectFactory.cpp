#include "stdafx.h"
#include "TestSceneObjectFactory.h"
#include "TestSceneObject.h"
#include "RenderedObject.h"
#include "IGraphicsSystemFacade.h"
TestSceneObjectFactory::TestSceneObjectFactory()
{
}
TestSceneObjectFactory::~TestSceneObjectFactory()
{
}
//From ISceneObjectFactory
SceneObject* TestSceneObjectFactory::CreateSceneObject(size_t objectTypeKey, IGraphicsSystemFacade* graphicsSystem)
{
	SceneObject* testObject = new TestSceneObject(0);
	testObject->GetRenderedObject()->SetModelStaticData(graphicsSystem->GetStaticModel(0));
	return testObject;
}
