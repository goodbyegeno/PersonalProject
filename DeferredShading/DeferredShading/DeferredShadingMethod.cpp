#include "stdafx.h"
#include "DeferredShadingMethod.h"
#include "RenderingManager.h"
#include "GraphicsSystem.h"
#include "IDeferredShadingMethodImpl.h"
#include "ModelDynamicData.h"
#include "ModelStaticData.h"
#include "IRenderedObject.h"
#include "CustomMatrix.h"
#include "ORBITMesh.h"
#include "ORBITMeshSubset.h"
#include "DeviceManager.h"
DeferredShadingMethod::DeferredShadingMethod(RenderingManager* renderingMnanger)
{
	_renderingMananger = renderingMnanger;
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
	_mSecPerFrame = static_cast<float>(1000) / static_cast<float>(_FPS);
	_currentMSecPerFrame = 0.0f;
	_graphicsDevice = _renderingMananger->GetDeviceManager()->GetDevice();

	return true;
}
bool DeferredShadingMethod::Reset()
{
	_VSync = _renderingMananger->IsVsyncOn();
	_FPS = _renderingMananger->GetFPS();
	_mSecPerFrame = static_cast<float>(1000) / static_cast<float>(_FPS);
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
		const ORBITMATRIX4x4 worldMatrix = ;
		const ORBITMesh* const* meshData = modelStaticData->GetMeshDatas();

		_renderingMethodImpl->SetWorldMatrix(&worldMatrix);
		_renderingMethodImpl->SetConstVariables();
		
		for (int meshIndex = 0; meshIndex < modelStaticData->GetMeshCount(); meshIndex++)
		{
			//subset
			const ORBITMeshSubset* meshSubsets = meshData[meshIndex]->GetSubset();
			int subsetCount = meshData[meshIndex]->GetSubsetCount();
			_renderingMethodImpl->SetVertexBuffer(meshData[meshIndex]);
			_renderingMethodImpl->SetSubsetVBIndicesInfo(meshData[meshIndex]->GetSubset());
			if (ORBITMesh::SUBSETINDEXMAPPINGTYPE::STORED == meshData[meshIndex]->GetSubsetIndexMappingType())
			{
				for (int subsetIndex = 0; subsetIndex < subsetCount; subsetIndex++)
				{
					_renderingMethodImpl->SetMaterial();
					//_renderingMethodImpl->SetSubsetVBIndicesInfo();
					_renderingMethodImpl->RenderMesh();


					//_renderingMethodImpl->RenderMesh();
				}
			}
			else if (ORBITMesh::SUBSETINDEXMAPPINGTYPE::LINEAR == meshData[meshIndex]->GetSubsetIndexMappingType())
			{
				for (int subsetIndex = 0; subsetIndex < subsetCount; subsetIndex++)
				{
					_renderingMethodImpl->SetMaterial();
					_renderingMethodImpl->RenderMesh();
				}
			}
			
			
			/*
			ID3D11Buffer*  vertexBuffer = static_cast<ID3D11Buffer*>(meshData[meshIndex]->GetVertexBuffer());
			ID3D11Buffer* const* ppVertexBuffer = &vertexBuffer;

			_deviceContext->IASetVertexBuffers(0, , ppVertexBuffer, , );
			_deviceContext->IASetIndexBuffer(meshData[meshIndex]->GetIndexBuffer(), _dxHelper->GetIndexBufferFormat(meshData[meshIndex]->GetIndexBufferFormat()), 0);
			//_deviceWrapper->RenderMesh(meshData[meshIndex]));
			*/
			//_renderingMethodImpl->RenderMesh();
		}

	}

	//_renderingMethodImpl->RenderMesh(renderRequestObjects);


}
void DeferredShadingMethod::RenderLighting_(DeviceManager* deviceManager, ShaderManager* shaderManager, std::vector<IRenderedObject*>& renderRequestObjects, float deltaTime)
{
	_renderingMethodImpl->RenderLighting(renderRequestObjects);
}
