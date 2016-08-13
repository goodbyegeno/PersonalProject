#pragma once
#include <d3d11_2.h>
#include "RenderEngineCommon.h"
#include "IRenderingMethod.h"

class ShaderManager;
class DeviceManager;
class RenderingManager;
class IDeferredShadingMethodImpl;

class DeferredShadingMethod : public IRenderMethod
{

public:
	DeferredShadingMethod(RenderingManager* renderingMnanger);
	virtual ~DeferredShadingMethod();

	virtual bool	Initialize();
	virtual bool	Reset();

	virtual void	Render(DeviceManager* deviceManager, ShaderManager* shaderManager, std::vector<IRenderedObject*>& renderRequestObjects, float deltaTime);
	RenderEngine::RENDERINGMODE GetRenderingMode() final { return RenderEngine::RENDERINGMODE::INDEXED_DEFERRED_SHADING; }

private:
	void	RenderGBuffer_(DeviceManager* deviceManager, ShaderManager* shaderManager, std::vector<IRenderedObject*>& renderRequestObjects, float deltaTime);
	void	RenderLighting_(DeviceManager* deviceManager, ShaderManager* shaderManager, std::vector<IRenderedObject*>& renderRequestObjects, float deltaTime);

private:

	IDeferredShadingMethodImpl* _renderingMethodImpl;
	RenderingManager*			_renderingMananger;
	bool						_VSync;
	float						_mSecPerFrame;
	float						_currentMSecPerFrame;
	int							_FPS;

	

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