#include "DeferredShadingMethod.h"
#include "RenderingManager.h"
#include "IDeferredShadingMethodImpl.h"

DeferredShadingMethod::DeferredShadingMethod(RenderingManager* pRenderingMnanger)
{
	_renderingMananger = pRenderingMnanger;
	_rendingMethodImpl = nullptr;
	_VSync = false;
	_mSecPerFrame = 0.0f;
	_currentMSecPerFrame = 0.0f;
	_FPS = 0;
}
DeferredShadingMethod::~DeferredShadingMethod()
{

}

bool DeferredShadingMethod::Initialize()
{
	_VSync = _renderingMananger->IsVsyncOn();
	_FPS = _renderingMananger->GetFPS();
	_mSecPerFrame = 1000 / _FPS; 
	_currentMSecPerFrame = 0.0f;

	return true;
}
bool DeferredShadingMethod::Reset()
{
	_VSync = _renderingMananger->IsVsyncOn();
	_FPS = _renderingMananger->GetFPS();
	_mSecPerFrame = 1000 / _FPS;
	_currentMSecPerFrame = 0.0f;

	return true;
}

void DeferredShadingMethod::Render(DeviceManager* deviceManager, ShaderManager* shaderManager, std::vector<IRenderedObject>* rederRequestObjects, float deltaTime)
{
	_rendingMethodImpl->SetCameraMatrix();

	RenderGBuffer_	(deviceManager, shaderManager, rederRequestObjects, deltaTime);
	RenderLighting_	(deviceManager, shaderManager, rederRequestObjects, deltaTime);

}

void DeferredShadingMethod::RenderGBuffer_(DeviceManager* deviceManager, ShaderManager* shaderManager, std::vector<IRenderedObject>* rederRequestObjects, float deltaTime)
{
	_rendingMethodImpl->SettingShaderOptions();
	_rendingMethodImpl->SetConstVariables();
	_rendingMethodImpl->SetRenderTarget();
	_rendingMethodImpl->RenderMesh();
}
void DeferredShadingMethod::RenderLighting_(DeviceManager* deviceManager, ShaderManager* shaderManager, std::vector<IRenderedObject>* rederRequestObjects, float deltaTime)
{
	_rendingMethodImpl->RenderLighting();
}
