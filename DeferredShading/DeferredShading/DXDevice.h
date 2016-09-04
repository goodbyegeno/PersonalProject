#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include "RenderEngineCommon.h"
#include <d3d11_4.h>
#include <directxmath.h>
#include <unordered_map>
#include "IGraphicsDevice.h"
class ORBITMesh;
class DXDevice : public IGraphcisDevice
{
public:
	DXDevice();
	virtual ~DXDevice();

	bool Initilize();
	bool Reset();

	void DrawPrimitive();
private:

	bool LoadDevice_(int screenWidth, int screenHeight);

private:
	ID3D11Device3*				_device;
	ID3D11DeviceContext3*		_deviceContext;
	IDXGISwapChain*				_swapChain;
	ID3D11RenderTargetView*		_renderTargetView;
	ID3D11Texture2D*			_depthStencilBuffer;
	ID3D11DepthStencilState*	_depthStencilState;
	ID3D11DepthStencilView*		_depthStencilView;
	ID3D11RasterizerState*		_rasterState;
	ULONG						_videoCardMem;

	std::unordered_map<UINT, ID3D11Texture2D*>			_renderTargetTex;
	std::unordered_map<UINT, ID3D11ShaderResourceView*>	_shaderResourceView;
	std::unordered_map<UINT, ID3D11RenderTargetView*>	_renderTargetView;
	/*
	ID3D11Texture2D*				m_lstRenderTargetTex[static_cast<UINT>(RenderEngine::RenderTargetIndex::MAX)];
	ID3D11ShaderResourceView*		m_lstSRV			[static_cast<UINT>(RenderEngine::RenderTargetIndex::MAX)];
	ID3D11RenderTargetView*			m_lstRTV			[static_cast<UINT>(RenderEngine::RenderTargetIndex::MAX)];
	*/
};