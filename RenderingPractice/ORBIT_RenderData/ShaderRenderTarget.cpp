#include "stdafx.h"
#include "ShaderRenderTarget.h"
#include "IShaderRenderTargetImpl.h"
#include "ShaderRenderTargetDX.h"


ShaderRenderTarget::ShaderRenderTarget(IShaderRenderTargetImpl* renderTargetImpl) :
	_shaderRenderTargetImpl(renderTargetImpl)
{
}
ShaderRenderTarget::~ShaderRenderTarget()
{
	if (_shaderRenderTargetImpl)
		delete _shaderRenderTargetImpl;
}
