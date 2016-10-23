#pragma once

class IShaderRenderTargetImpl;
class ShaderRenderTarget
{
public:
	ShaderRenderTarget(IShaderRenderTargetImpl* renderTargetImpl);
	virtual ~ShaderRenderTarget();

	IShaderRenderTargetImpl*	GetData() { return _shaderRenderTargetImpl;  }

private:

	IShaderRenderTargetImpl*	_shaderRenderTargetImpl;
};