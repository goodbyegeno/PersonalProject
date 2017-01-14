#pragma once

#include "RenderEngineCommon.h"

#include "GraphicsDevice.h"
class ORBITMesh;
class DXDevice11_4 : public GraphicsDevice
{
public:
	DXDevice11_4();
	virtual ~DXDevice11_4();

	virtual bool Initialize(HWND hwnd);
	virtual bool Reset();

	virtual bool	UpdateRenderResolution();
	virtual bool	UpdateBackBufferResolution();

	virtual void* GetShader() { return nullptr; }
	virtual void* GetBuffer() { return _device; }
	virtual void BegineScene();
	virtual void EndScene();

	void DrawPrimitive();
	ID3D11DeviceContext3*		GetDeviceContext()		{ return _deviceContext; }
	ID3D11DepthStencilState*	GetStencileState()		{ return _depthStencilState; }
	ID3D11DepthStencilView*		GetDepthStencilView()	{ return _depthStencilView; }
	ID3D11BlendState*			GetBlendState()			{ return _blendState; }
	int							GetRenderingResolutionWidth() { return _renderingResoWidth; }
	int							GetRenderingResolutionHeight() { return _renderingResoHeight; }

private:
	bool ReleaseDevice_();
	bool LoadDevice_(HWND hwnd);// (int screenWidth, int screenHeight);

private:
	IDXGIAdapter*				_adapter;
	IDXGIOutput*				_adapterOutput;
	ID3D11Device3*				_device;
	ID3D11DeviceContext3*		_deviceContext;
	IDXGISwapChain*				_swapChain;
	ID3D11RenderTargetView*		_backBufferRTV;
	ID3D11Texture2D*			_depthStencilBuffer;
	ID3D11DepthStencilState*	_depthStencilState;
	ID3D11DepthStencilView*		_depthStencilView;
	ID3D11RasterizerState*		_rasterState;
	ID3D11BlendState1*			_blendState;
	ULONG						_videoCardMem;
	
	DirectX::XMMATRIX			_projectionMatrix;

	HWND						_hwnd;

	/*
	std::unordered_map<UINT, ID3D11Texture2D*>			_renderTargetTex;
	std::unordered_map<UINT, ID3D11ShaderResourceView*>	_shaderResourceView;
	std::unordered_map<UINT, ID3D11RenderTargetView*>	_renderTargetViewMap;
	*/
	/*
	ID3D11Texture2D*				_renderTargetTex[static_cast<UINT>(RenderEngine::RenderTargetIndex::MAX)];
	ID3D11ShaderResourceView*		m_lstSRV			[static_cast<UINT>(RenderEngine::RenderTargetIndex::MAX)];
	ID3D11RenderTargetView*			m_lstRTV			[static_cast<UINT>(RenderEngine::RenderTargetIndex::MAX)];
	*/
};