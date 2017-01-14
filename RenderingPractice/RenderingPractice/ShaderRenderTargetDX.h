#pragma once
#include "IShaderRenderTargetImpl.h"

class ShaderRenderTargetDX : public IShaderRenderTargetImpl
{
public:
	ShaderRenderTargetDX(ID3D11Texture2D* renderTargetTex, ID3D11ShaderResourceView* shaderRenderView, ID3D11RenderTargetView* renderingTargetView);
	virtual ~ShaderRenderTargetDX();

	ID3D11Texture2D*				GetTexture()			{ return _renderTargetTex; }
	ID3D11RenderTargetView*			GetRenderTargetView()	{ return _renderingTargetView; }
	ID3D11ShaderResourceView*		GetShaderResourceView() { return _shaderRenderView; }

private:

	ID3D11Texture2D*				_renderTargetTex;
	ID3D11ShaderResourceView*		_shaderRenderView;
	ID3D11RenderTargetView*			_renderingTargetView;
};