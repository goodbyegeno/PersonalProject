#include "DXDevice.h"
#include "CameraBase.h"

DXDevice::DXDevice()
{
	m_pDevice				= nullptr;
	m_pDeviceContext		= nullptr;
	m_pSwapChain			= nullptr;
	m_pRenderTargetView		= nullptr;
	m_pDepthStencilBuffer	= nullptr;
	m_pDepthStencilState	= nullptr;
	m_pDepthStencilView		= nullptr;
	m_pRasterState			= nullptr;

	for( int iRT = 0; iRT < static_cast<UINT>(CoreEngine::GRAPHICSAPITYPE::MAX); iRT++)
	{ 
		_renderTargetTex[iRT] = nullptr;
		_shaderRenderView[iRT] = nullptr;
		_renderingTargetView[iRT] = nullptr;
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

	m_nVCMemory = static_cast<ULONG>(adapterDesc.DedicatedVideoMemory);

	delete[] displayModeList;
	displayModeList = nullptr;

	adapterOutput->Release();
	adapterOutput = nullptr;

	adapter->Release();
	adapter = nullptr;

	factory->Release();
	factory = nullptr;

	memset(&SwapChainDesc, 0, sizeof(SwapChainDesc));

	SwapChainDesc.BufferCount = 2;
	SwapChainDesc.BufferDesc.Width = screenWidth;
	SwapChainDesc.BufferDesc.Height = screenHeight;

	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;

	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	SwapChainDesc.Flags = 0;
	FeatureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_1;

	result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &FeatureLevel, 1, D3D11_SDK_VERSION, &SwapChainDesc, &m_pSwapChain, &m_pDevice, NULL, &m_pDeviceContext);
	if (FAILED(result))
		return false;
	
	result = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&backBufferPtr));
	if (FAILED(result))
		return false;

	result = m_pDevice->CreateRenderTargetView(backBufferPtr, NULL, &_renderTargetView);
	if (FAILED(result))
		return false;

	backBufferPtr = nullptr;
	backBufferPtr->Release();
	
	memset(&DepthBufferDesc, 0, sizeof(DepthBufferDesc));

	DepthBufferDesc.Width = screenWidth;
	DepthBufferDesc.Height = screenHeight;
	DepthBufferDesc.MipLevels = 1;
	DepthBufferDesc.ArraySize = 1;
	DepthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DepthBufferDesc.SampleDesc.Count = 1;
	DepthBufferDesc.SampleDesc.Quality = 0;
	DepthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	DepthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	DepthBufferDesc.CPUAccessFlags = 0;
	DepthBufferDesc.MiscFlags = 0;

	result = m_pDevice->CreateTexture2D(&DepthBufferDesc, NULL, &m_pDepthStencilBuffer);
	if (FAILED(result))
		return false;

	memset(&depthStencilDesc, 0, sizeof(depthStencilDesc));

	DepthStencilDesc.DepthEnable = true;
	DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	DepthStencilDesc.StencilEnable = true;
	DepthStencilDesc.StencilReadMask = 0xFF;
	DepthStencilDesc.StencilWriteMask = 0xFF;

	DepthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	DepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	DepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	DepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	DepthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	DepthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	DepthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	DepthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	Result = m_pDevice->CreateDepthStencilState(&DepthStencilDesc, &m_pDepthStencilState);
	if (FAILED(Result))
		return false;
	m_pDeviceContext->OMSetDepthStencilState(m_pDepthStencilState, 1);

	memset(&DepthStencilViewDesc, 0, sizeof(DepthStencilViewDesc));
	DepthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	DepthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	DepthStencilViewDesc.Texture2D.MipSlice = 0;

	Result = m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, &DepthStencilViewDesc, &m_pDepthStencilView);
	if (FAILED(Result))
		return false;

	RasterDesc.AntialiasedLineEnable = false;
	RasterDesc.CullMode = D3D11_CULL_BACK;
	RasterDesc.DepthBias = 0;
	RasterDesc.DepthBiasClamp = 0.0f;
	RasterDesc.DepthClipEnable = true;
	RasterDesc.FillMode = D3D11_FILL_SOLID;
	RasterDesc.FrontCounterClockwise = false;
	RasterDesc.MultisampleEnable = false;
	RasterDesc.ScissorEnable = false;
	RasterDesc.SlopeScaledDepthBias = 0.0f;

	Result = m_pDevice->CreateRasterizerState(&RasterDesc, &m_pRasterState);
	if (FAILED(Result))
		return false;

	m_pDeviceContext->RSSetState(m_pRasterState);

	Viewport.Width = (float)nScreenWidth;
	Viewport.Height = (float)nScreenHeight;
	Viewport.MinDepth = 0.0f;
	Viewport.MaxDepth = 1.0f;
	Viewport.TopLeftX = 0.0f;
	Viewport.TopLeftY = 0.0f;

	m_pDeviceContext->RSSetViewports(1, &Viewport);

	fieldOfView = 3.141592654f / 4.0f;
	screenAspect = (float)nScreenWidth / (float)nScreenHeight;

	m_matProjectionMatrix = XMMatrixPerspectiveFovLH(fieldOfView, screenAspect, screenNear, screenDepth);

	D3D11_TEXTURE2D_DESC NormalRTTexDesc;
	NormalRTTexDesc.Width = nScreenWidth;
	NormalRTTexDesc.Height = nScreenHeight;
	NormalRTTexDesc.MipLevels = 1;
	NormalRTTexDesc.ArraySize = 1;
	NormalRTTexDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	NormalRTTexDesc.SampleDesc.Count = 1;
	NormalRTTexDesc.SampleDesc.Quality = 0;
	NormalRTTexDesc.Usage = D3D11_USAGE_DEFAULT;
	NormalRTTexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	NormalRTTexDesc.CPUAccessFlags = 0;
	NormalRTTexDesc.MiscFlags = 0;

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
