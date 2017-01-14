#include "stdafx.h"
#include "RenderingOverviewDefault.h"
#include "RenderingManager.h"
#include "RenderingMethod.h"
#include "DeviceManager.h"
#include "GraphicsDevice.h"
RenderingOverviewDefault::RenderingOverviewDefault(RenderingManager* renderingManager) :
	_forwardHashCode(std::hash<std::wstring>{}(L"ForwardRendering")),
	_deferredHashCode(std::hash<std::wstring>{}(L"DeferredRendering")),
	RenderingOverviewBase(renderingManager)
{
}
RenderingOverviewDefault::~RenderingOverviewDefault()
{
}
void RenderingOverviewDefault::Render(DeviceManager* deviceManager, ShaderManager* shaderManager, std::unordered_map<size_t, std::vector<IRenderableObject*>>* renderingRequestMap, std::unordered_map<size_t, RenderMethod*>* renderingMethodMap)
{
	//start Rendering;
	//std::unordered_map<size_t, RenderMethod*>*	_renderingMethodMap;		//from RenderingManager
	std::unordered_map<size_t, RenderMethod*>::iterator itorForward = renderingMethodMap->find(_forwardHashCode);
	GraphicsDevice* device = deviceManager->GetDevice();
	device->BegineScene();

	if (renderingMethodMap->end() != itorForward)
	{
		std::unordered_map<size_t, std::vector<IRenderableObject*>>::iterator itorRequestObject = renderingRequestMap->find(_forwardHashCode);
		if (itorRequestObject != renderingRequestMap->end())
		{
			std::vector<IRenderableObject*>& forwardRenderedObject = itorRequestObject->second;
			itorForward->second->Render(deviceManager, shaderManager, forwardRenderedObject, 0.0f);
		}
	}
	std::unordered_map<size_t, RenderMethod*>::iterator itorDeferred = renderingMethodMap->find(_forwardHashCode);
	if (renderingMethodMap->end() != itorDeferred)
	{
		std::unordered_map<size_t, std::vector<IRenderableObject*>>::iterator itorRequestObject = renderingRequestMap->find(_deferredHashCode);

		if (renderingRequestMap->end() != itorRequestObject)
		{
			std::vector<IRenderableObject*>& deferredRenderedObject = itorRequestObject->second;
			itorForward->second->Render(deviceManager, shaderManager, deferredRenderedObject, 0.0f);
		}
	}

	//end Rendering
	device->EndScene();
}
bool RenderingOverviewDefault::Initialize()
{
	return __super::Initialize();
}
bool RenderingOverviewDefault::Reset()
{
	return __super::Initialize();
}