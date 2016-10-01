#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include "RenderEngineCommon.h"
#include <d3d11_4.h>
#include <directxmath.h>
#include <unordered_map>
#include "GraphicsDevice.h"
class ORBITMesh;
class DXDevice11_4 : public GraphicsDevice
{
public:
	DXDevice11_4();
	virtual ~DXDevice11_4();

	virtual bool Initialize(HWND hwnd);
	virtual bool Reset();

	virtual void* GetShader() { return nullptr; }

	virtual void* GetBuffer() { return _device; }

	void DrawPrimitive();
	ID3D11DeviceContext3* GetDeviceContext() { return _deviceContext; }
private:

	bool LoadDevice_(HWND hwnd);// (int screenWidth, int screenHeight);

private:
	ID3D11Device3*				_device;
	ID3D11DeviceContext3*		_deviceContext;
	IDXGISwapChain*				_swapChain;
	ID3D11RenderTargetView*		_backBufferRTV;
	ID3D11Texture2D*			_depthStencilBuffer;
	ID3D11DepthStencilState*	_depthStencilState;
	ID3D11DepthStencilView*		_depthStencilView;
	ID3D11RasterizerState*		_rasterState;
	ULONG						_videoCardMem;
	int							_screenWidth;
	int							_screenHeight;
	float						_fieldOfView;
	float						_screenAspect;
	float						_screenNear;
	float						_screenFar;
	DirectX::XMMATRIX			_projectionMatrix;

	std::unordered_map<UINT, ID3D11Texture2D*>			_renderTargetTex;
	std::unordered_map<UINT, ID3D11ShaderResourceView*>	_shaderResourceView;
	std::unordered_map<UINT, ID3D11RenderTargetView*>	_renderTargetViewMap;
	/*
	ID3D11Texture2D*				_renderTargetTex[static_cast<UINT>(RenderEngine::RenderTargetIndex::MAX)];
	ID3D11ShaderResourceView*		m_lstSRV			[static_cast<UINT>(RenderEngine::RenderTargetIndex::MAX)];
	ID3D11RenderTargetView*			m_lstRTV			[static_cast<UINT>(RenderEngine::RenderTargetIndex::MAX)];
	*/
};