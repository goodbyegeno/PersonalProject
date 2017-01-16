#include "stdafx.h"
#include "DXDevice11_4.h"
//#include "CameraBase.h"
//#include "ORBITMesh.h"
//#include "CoreSystem.h"
#include "Orbit_Base\SystemConfig.h"
#include "Orbit_Base\SystemConfigureFileImporter.h"
namespace RenderEngine
{
	DXDevice11_4::DXDevice11_4() :
		_device(nullptr),
		_deviceContext(nullptr),
		_swapChain(nullptr),
		_depthStencilBuffer(nullptr),
		_depthStencilState(nullptr),
		_depthStencilView(nullptr),
		_rasterState(nullptr),
		_videoCardMem(0),
		_backBufferRTV(nullptr),
		GraphicsDevice(RenderEngine::GRAPHICSAPITYPE::DIRECTX11_4)
	{
		/*
		for( int iRT = 0; iRT < static_cast<UINT>(RenderEngine::INDEXEDDEFERREDSHADINGRT::MAX); iRT++)
		{
			_renderTargetTex[iRT] = nullptr;
			_shaderResourceView[iRT] = nullptr;
			_renderTargetViewMap[iRT] = nullptr;
			//_renderTargetView[iRT] = nullptr;
		}
		*/

	}
	DXDevice11_4::~DXDevice11_4()
	{
		ReleaseDevice_();

		_adapterOutput->Release();
		_adapterOutput = nullptr;

		_adapter->Release();
		_adapter = nullptr;

	}
	bool DXDevice11_4::Initialize(HWND hwnd, const SystemConfig* systemConfig)
	{
		//_fieldOfView = 3.141592654f / 4.0f;
		const SystemConfigureEntity* tempEntity = systemConfig->GetConfigEntity(0, std::hash<std::wstring>{}(L"RenderResolutionWidth"));
		if (nullptr != tempEntity)
			_renderingResoWidth = static_cast<int>(tempEntity->GetValue());

		tempEntity = systemConfig->GetConfigEntity(0, std::hash<std::wstring>{}(L"RenderResolutionHeight"));
		if (nullptr != tempEntity)
			_renderingResoHeight = static_cast<int>(tempEntity->GetValue());

		tempEntity = systemConfig->GetConfigEntity(0, std::hash<std::wstring>{}(L"ScreenResolutionWidth"));
		if (nullptr != tempEntity)
			_screenResoWidth = static_cast<int>(tempEntity->GetValue());

		tempEntity = systemConfig->GetConfigEntity(0, std::hash<std::wstring>{}(L"ScreenResolutionHeight"));
		if (nullptr != tempEntity)
			_screenResoHeight = static_cast<int>(tempEntity->GetValue());

		tempEntity = systemConfig->GetConfigEntity(0, std::hash<std::wstring>{}(L"FrustumNearDefault"));
		if (nullptr != tempEntity)
			_frustumNear = tempEntity->GetValue();

		tempEntity = systemConfig->GetConfigEntity(0, std::hash<std::wstring>{}(L"FrustumFarDefault"));
		if (nullptr != tempEntity)
			_frustumFar = tempEntity->GetValue();

		tempEntity = systemConfig->GetConfigEntity(0, std::hash<std::wstring>{}(L"FOV"));
		float fov = 360.0f;
		if (nullptr != tempEntity)
			fov = tempEntity->GetValue();

		_fieldOfView = 3.141592654f * static_cast<float>(fov / 360.0f);

		_viewScreenAspect = static_cast<float>(_renderingResoWidth) / static_cast<float>(_renderingResoHeight);
		_projectionMatrix = DirectX::XMMatrixPerspectiveFovLH(_fieldOfView, _viewScreenAspect, _frustumNear, _frustumFar);

		_hwnd = hwnd;

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
		DXGI_ADAPTER_DESC adapterDesc;
		D3D_FEATURE_LEVEL featureLevel;
		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		D3D11_RASTERIZER_DESC rasterDesc;
		D3D11_VIEWPORT viewport;

		result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
		if (FAILED(result))
			return false;

		IDXGIAdapter* adapter;
		result = factory->EnumAdapters(0, &adapter);
		if (FAILED(result))
			return false;
		_adapter = adapter;

		IDXGIOutput* adapterOutput;
		result = adapter->EnumOutputs(0, &adapterOutput);
		if (FAILED(result))
			return false;
		_adapterOutput = adapterOutput;

		UINT numModes = 0;
		bool isHDRMonitor = true;
		int numerator, denominator;

		result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr);
		if (FAILED(result))
			return false;

