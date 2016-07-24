#pragma once

#include "RenderEngineCommon.h"
#include "IDeferredShadingMethodImpl.h"
#include <d3d11.h>
#include <vector>
class DeviceManager;
class ShaderManager;
class IRenderedObject;

class DeferredShadingMethodDX : public IDeferredShadingMethodImpl
{
public:
	DeferredShadingMethodDX();
	virtual ~DeferredShadingMethodDX();

	bool Initialize(DeviceManager* deviceManager, ShaderManager* shaderManager);
	bool Reset(DeviceManager* deviceManager, ShaderManager* shaderManager);

	virtual CoreEngine::GRAPHICSAPITYPE GetMiddleWareType() { return CoreEngine::GRAPHICSAPITYPE::DIRECTX;  }

	virtual bool SetMatrix();
	virtual bool SetShader();
	virtual bool SetConstVariables();
	virtual bool SetRenderTarget();
	virtual bool RenderMesh();
	virtual bool RenderLighting();
	

private:
	bool SetShader_(ShaderManager* shaderManager, ID3D11Device* deviceDX);
private:

	ShaderManager*					_shaderManager;
									
	ID3D11Device*					_device;
	ID3D11DeviceContext*			_deviceContext;
									
	ID3D11Texture2D*				_renderTargetTex[4];
	ID3D11ShaderResourceView*		_shaderRenderView[4];
	ID3D11RenderTargetView*			_renderingTargetView[4];
	ID3D11InputLayout*				_inputLayout;
									
	ID3D11VertexShader*				_vertexShader;
	ID3D11PixelShader*				_pixelShader;
	ID3D11ComputeShader*			_computeShader;
									
	size_t							_vertexShaderHash;
	size_t							_pixelShaderHash;
	size_t							_computeShaderHash;

};