#pragma once

class IDeferredShadingMethodImpl
{
public:
	IDeferredShadingMethodImpl() {}
	virtual ~IDeferredShadingMethodImpl() {}

	virtual bool Initialize(ShaderManager* pShaderManager) = 0;
	virtual bool Reset(ShaderManager* pShaderManager) = 0;

	virtual bool SetMatrix() = 0;
	virtual bool SetShader() = 0;
	virtual bool SetConstVariables() = 0;
	virtual bool SetRenderTarget() = 0;
	virtual bool RenderMesh() = 0;
	virtual bool RenderLighting() = 0;

};