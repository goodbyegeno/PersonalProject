#pragma once
class IShaderRenderTargetImpl;
class IRenderedObject;

enum class INDEXEDDEFERREDSHADINGRT
{
	ALBEDO,
	NORMAL,
	POSITION,
	SPECULAR,
	MAX
};
class IDeferredShadingMethodImpl
{
public:
	

	IDeferredShadingMethodImpl() {}
	virtual ~IDeferredShadingMethodImpl() {}

	virtual bool Initialize(DeviceManager* deviceManager, ShaderManager* shaderManager) = 0;
	virtual bool Reset(DeviceManager* deviceManager, ShaderManager* shaderManager) = 0;

	virtual bool SetCameraMatrix() = 0;
	virtual bool SettingShaderOptions() = 0;
	virtual bool SetConstVariables() = 0;
	virtual bool SetRenderTarget() = 0;
	virtual bool RenderMesh(std::vector<IRenderedObject*>& renderRequestObjects) = 0;
	virtual bool RenderLighting(std::vector<IRenderedObject*>& renderRequestObjects) = 0;
	virtual bool ResetRenderTarget() = 0;

};