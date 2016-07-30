#pragma once

#include "RenderEngineCommon.h"
#include "IDeferredShadingMethodImpl.h"
#include <d3d11_2.h>
#include <vector>
class DeviceManager;
class ShaderManager;
class IRenderedObject;
class ShaderRenderTargetDX;
class ShaderRenderTarget;

struct ShaderConstVariables
{
	DirectX::XMMATRIX				_viewMatrix;
	DirectX::XMMATRIX				_projMatrix;
	DirectX::XMMATRIX				_viewProjMatrix;
};

class DeferredShadingMethodDX : public IDeferredShadingMethodImpl
{
public:
	DeferredShadingMethodDX();
	virtual ~DeferredShadingMethodDX();

	bool Initialize(DeviceManager* deviceManager, ShaderManager* shaderManager);
	bool Reset(DeviceManager* deviceManager, ShaderManager* shaderManager);

	bool InitRenderTargets(ShaderRenderTarget** renderTargets, int renderTargetNum);

	virtual CoreEngine::GRAPHICSAPITYPE GetMiddleWareType() { return CoreEngine::GRAPHICSAPITYPE::DIRECTX;  }

	virtual bool SetCameraMatrix();
	virtual bool SettingShaderOptions();
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
	
	ShaderRenderTargetDX*			_renderTargets		[static_cast<int>(INDEXEDDEFERREDSHADINGRT::MAX)];
	
	ID3D11Texture2D*				_renderTargetTex	[static_cast<int>(INDEXEDDEFERREDSHADINGRT::MAX)];
	ID3D11ShaderResourceView*		_shaderRenderView	[static_cast<int>(INDEXEDDEFERREDSHADINGRT::MAX)];
	ID3D11RenderTargetView*			_renderingTargetView[static_cast<int>(INDEXEDDEFERREDSHADINGRT::MAX)];
	ID3D11DepthStencilView*			_depthStencilView;
	int								_renderTargetCount;

	ID3D11InputLayout*				_inputLayout;
	ID3D11VertexShader*				_vertexShader;
	ID3D11PixelShader*				_pixelShader;
	ID3D11ComputeShader*			_computeShader;
									
	size_t							_vertexShaderHash;
	size_t							_pixelShaderHash;
	size_t							_computeShaderHash;
	
	ShaderConstVariables			_shaderConstVariables;
	ID3D11Buffer*					_shaderConstVariableBuffer;

	
};