		DXGI_MODE_DESC* displayModeList;
		// Create a list to hold all the possible display modes for this monitor/video card combination.
		displayModeList = new DXGI_MODE_DESC[numModes];
		if (!displayModeList)
			return false;

		result = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
		if (FAILED(result))
			return false;

		numerator = displayModeList[0].RefreshRate.Numerator;
		denominator = displayModeList[0].RefreshRate.Denominator;

		result = adapter->GetDesc(&adapterDesc);
		if (FAILED(result))
			return false;

		_videoCardMem = static_cast<ULONG>(adapterDesc.DedicatedVideoMemory);

		DXGI_SWAP_CHAIN_DESC swapChainDesc;

		memset(&swapChainDesc, 0, sizeof(swapChainDesc));

		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = _screenResoWidth;
		swapChainDesc.BufferDesc.Height = _screenResoHeight;
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
		featureLevel = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;

		ID3D11Device* device11 = nullptr;
		ID3D11DeviceContext* deviceContext11 = nullptr;
		result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &featureLevel, 1, D3D11_SDK_VERSION, &swapChainDesc, &_swapChain, &device11, nullptr, &deviceContext11);
		if (FAILED(result))
			return false;

		_device = static_cast<ID3D11Device3*>(device11);
		_deviceContext = static_cast<ID3D11DeviceContext3*>(deviceContext11);
		ID3D11Texture2D* backBufferPtr;
		result = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<LPVOID*>(&backBufferPtr));
		if (FAILED(result))
			return false;

		result = _device->CreateRenderTargetView(backBufferPtr, nullptr, &_backBufferRTV);
		if (FAILED(result))
			return false;

		backBufferPtr->Release();
		backBufferPtr = nullptr;

		D3D11_TEXTURE2D_DESC depthBufferDesc;
		memset(&depthBufferDesc, 0, sizeof(depthBufferDesc));

		depthBufferDesc.Width = _renderingResoWidth;
		depthBufferDesc.Height = _renderingResoHeight;
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

		D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
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

		viewport.Width = static_cast<float>(_renderingResoWidth);
		viewport.Height = static_cast<float>(_renderingResoHeight);
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		_deviceContext->RSSetViewports(1, &viewport);

		D3D11_BLEND_DESC1 blendDesc;
		D3D11_RENDER_TARGET_BLEND_DESC1 renderTargetBlendDesc;
		/*renderTargetBlendDesc.BlendEnable = false;
		renderTargetBlendDesc.SrcBlend = D3D11_BLEND::D3D11_BLEND_ONE;
		renderTargetBlendDesc.SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		renderTargetBlendDesc.DestBlend = D3D11_BLEND::D3D11_BLEND_ZERO;
		renderTargetBlendDesc.DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ZERO;
		renderTargetBlendDesc.BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		renderTargetBlendDesc.BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		renderTargetBlendDesc.LogicOp = D3D11_LOGIC_OP::D3D11_LOGIC_OP_CLEAR;
		renderTargetBlendDesc.LogicOpEnable = false;
		renderTargetBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		*/
		renderTargetBlendDesc.BlendEnable = true;
		renderTargetBlendDesc.SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_COLOR;
		renderTargetBlendDesc.SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA;
		renderTargetBlendDesc.DestBlend = D3D11_BLEND::D3D11_BLEND_DEST_COLOR;
		renderTargetBlendDesc.DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_DEST_ALPHA;
		renderTargetBlendDesc.BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		renderTargetBlendDesc.BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		renderTargetBlendDesc.LogicOp = D3D11_LOGIC_OP::D3D11_LOGIC_OP_CLEAR;
		renderTargetBlendDesc.LogicOpEnable = false;
		renderTargetBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		blendDesc.AlphaToCoverageEnable = true;
		blendDesc.IndependentBlendEnable = true;
		for (int renderTargetIndex = 0; renderTargetIndex < 8; renderTargetIndex++)
		{
			blendDesc.RenderTarget[renderTargetIndex] = renderTargetBlendDesc;
		}
		result = _device->CreateBlendState1(&blendDesc, &_blendState);
		if (FAILED(result))
			return false;
		/*
		D3D11_TEXTURE2D_DESC normalRTTexDesc;
		normalRTTexDesc.Width = _renderingResoWidth;
		normalRTTexDesc.Height = _renderingResoHeight;
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
		*/
		delete[] displayModeList;
		displayModeList = nullptr;


		factory->Release();
		factory = nullptr;

		return true;
	}

	void DXDevice11_4::DrawPrimitive()
	{
	}
	bool DXDevice11_4::ReleaseDevice_()
	{
		_backBufferRTV->Release();
		_depthStencilBuffer->Release();
		_depthStencilState->Release();
		_depthStencilView->Release();
		_rasterState->Release();
		_blendState->Release();
		_swapChain->Release();
		_deviceContext->Release();
		_device->Release();

		_videoCardMem = 0;
		_renderingResoWidth = 0;
		_renderingResoHeight = 0;

		_screenResoWidth = 0;
		_screenResoHeight = 0;

		_fieldOfView = 0.0f;
		_viewScreenAspect = 0.0f;
		_frustumNear = 0.0f;
		_frustumFar = 0.0f;

		memset(&_projectionMatrix, 0, sizeof(DirectX::XMMATRIX));

		return true;
	}

	bool	DXDevice11_4::UpdateRenderResolution(const SystemConfig* systemConfig)
	{
		//resize depth/stencilBuffer with renderResolution;
		int renderingResoWidth = 0, renderingResoHeight = 0;

		const SystemConfigureEntity* tempEntity = systemConfig->GetConfigEntity(0, std::hash<std::wstring>{}(L"RenderResolutionWidth"));
		if (nullptr != tempEntity)
			renderingResoWidth = static_cast<int>(tempEntity->GetValue());

		tempEntity = systemConfig->GetConfigEntity(0, std::hash<std::wstring>{}(L"RenderResolutionHeight"));
		if (nullptr != tempEntity)
			renderingResoHeight = static_cast<int>(tempEntity->GetValue());

		DXGI_MODE_DESC* displayModeList;
		UINT numModes;
		HRESULT result;
		result = _adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, nullptr);
		if (FAILED(result))
			return false;

		displayModeList = new DXGI_MODE_DESC[numModes];
		if (!displayModeList)
			return false;

		result = _adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, displayModeList);
		if (FAILED(result))
			return false;
		displayModeList->Width = renderingResoWidth;
		displayModeList->Height = renderingResoHeight;
		_renderingResoWidth = renderingResoWidth;
		_renderingResoHeight = renderingResoHeight;

		_swapChain->ResizeTarget(displayModeList);

		//terminateBuffers
		//createNew
		return true;
	}
	bool	DXDevice11_4::UpdateBackBufferResolution(const SystemConfig* systemConfig)
	{
		//resize only Backbuffer
		int newScreenResoWidth, newScreenResoHeight;

		const SystemConfigureEntity* tempEntity = systemConfig->GetConfigEntity(0, std::hash<std::wstring>{}(L"ScreenResolutionWidth"));
		if (nullptr != tempEntity)
			newScreenResoWidth = static_cast<int>(tempEntity->GetValue());

		tempEntity = systemConfig->GetConfigEntity(0, std::hash<std::wstring>{}(L"ScreenResolutionHeight"));
		if (nullptr != tempEntity)
			newScreenResoHeight = static_cast<int>(tempEntity->GetValue());

		if (newScreenResoWidth != _screenResoWidth || newScreenResoHeight != _screenResoHeight)
		{
			_screenResoWidth = newScreenResoWidth;
			_screenResoHeight = newScreenResoHeight;

			//_backBufferRTV->Release();

			_swapChain->ResizeBuffers(1, _screenResoWidth, _screenResoHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
		}
		return true;
	}
	void	DXDevice11_4::BegineScene()
	{

	}

	void DXDevice11_4::EndScene()
	{
		//TODO VSYNC?
		//if()
		{
			_swapChain->Present(0, 0);
		}
	}
}