#include "stdafx.h"
#include "ForwardShadingMethod.h"
#include "GraphicsDevice.h"
#include "ForwardShadingMethodDX.h"
#include "ModelDynamicData.h"
#include "ModelStaticData.h"
#include "IRenderableObject.h"
#include "ORBITMesh.h"
#include "ORBITMeshSubset.h"
#include "RenderingManager.h"
#include "DeviceManager.h"
#include "GraphicsSystem.h"
ForwardShadingMethod::ForwardShadingMethod(GraphicsSystem* graphicSystem) :
	_graphicsSystem(graphicSystem),
	RenderMethod(std::hash<std::wstring>{}(L"ForwardRendering"))
{
	_renderingMananger = _graphicsSystem->GetRenderingManager();
}

ForwardShadingMethod::~ForwardShadingMethod()
{
	if (_renderingMethodImpl)
		delete _renderingMethodImpl;
}

bool ForwardShadingMethod::Initialize()
{
	_VSync = _renderingMananger->IsVsyncOn();
	_FPS = _renderingMananger->GetTargetFPS();
	_mSecPerFrame = static_cast<float>(1000) / static_cast<float>(_FPS);
	_currentMSecPerFrame = 0.0f;
	_graphicsDevice = _renderingMananger->GetDeviceManager()->GetDevice();
	CreateRenderingMethodImpl_();
	if (false == _renderingMethodImpl->Initialize(_renderingMananger->GetDeviceManager(), _graphicsSystem->GetShaderManager()))
		return false;


	return true;
}
bool ForwardShadingMethod::Reset()
{
	_VSync = _renderingMananger->IsVsyncOn();
	_FPS = _renderingMananger->GetTargetFPS();
	_mSecPerFrame = static_cast<float>(1000) / static_cast<float>(_FPS);
	_currentMSecPerFrame = 0.0f;

	return true;
}
void ForwardShadingMethod::Render(DeviceManager* deviceManager, ShaderManager* shaderManager, std::vector<IRenderableObject*>& renderRequestObjects, float deltaTime)
{
	//_renderingMethodImpl->SetConstVariables();
	_renderingMethodImpl->SettingShaderOptions();
	_renderingMethodImpl->SetRenderTarget();

	for (int objectsIndex = 0; objectsIndex < renderRequestObjects.size(); objectsIndex++)
	{
		const ModelDynamicData* modelDaynamicData = renderRequestObjects[objectsIndex]->GetModelDynamicData();
		const ModelStaticData* modelStaticData = renderRequestObjects[objectsIndex]->GetModelStaticData();
		const ORBITMATRIX4x4* worldMatrix = renderRequestObjects[objectsIndex]->GetWorldMatrix();
		const ORBITMesh* const* meshData = modelStaticData->GetMeshDatas();

		_renderingMethodImpl->SetWorldMatrix(worldMatrix);
		_renderingMethodImpl->SetConstVariables();

		for (int meshIndex = 0; meshIndex < modelStaticData->GetMeshCount(); meshIndex++)
		{
			//subset
			ORBITMeshSubset** meshSubsets = meshData[meshIndex]->GetSubset();
			int subsetCount = meshData[meshIndex]->GetSubsetCount();
			_renderingMethodImpl->SetVertexBuffer(meshData[meshIndex]);
			for (int subsetIndex = 0; subsetIndex < subsetCount; subsetIndex++)
			{
				_renderingMethodImpl->SetSubsetVBIndicesInfo(meshSubsets[subsetIndex]);
				if (ORBITMesh::SUBSETINDEXMAPPINGTYPE::STORED == meshData[meshIndex]->GetSubsetIndexMappingType())
				{
					_renderingMethodImpl->SetMaterial(meshSubsets[subsetIndex]->GetMaterial());
					_renderingMethodImpl->RenderMesh();
				}
				else if (ORBITMesh::SUBSETINDEXMAPPINGTYPE::LINEAR == meshData[meshIndex]->GetSubsetIndexMappingType())
				{
					_renderingMethodImpl->SetMaterial(meshSubsets[subsetIndex]->GetMaterial());
					_renderingMethodImpl->RenderMesh();
				}
			}
		}
	}
}
bool ForwardShadingMethod::CreateRenderingMethodImpl_()
{
	switch (_graphicsDevice->GetGraphicsAPIType())
	{
	case RenderEngine::GRAPHICSAPITYPE::DIRECTX11_4:
		_renderingMethodImpl = new ForwardShadingMethodDX();
		break;
	case RenderEngine::GRAPHICSAPITYPE::OPENGL:
		break;

	}
	return true;
}