#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include "RenderEngineCommon.h"
#include <d3d11_2.h>
#include <directxmath.h>
#include <unordered_map>

class DXDevice
{
public:
	DXDevice();
	virtual ~DXDevice();

	bool Initilize();
	bool Reset();

	bool Render();
	bool RenderGBuffer();
private:

	bool LoadDevice_();

private:
	ID3D11Device*				m_pDevice;
	ID3D11DeviceContext*		m_pDeviceContext;
	IDXGISwapChain*				m_pSwapChain;
	ID3D11RenderTargetView*		m_pRenderTargetView;
	ID3D11Texture2D*			m_pDepthStencilBuffer;
	ID3D11DepthStencilState*	m_pDepthStencilState;
	ID3D11DepthStencilView*		m_pDepthStencilView;
	ID3D11RasterizerState*		m_pRasterState;
	ULONG						m_nVCMemory;

	std::unordered_map<UINT, ID3D11Texture2D*>			m_mapRenderTargetTex;
	std::unordered_map<UINT, ID3D11ShaderResourceView*>	m_mapShaderResourceView;
	std::unordered_map<UINT, ID3D11RenderTargetView*>	m_mapRenderTargetView;
	/*
	ID3D11Texture2D*				m_lstRenderTargetTex[static_cast<UINT>(RenderEngine::RenderTargetIndex::MAX)];
	ID3D11ShaderResourceView*		m_lstSRV			[static_cast<UINT>(RenderEngine::RenderTargetIndex::MAX)];
	ID3D11RenderTargetView*			m_lstRTV			[static_cast<UINT>(RenderEngine::RenderTargetIndex::MAX)];
	*/
};