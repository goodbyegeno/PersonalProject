#include "stdafx.h"
#include "DXDevice.h"
#include "CameraBase.h"
#include "ORBITMesh.h"

DXDevice::DXDevice()
{
	_device				= nullptr;
	_deviceContext		= nullptr;
	_swapChain			= nullptr;
	//_renderTargetView	= nullptr;
	_depthStencilBuffer	= nullptr;
	_depthStencilState	= nullptr;
	_depthStencilView	= nullptr;
	_rasterState		= nullptr;
	
	for( int iRT = 0; iRT < static_cast<UINT>(CoreEngine::GRAPHICSAPITYPE::MAX); iRT++)
	{ 
		_renderTargetTex[iRT] = nullptr;
		_shaderResourceView[iRT] = nullptr;
		_renderTargetView[iRT] = nullptr;
	}
	
}
DXDevice::~DXDevice()
{

}
bool DXDevice::Initilize()
{
	LoadDevice_(1024, 1024);
	return true;
}


bool DXDevice::Reset()
{
	return true;
}

bool DXDevice::LoadDevice_(int screenWidth, int screenHeight)
{
	HRESULT result;
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapterOutput;
	DXGI_MODE_DESC* displayModeList;
	DXGI_ADAPTER_DESC adapterDesc;
	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	D3D_FEATURE_LEVEL featureLevel;
	ID3D11Texture2D* backBufferPtr;
	D3D11_TEXTURE2D_DESC depthBufferDesc;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	D3D11_RASTERIZER_DESC rasterDesc;
	D3D11_VIEWPORT viewport;
	float fieldOfView, screenAspect;

	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(result))
		return false;

	result = factory->EnumAdapters(0, &adapter);
	if (FAILED(result))
		return false;

	result = adapter->EnumOutputs(0, &adapterOutput);
	if (FAILED(result))
		return false;

	UINT numModes = 0;
	bool isHDRMonitor = true;
	int numerator, denominator;

	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
	if (FAILED(result))
		return false;
	
	// Create a list to hold all the possible display modes for this monitor/video card combination.
	displayModeList = new DXGI_MODE_DESC[numModes];
	if (!displayModeList)
		return false;

	numerator = displayModeList[0].RefreshRate.Numerator;
	denominator = displayModeList[0].RefreshRate.Denominator;
	
	result = adapter->GetDesc(&adapterDesc);
	if (FAILED(result))
		return false;

	_videoCardMem = static_cast<ULONG>(adapterDesc.DedicatedVideoMemory);

	delete[] displayModeList;
	displayModeList = nullptr;

	adapterOutput->Release();
	adapterOutput = nullptr;

	adapter->Release();
	adapter = nullptr;

	factory->Release();
	factory = nullptr;

	memset(&swapChainDesc, 0, sizeof(swapChainDesc));

	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Width = screenWidth;
	swapChainDesc.BufferDesc.Height = screenHeight;

	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	swapChainDesc.Flags = 0;
	featureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_1;

	result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, &_swapChain, &_device, NULL, &_deviceContext);
	if (FAILED(result))
		return false;
	
	result = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&backBufferPtr));
	if (FAILED(result))
		return false;

	result = _device->CreateRenderTargetView(backBufferPtr, NULL, &_renderTargetView);
	if (FAILED(result))
		return false;

	backBufferPtr = nullptr;
	backBufferPtr->Release();
	
	memset(&depthBufferDesc, 0, sizeof(depthBufferDesc));

	depthBufferDesc.Width = screenWidth;
	depthBufferDesc.Height = screenHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	result = _device->CreateTexture2D(&depthBufferDesc, NULL, &_depthStencilBuffer);
	if (FAILED(result))
		return false;

	memset(&depthStencilDesc, 0, sizeof(depthStencilDesc));

	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	result = _device->CreateDepthStencilState(&depthStencilDesc, &_depthStencilState);
	if (FAILED(result))
		return false;
	_deviceContext->OMSetDepthStencilState(_depthStencilState, 1);

	memset(&depthStencilViewDesc, 0, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;

	result = _device->CreateDepthStencilView(_depthStencilBuffer, &depthStencilViewDesc, &_depthStencilView);
	if (FAILED(result))
		return false;

	rasterDesc.AntialiasedLineEnable = false;
	rasterDesc.CullMode = D3D11_CULL_BACK;
	rasterDesc.DepthBias = 0;
	rasterDesc.DepthBiasClamp = 0.0f;
	rasterDesc.DepthClipEnable = true;
	rasterDesc.FillMode = D3D11_FILL_SOLID;
	rasterDesc.FrontCounterClockwise = false;
	rasterDesc.MultisampleEnable = false;
	rasterDesc.ScissorEnable = false;
	rasterDesc.SlopeScaledDepthBias = 0.0f;

	result = _device->CreateRasterizerState(&rasterDesc, &_rasterState);
	if (FAILED(result))
		return false;

	_deviceContext->RSSetState(_rasterState);

	viewport.Width = (float)screenWidth;
	viewport.Height = (float)screenHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	_deviceContext->RSSetViewports(1, &viewport);

	fieldOfView = 3.141592654f / 4.0f;
	screenAspect = (float)screenWidth / (float)screenHeight;

	_projectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenDepth);
	D3D11_TEXTURE2D_DESC normalRTTexDesc;
	normalRTTexDesc.Width = screenWidth;
	normalRTTexDesc.Height = screenHeight;
	normalRTTexDesc.MipLevels = 1;
	normalRTTexDesc.ArraySize = 1;
	normalRTTexDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	normalRTTexDesc.SampleDesc.Count = 1;
	normalRTTexDesc.SampleDesc.Quality = 0;
	normalRTTexDesc.Usage = D3D11_USAGE_DEFAULT;
	normalRTTexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	normalRTTexDesc.CPUAccessFlags = 0;
	normalRTTexDesc.MiscFlags = 0;

	Result = m_pDevice->CreateTexture2D(&NormalRTTexDesc, NULL, &m_lstRenderTargetTex[static_cast<UINT>(RenderEngine::RenderTargetIndex::NORMAL)]);
	if (FAILED(Result))
		return false;

	Result = m_pDevice->CreateRenderTargetView(	m_lstRenderTargetTex[static_cast<UINT>(RenderEngine::RenderTargetIndex::NORMAL)], 
												NULL, 
												&m_lstRTV[static_cast<UINT>(RenderEngine::RenderTargetIndex::NORMAL)]);
	if (FAILED(Result))
		return false;

	Result = m_pDevice->CreateShaderResourceView(	m_lstRenderTargetTex[static_cast<UINT>(RenderEngine::RenderTargetIndex::NORMAL)],
													NULL,
													&m_lstSRV[static_cast<UINT>(RenderEngine::RenderTargetIndex::NORMAL)]);
	if (FAILED(Result))
		return false;

	D3D11_TEXTURE2D_DESC AlbedoRTTexDesc;
	AlbedoRTTexDesc.Width = nScreenWidth;
	AlbedoRTTexDesc.Height = nScreenHeight;
	AlbedoRTTexDesc.MipLevels = 1;
	AlbedoRTTexDesc.ArraySize = 1;
	AlbedoRTTexDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	AlbedoRTTexDesc.SampleDesc.Count = 1;
	AlbedoRTTexDesc.SampleDesc.Quality = 0;
	AlbedoRTTexDesc.Usage = D3D11_USAGE_DEFAULT;
	AlbedoRTTexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	AlbedoRTTexDesc.CPUAccessFlags = 0;
	AlbedoRTTexDesc.MiscFlags = 0;

	Result = m_pDevice->CreateTexture2D(&AlbedoRTTexDesc, NULL, &m_lstRenderTargetTex[static_cast<UINT>(RenderEngine::RenderTargetIndex::ALBEDO)]);
	if (FAILED(Result))
		return false;

	Result = m_pDevice->CreateRenderTargetView(m_lstRenderTargetTex[static_cast<UINT>(RenderEngine::RenderTargetIndex::ALBEDO)],
		NULL,
		&m_lstRTV[static_cast<UINT>(RenderEngine::RenderTargetIndex::ALBEDO)]);
	if (FAILED(Result))
		return false;

	Result = m_pDevice->CreateShaderResourceView(m_lstRenderTargetTex[static_cast<UINT>(RenderEngine::RenderTargetIndex::ALBEDO)],
		NULL,
		&m_lstSRV[static_cast<UINT>(RenderEngine::RenderTargetIndex::ALBEDO)]);
	if (FAILED(Result))
		return false;

	D3D11_TEXTURE2D_DESC DepthRTTexDesc;
	DepthRTTexDesc.Width = nScreenWidth;
	DepthRTTexDesc.Height = nScreenHeight;
	DepthRTTexDesc.MipLevels = 1;
	DepthRTTexDesc.ArraySize = 1;
	DepthRTTexDesc.Format = DXGI_FORMAT_R16G16_FLOAT;
	DepthRTTexDesc.SampleDesc.Count = 1;
	DepthRTTexDesc.SampleDesc.Quality = 0;
	DepthRTTexDesc.Usage = D3D11_USAGE_DEFAULT;
	DepthRTTexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	DepthRTTexDesc.CPUAccessFlags = 0;
	DepthRTTexDesc.MiscFlags = 0;

	Result = m_pDevice->CreateTexture2D(&DepthRTTexDesc, NULL, &m_lstRenderTargetTex[static_cast<UINT>(RenderEngine::RenderTargetIndex::POSITION)]);
	if (FAILED(Result))
		return false;

	Result = m_pDevice->CreateRenderTargetView(m_lstRenderTargetTex[static_cast<UINT>(RenderEngine::RenderTargetIndex::POSITION)],
		NULL,
		&m_lstRTV[static_cast<UINT>(RenderEngine::RenderTargetIndex::POSITION)]);
	if (FAILED(Result))
		return false;

	Result = m_pDevice->CreateShaderResourceView(m_lstRenderTargetTex[static_cast<UINT>(RenderEngine::RenderTargetIndex::POSITION)],
		NULL,
		&m_lstSRV[static_cast<UINT>(RenderEngine::RenderTargetIndex::POSITION)]);
	if (FAILED(Result))
		return false;

	D3D11_TEXTURE2D_DESC SpecularRTTexDesc;
	SpecularRTTexDesc.Width = nScreenWidth;
	SpecularRTTexDesc.Height = nScreenHeight;
	SpecularRTTexDesc.MipLevels = 1;
	SpecularRTTexDesc.ArraySize = 1;
	SpecularRTTexDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SpecularRTTexDesc.SampleDesc.Count = 1;
	SpecularRTTexDesc.SampleDesc.Quality = 0;
	SpecularRTTexDesc.Usage = D3D11_USAGE_DEFAULT;
	SpecularRTTexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	SpecularRTTexDesc.CPUAccessFlags = 0;
	SpecularRTTexDesc.MiscFlags = 0;

	Result = m_pDevice->CreateTexture2D(&SpecularRTTexDesc, NULL, &m_lstRenderTargetTex[static_cast<UINT>(RenderEngine::RenderTargetIndex::SPECULAR)]);
	if (FAILED(Result))
		return false;

	Result = m_pDevice->CreateRenderTargetView(m_lstRenderTargetTex[static_cast<UINT>(RenderEngine::RenderTargetIndex::SPECULAR)],
		NULL,
		&m_lstRTV[static_cast<UINT>(RenderEngine::RenderTargetIndex::SPECULAR)]);
	if (FAILED(Result))
		return false;

	Result = m_pDevice->CreateShaderResourceView(m_lstRenderTargetTex[static_cast<UINT>(RenderEngine::RenderTargetIndex::SPECULAR)],
		NULL,
		&m_lstSRV[static_cast<UINT>(RenderEngine::RenderTargetIndex::SPECULAR)]);
	if (FAILED(Result))
		return false;
	
	return true;
}


void DXDevice::RenderMesh(const ORBITMesh* meshData) const
{



}