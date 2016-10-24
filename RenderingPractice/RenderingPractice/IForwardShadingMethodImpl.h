#pragma once
class DeviceManager;
class IShaderRenderTargetImpl;
class IRenderableObject;
class ORBITMATRIX4x4;
class ModelStaticData;
class ORBITMesh;
class ORBITMeshSubset;
class ORBITMaterial;
class ShaderManager;
class RenderTargetManager;

#include <vector>


class IForwardShadingMethodImpl
{
public:

	IForwardShadingMethodImpl() {}
	virtual ~IForwardShadingMethodImpl() {}

	virtual bool Initialize(DeviceManager* deviceManager, ShaderManager* shaderManager, RenderTargetManager* renderTargetManager) = 0;
	virtual bool Reset(DeviceManager* deviceManager, ShaderManager* shaderManager) = 0;

	virtual bool SetWorldMatrix(const ORBITMATRIX4x4* worldMatrix) = 0;
	virtual bool SetCameraMatrix() = 0;
	virtual bool SettingShaderOptions() = 0;
	virtual bool SetConstVariables() = 0;
	virtual bool SetRenderTarget() = 0;
	virtual bool SetVertexBuffer(const ORBITMesh* mesh) const = 0;
	virtual bool SetSubsetVBIndicesInfo(const ORBITMeshSubset* subsetData) = 0;
	virtual bool SetMaterial(const ORBITMaterial* material) = 0;
	virtual bool RenderMesh() = 0;
	virtual bool ResetRenderTarget() = 0;
	virtual bool CreateVertexBuffer(int vertexCount, int indexCount, ORBITVertex* verticesOrigin, UINT* indicesOrigin, ORBITMesh* outMeshData) = 0;


};