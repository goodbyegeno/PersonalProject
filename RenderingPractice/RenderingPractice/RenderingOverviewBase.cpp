#include "stdafx.h"
#include "RenderingOverviewBase.h"
#include "RenderingManager.h"
RenderingOverviewBase::RenderingOverviewBase(RenderingManager* renderingManager) :
	_renderingManager(renderingManager)
{
}
RenderingOverviewBase::~RenderingOverviewBase()
{

}

bool RenderingOverviewBase::Initialize()
{
	//_renderingMethodMap = _renderingManager->GetRenderingMethodMap();

	return true;
}
bool RenderingOverviewBase::Reset()
{
	//_renderingMethodMap = _renderingManager->GetRenderingMethodMap();

	return true;
}
void RenderingOverviewBase::Render(DeviceManager* deviceManager, ShaderManager* shaderManager, std::unordered_map<size_t, std::vector<IRenderableObject*>>* renderingRequestMap, std::unordered_map<size_t, RenderMethod*>* renderingMethodMap)
{
}
