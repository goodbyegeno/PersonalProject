#include "stdafx.h"
#include "DXDevice11_4.h"
#include "CameraBase.h"
#include "ORBITMesh.h"
#include "CoreSystem.h"
#include <unordered_map>
#include "SystemConfigureFileImporter.h"
DXDevice11_4::DXDevice11_4() :
	_device(nullptr),
	_deviceContext(nullptr),
	_swapChain(nullptr),
	_depthStencilBuffer(nullptr),
	_depthStencilState(nullptr),
	_depthStencilView(nullptr),
	_rasterState(nullptr),
	_videoCardMem(0),
	_screenWidth(0),
	_screenHeight(0),
	_fieldOfView(0.0f),
	_screenAspect(0.0f),
	_screenNear(0.0f),
	_screenFar(0.0f),
	_backBufferRTV(nullptr),
	GraphicsDevice(RenderEngine::GRAPHICSAPITYPE::DIRECTX11_4)
{
	for( int iRT = 0; iRT < static_cast<UINT>(RenderEngine::INDEXEDDEFERREDSHADINGRT::MAX); iRT++)
	{ 
		_renderTargetTex[iRT] = nullptr;
		_shaderResourceView[iRT] = nullptr;
		_renderTargetViewMap[iRT] = nullptr;
		//_renderTargetView[iRT] = nullptr;
	}
	
}
DXDevice11_4::~DXDevice11_4()
{

}
bool DXDevice11_4::Initialize(HWND hwnd)
{
	//_fieldOfView = 3.141592654f / 4.0f;
	SystemConfigureEntity* tempEntity = coreSystem->GetConfigValue(std::hash<std::wstring>{}(L"NativeResolutionWidth"));
	if(nullptr != tempEntity)
		_screenWidth = static_cast<int>(tempEntity->GetValue());

	tempEntity = coreSystem->GetConfigValue(std::hash<std::wstring>{}(L"NativeResolutionHeight"));
	if (nullptr != tempEntity)
		_screenHeight = static_cast<int>(tempEntity->GetValue());

	tempEntity = coreSystem->GetConfigValue(std::hash<std::wstring>{}(L"ScreenNear"));
	if (nullptr != tempEntity)
		_screenNear = tempEntity->GetValue();

	tempEntity = coreSystem->GetConfigValue(std::hash<std::wstring>{}(L"ScreenFar"));
	if (nullptr != tempEntity)
		_screenFar = tempEntity->GetValue();


	tempEntity = coreSystem->GetConfigValue(std::hash<std::wstring>{}(L"FOV"));
	float fov = 360.0f;
	if (nullptr != tempEntity)
		fov = tempEntity->GetValue();

	_fieldOfView = 3.141592654f * static_cast<float>(fov / 360.0f);

	_screenAspect = static_cast<float>(_screenWidth) / static_cast<float>(_screenHeight);
	_projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(_fieldOfView, _screenAspect, _screenNear, _screenFar);


	if (false == LoadDevice_(hwnd))//(1024, 1024);
		return false;
	
	return true;
}


bool DXDevice11_4::Reset()
{
	return true;
}

