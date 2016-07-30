#include "ShaderRenderTargetDX.h"


ShaderRenderTargetDX::ShaderRenderTargetDX(ID3D11Texture2D* renderTargetTex, ID3D11ShaderResourceView* shaderRenderView, ID3D11RenderTargetView* renderingTargetView)
{
	_renderTargetTex		= renderTargetTex;
	_shaderRenderView		= shaderRenderView;
	_renderingTargetView	= renderingTargetView;
}
ShaderRenderTargetDX::~ShaderRenderTargetDX()
{
	if (_renderTargetTex)
		delete _renderTargetTex;
	
	if (_shaderRenderView)
		delete _shaderRenderView;
	
	if (_renderingTargetView)
		delete _renderingTargetView;
}