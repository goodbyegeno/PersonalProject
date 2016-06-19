#pragma once
#include "RenderEngineCommon.h"
class ShaderManager;
class DeviceManager;
class RenderingManager;
#include <d3d11.h>

class DeferredShadingMethod : public IRenderMethod
{
public:
	DeferredShadingMethod(RenderingManager* pRenderingMnanger);
	virtual ~DeferredShadingMethod();

	virtual bool	Initialize();
	virtual bool	Reset();

	virtual void	Render(DeviceManager* pDeviceManager, ShaderManager* pShaderManager, std::vector<IRenderedObject>* lstRederRequestObject, float fDeltaTime);

	RenderEngine::RenderingMode GetRenderingMode() final { return RenderEngine::RenderingMode::Indexed_Deferred; }

private:
	void RenderGBuffer_();

private:

	RenderingManager*	m_pRenderingMananger;
	bool				m_bVsync;
	float				m_fMSecPerFrame;
	float				m_fCurrentMSecPerFrame;
	int					m_nFPS;

	ID3D11Texture2D*				m_lstRenderTargetTex[static_cast<UINT>(RenderEngine::RenderTargetIndex::MAX)];
	ID3D11ShaderResourceView*		m_lstSRV[static_cast<UINT>(RenderEngine::RenderTargetIndex::MAX)];
	ID3D11RenderTargetView*			m_lstRTV[static_cast<UINT>(RenderEngine::RenderTargetIndex::MAX)];

	/*
	ID3D11Texture2D*			m_pNormalRTBuffer;
	ID3D11ShaderResourceView*	m_pNormalSRV;
	ID3D11RenderTargetView*		m_pNormalRTV;

	ID3D11Texture2D*	m_pDepthRTBuffer;
	ID3D11ShaderResourceView*	m_pDepthSRV;
	ID3D11RenderTargetView*		m_pDepthRTV;
	ID3D11Texture2D*	m_pSpecularRTBuffer;
	ID3D11ShaderResourceView*	m_pSpecularSRV;
	ID3D11RenderTargetView*		m_pSpecularRTV;
	ID3D11Texture2D*	m_pAlbedoRTBuffer;
	ID3D11ShaderResourceView*	m_pAlbedoSRV;
	ID3D11RenderTargetView*		m_pAlbedoRTV;
	*/
};