bool DXDevice11_4::LoadDevice_(HWND hwnd)//(int screenWidth, int screenHeight)
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

	result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr);
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

	memset(&swapChainDesc, 0, sizeof(swapChainDesc));

	
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = _screenWidth;
	swapChainDesc.BufferDesc.Height = _screenHeight;

	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	//vsync
	swapChainDesc.BufferDesc.RefreshRate.Numerator = numerator;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = denominator;

	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	//SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.Windowed = true;

	swapChainDesc.OutputWindow = hwnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;

	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	swapChainDesc.Flags = 0;
	featureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_1;
	ID3D11Device* device11 = nullptr;
	ID3D11DeviceContext* deviceContext11 = nullptr;
	result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, &_swapChain, &device11, nullptr, &deviceContext11);
	if (FAILED(result))
		return false;
	
	_device = static_cast<ID3D11Device3*>(device11);
	_deviceContext = static_cast<ID3D11DeviceContext3*>(deviceContext11);
	result = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&backBufferPtr));
	if (FAILED(result))
		return false;

	result = _device->CreateRenderTargetView(backBufferPtr, nullptr, &_backBufferRTV);
	if (FAILED(result))
		return false;

	backBufferPtr->Release();
	backBufferPtr = nullptr;

	memset(&depthBufferDesc, 0, sizeof(depthBufferDesc));

	depthBufferDesc.Width = _screenWidth;
	depthBufferDesc.Height = _screenHeight;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = 1;
	depthBufferDesc.SampleDesc.Quality = 0;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;

	result = _device->CreateTexture2D(&depthBufferDesc, nullptr, &_depthStencilBuffer);
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

	viewport.Width = static_cast<float>(_screenWidth);
	viewport.Height = static_cast<float>(_screenHeight);
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;

	_deviceContext->RSSetViewports(1, &viewport);


	D3D11_TEXTURE2D_DESC normalRTTexDesc;
	normalRTTexDesc.Width = _screenWidth;
	normalRTTexDesc.Height = _screenHeight;
	normalRTTexDesc.MipLevels = 1;
	normalRTTexDesc.ArraySize = 1;
	normalRTTexDesc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
	normalRTTexDesc.SampleDesc.Count = 1;
	normalRTTexDesc.SampleDesc.Quality = 0;
	normalRTTexDesc.Usage = D3D11_USAGE_DEFAULT;
	normalRTTexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	normalRTTexDesc.CPUAccessFlags = 0;
	normalRTTexDesc.MiscFlags = 0;

	result = _device->CreateTexture2D(&normalRTTexDesc, nullptr, &_renderTargetTex[static_cast<UINT>(RenderEngine::INDEXEDDEFERREDSHADINGRT::NORMAL)]);
	if (FAILED(result))
		return false;

	result = _device->CreateRenderTargetView(	_renderTargetTex[static_cast<UINT>(RenderEngine::INDEXEDDEFERREDSHADINGRT::NORMAL)],
												nullptr, 
												&_renderTargetViewMap[static_cast<UINT>(RenderEngine::INDEXEDDEFERREDSHADINGRT::NORMAL)]);
	if (FAILED(result))
		return false;

	result = _device->CreateShaderResourceView(	_renderTargetTex[static_cast<UINT>(RenderEngine::INDEXEDDEFERREDSHADINGRT::NORMAL)],
													nullptr,
													&_shaderResourceView[static_cast<UINT>(RenderEngine::INDEXEDDEFERREDSHADINGRT::NORMAL)]);
	if (FAILED(result))
		return false;

	D3D11_TEXTURE2D_DESC AlbedoRTTexDesc;
	AlbedoRTTexDesc.Width = _screenWidth;
	AlbedoRTTexDesc.Height = _screenHeight;
	AlbedoRTTexDesc.MipLevels = 1;
	AlbedoRTTexDesc.ArraySize = 1;
	AlbedoRTTexDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	AlbedoRTTexDesc.SampleDesc.Count = 1;
	AlbedoRTTexDesc.SampleDesc.Quality = 0;
	AlbedoRTTexDesc.Usage = D3D11_USAGE_DEFAULT;
	AlbedoRTTexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	AlbedoRTTexDesc.CPUAccessFlags = 0;
	AlbedoRTTexDesc.MiscFlags = 0;

	result = _device->CreateTexture2D(&AlbedoRTTexDesc, nullptr, &_renderTargetTex[static_cast<UINT>(RenderEngine::INDEXEDDEFERREDSHADINGRT::ALBEDO)]);
	if (FAILED(result))
		return false;

	result = _device->CreateRenderTargetView(_renderTargetTex[static_cast<UINT>(RenderEngine::INDEXEDDEFERREDSHADINGRT::ALBEDO)],
		nullptr,
		&_renderTargetViewMap[static_cast<UINT>(RenderEngine::INDEXEDDEFERREDSHADINGRT::ALBEDO)]);
	if (FAILED(result))
		return false;

	result = _device->CreateShaderResourceView(_renderTargetTex[static_cast<UINT>(RenderEngine::INDEXEDDEFERREDSHADINGRT::ALBEDO)],
		nullptr,
		&_shaderResourceView[static_cast<UINT>(RenderEngine::INDEXEDDEFERREDSHADINGRT::ALBEDO)]);
	if (FAILED(result))
		return false;

	D3D11_TEXTURE2D_DESC DepthRTTexDesc;
	DepthRTTexDesc.Width = _screenWidth;
	DepthRTTexDesc.Height = _screenHeight;
	DepthRTTexDesc.MipLevels = 1;
	DepthRTTexDesc.ArraySize = 1;
	DepthRTTexDesc.Format = DXGI_FORMAT_R16G16_FLOAT;
	DepthRTTexDesc.SampleDesc.Count = 1;
	DepthRTTexDesc.SampleDesc.Quality = 0;
	DepthRTTexDesc.Usage = D3D11_USAGE_DEFAULT;
	DepthRTTexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	DepthRTTexDesc.CPUAccessFlags = 0;
	DepthRTTexDesc.MiscFlags = 0;

	result = _device->CreateTexture2D(&DepthRTTexDesc, nullptr, &_renderTargetTex[static_cast<UINT>(RenderEngine::INDEXEDDEFERREDSHADINGRT::POSITION)]);
	if (FAILED(result))
		return false;

	result = _device->CreateRenderTargetView(_renderTargetTex[static_cast<UINT>(RenderEngine::INDEXEDDEFERREDSHADINGRT::POSITION)],
		nullptr,
		&_renderTargetViewMap[static_cast<UINT>(RenderEngine::INDEXEDDEFERREDSHADINGRT::POSITION)]);
	if (FAILED(result))
		return false;

	result = _device->CreateShaderResourceView(_renderTargetTex[static_cast<UINT>(RenderEngine::INDEXEDDEFERREDSHADINGRT::POSITION)],
		nullptr,
		&_shaderResourceView[static_cast<UINT>(RenderEngine::INDEXEDDEFERREDSHADINGRT::POSITION)]);
	if (FAILED(result))
		return false;

	D3D11_TEXTURE2D_DESC SpecularRTTexDesc;
	SpecularRTTexDesc.Width = _screenWidth;
	SpecularRTTexDesc.Height = _screenHeight;
	SpecularRTTexDesc.MipLevels = 1;
	SpecularRTTexDesc.ArraySize = 1;
	SpecularRTTexDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SpecularRTTexDesc.SampleDesc.Count = 1;
	SpecularRTTexDesc.SampleDesc.Quality = 0;
	SpecularRTTexDesc.Usage = D3D11_USAGE_DEFAULT;
	SpecularRTTexDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	SpecularRTTexDesc.CPUAccessFlags = 0;
	SpecularRTTexDesc.MiscFlags = 0;

	result = _device->CreateTexture2D(&SpecularRTTexDesc, nullptr, &_renderTargetTex[static_cast<UINT>(RenderEngine::INDEXEDDEFERREDSHADINGRT::SPECULAR)]);
	if (FAILED(result))
		return false;

	result = _device->CreateRenderTargetView(_renderTargetTex[static_cast<UINT>(RenderEngine::INDEXEDDEFERREDSHADINGRT::SPECULAR)],
		nullptr,
		&_renderTargetViewMap[static_cast<UINT>(RenderEngine::INDEXEDDEFERREDSHADINGRT::SPECULAR)]);
	if (FAILED(result))
		return false;

	result = _device->CreateShaderResourceView(_renderTargetTex[static_cast<UINT>(RenderEngine::INDEXEDDEFERREDSHADINGRT::SPECULAR)],
		nullptr,
		&_shaderResourceView[static_cast<UINT>(RenderEngine::INDEXEDDEFERREDSHADINGRT::SPECULAR)]);
	if (FAILED(result))
		return false;
	
	delete[] displayModeList;
	displayModeList = nullptr;

	adapterOutput->Release();
	adapterOutput = nullptr;

	adapter->Release();
	adapter = nullptr;

	factory->Release();
	factory = nullptr;

	return true;
}

void DXDevice11_4::DrawPrimitive()
{
}
/*
void DXDevice11_4::RenderMesh(const ORBITMesh* meshData) const
{



}
*/