#pragma once
#include <d3d11_4.h>
#include "RenderEngineCommon.h"
#include "RenderingMethod.h"

class ShaderManager;
class DeviceManager;
class RenderingManager;
class IDeferredShadingMethodImpl;
class GraphicsDevice;

class DeferredShadingMethod : public RenderMethod
{

public:
	DeferredShadingMethod(RenderingManager* renderingMnanger);
	virtual ~DeferredShadingMethod();

	virtual bool	Initialize();
	virtual bool	Reset();

	virtual void	Render(DeviceManager* deviceManager, ShaderManager* shaderManager, std::vector<IRenderableObject*>& renderRequestObjects, float deltaTime);
	virtual RenderEngine::RENDERINGMODE GetRenderingMode() final { return RenderEngine::RENDERINGMODE::INDEXED_DEFERRED_SHADING; }

private:
	void	RenderGBuffer_(DeviceManager* deviceManager, ShaderManager* shaderManager, std::vector<IRenderableObject*>& renderRequestObjects, float deltaTime);

	void	RenderLighting_(DeviceManager* deviceManager, ShaderManager* shaderManager, std::vector<IRenderableObject*>& renderRequestObjects, float deltaTime);
	bool	CreateRenderingMethodImpl_();

private:

	IDeferredShadingMethodImpl* _renderingMethodImpl;
	RenderingManager*			_renderingMananger;
	bool						_VSync;
	float						_mSecPerFrame;
	float						_currentMSecPerFrame;
	int							_FPS;
	GraphicsDevice *			_graphicsDevice;
	

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