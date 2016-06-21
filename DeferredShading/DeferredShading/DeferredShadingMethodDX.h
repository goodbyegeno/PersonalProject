#pragma once

#include "IDeferredShadingMethodImpl.h"
#include <d3d11.h>
class DeviceManager;
class ShaderManager;

class DeferredShadingMethodDX : public IDeferredShadingMethodImpl
{
public:
	DeferredShadingMethodDX();
	virtual ~DeferredShadingMethodDX();

	bool Initialize(DeviceManager* pDeviceManager, ShaderManager* pShaderManager);
	bool Reset(DeviceManager* pDeviceManager, ShaderManager* pShaderManager);
	void SetConstVariables();
	void SetRenderTarget();

private:
	bool SetShader_(ShaderManager* pShaderManager, ID3D11Device* pDeviceDX);
private:

	ID3D11Texture2D*				m_lstRenderTargetTex[4];
	ID3D11ShaderResourceView*		m_lstSRV[4];
	ID3D11RenderTargetView*			m_lstRTV[4];
	ID3D11InputLayout*				m_pInputLayout;

	ID3D11VertexShader*				m_pVertexShader;
	ID3D11PixelShader*				m_pPixelShader;
	ID3D11ComputeShader*			m_pComputeShader;

	size_t							m_nVertexShaderHash;
	size_t							m_nPixelShaderHash;
	size_t							m_nComputeShaderHash;
};