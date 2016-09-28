#include "stdafx.h"
#include "RenderingOverviewDefault.h"
#include "RenderingManager.h"
#include "RenderingMethod.h"
RenderingOverviewDefault::RenderingOverviewDefault(RenderingManager* renderingManager) :
	_forwardHashCode(std::hash<std::wstring>{}(L"forward")),
	_deferredHashCode(std::hash<std::wstring>{}(L"deferred")),
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
	if (itorForward != renderingMethodMap->end())
	{
		std::unordered_map<size_t, std::vector<IRenderableObject*>>::iterator itorRequestObject = renderingRequestMap->find(_forwardHashCode);
		if (itorRequestObject != renderingRequestMap->end())
		{
			std::vector<IRenderableObject*>& forwardRenderedObject = itorRequestObject->second;
			itorForward->second->Render(deviceManager, shaderManager, forwardRenderedObject, 0.0f);
		}
	}
	std::unordered_map<size_t, RenderMethod*>::iterator itorDeferred = renderingMethodMap->find(_forwardHashCode);
	if (itorDeferred != renderingMethodMap->end())
	{
		std::unordered_map<size_t, std::vector<IRenderableObject*>>::iterator itorRequestObject = renderingRequestMap->find(_deferredHashCode);

		if (itorRequestObject != renderingRequestMap->end())
		{
			std::vector<IRenderableObject*>& deferredRenderedObject = itorRequestObject->second;
			itorForward->second->Render(deviceManager, shaderManager, deferredRenderedObject, 0.0f);

		}
	}
	
	//end Rendering
}
bool RenderingOverviewDefault::Initialize()
{
	return __super::Initialize();
}
bool RenderingOverviewDefault::Reset()
{
	return __super::Initialize();
}