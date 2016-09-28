#pragma once

class IShaderRenderTargetImpl;
class ShaderRenderTarget
{
public:
	ShaderRenderTarget();
	virtual ~ShaderRenderTarget();

	IShaderRenderTargetImpl*	GetData() { return _shaderRenderTargetImpl;  }

private:

	IShaderRenderTargetImpl*	_shaderRenderTargetImpl;
};