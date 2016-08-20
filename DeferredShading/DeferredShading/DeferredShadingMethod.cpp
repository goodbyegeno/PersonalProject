#include "DeferredShadingMethod.h"
#include "RenderingManager.h"
#include "IDeferredShadingMethodImpl.h"
#include "ModelDynamicData.h"
#include "ModelStaticData.h"
#include "IRenderedObject.h"
DeferredShadingMethod::DeferredShadingMethod(RenderingManager* pRenderingMnanger)
{
	_renderingMananger = pRenderingMnanger;
	_renderingMethodImpl = nullptr;
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

void DeferredShadingMethod::Render(DeviceManager* deviceManager, ShaderManager* shaderManager, std::vector<IRenderedObject*>& renderRequestObjects, float deltaTime)
{
	_renderingMethodImpl->SetCameraMatrix();

	RenderGBuffer_	(deviceManager, shaderManager, renderRequestObjects, deltaTime);
	RenderLighting_	(deviceManager, shaderManager, renderRequestObjects, deltaTime);
	
	_renderingMethodImpl->ResetRenderTarget();

}

void DeferredShadingMethod::RenderGBuffer_(DeviceManager* deviceManager, ShaderManager* shaderManager, std::vector<IRenderedObject*>& renderRequestObjects, float deltaTime)
{
	//_renderingMethodImpl->SetConstVariables();
	_renderingMethodImpl->SettingShaderOptions();
	_renderingMethodImpl->SetRenderTarget();

	for (int objectsIndex = 0; objectsIndex < renderRequestObjects.size(); objectsIndex++)
	{
		const ModelDynamicData* modelDaynamicData = renderRequestObjects[objectsIndex]->GetModelDynamicData();
		const ModelStaticData* modelStaticData = renderRequestObjects[objectsIndex]->GetModelStaticData();

		const ORBITMesh* const* meshData = modelStaticData->GetMeshDatas();

		_renderingMethodImpl->SetWorldMatrix(matrix);
		_renderingMethodImpl->SetConstVariables();
		
		for (int meshIndex = 0; meshIndex < modelStaticData->GetMeshCount(); meshIndex++)
		{
			//subset
			_renderingMethodImpl->SetVertexBuffer()
			for ()
			{
				_renderingMethodImpl->SetMaterial();
				_renderingMethodImpl->RenderMesh();
			}
			
			/*
			ID3D11Buffer*  vertexBuffer = static_cast<ID3D11Buffer*>(meshData[meshIndex]->GetVertexBuffer());
			ID3D11Buffer* const* ppVertexBuffer = &vertexBuffer;

			_deviceContext->IASetVertexBuffers(0, , ppVertexBuffer, , );
			_deviceContext->IASetIndexBuffer(meshData[meshIndex]->GetIndexBuffer(), _dxHelper->GetIndexBufferFormat(meshData[meshIndex]->GetIndexBufferFormat()), 0);
			//_deviceWrapper->RenderMesh(meshData[meshIndex]));
			*/
			_renderingMethodImpl->RenderMesh();
		}

	}

	//_renderingMethodImpl->RenderMesh(renderRequestObjects);


}
void DeferredShadingMethod::RenderLighting_(DeviceManager* deviceManager, ShaderManager* shaderManager, std::vector<IRenderedObject*>& renderRequestObjects, float deltaTime)
{
	_renderingMethodImpl->RenderLighting(renderRequestObjects);
}
