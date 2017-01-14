#pragma once
#include "RenderEngineCommon.h"
class ORBITMesh;
namespace RenderEngine
{
	class GraphicsDevice
	{
	public:
		GraphicsDevice(RenderEngine::GRAPHICSAPITYPE graphcisAPIType);
		GraphicsDevice(const GraphicsDevice&) = delete;
		virtual ~GraphicsDevice() {};

		virtual bool	Initialize(HWND hwnd) = 0;
		virtual bool	Reset()			= 0;

		virtual void*	GetShader()		= 0;
		virtual void*	GetBuffer()		= 0;
		virtual void	BegineScene()	= 0;
		virtual void	EndScene()		= 0;

		virtual bool	UpdateRenderResolution()		= 0;
		virtual bool	UpdateBackBufferResolution()	= 0;

		float	GetFoV()					{ return _fieldOfView; }
		float	GetFrustumNearDefault()		{ return _frustumNear; }
		float	GetFrustumFarDefault()		{ return _frustumFar; }
		float	GetScreenAspect()			{ return _viewScreenAspect; }

		RenderEngine::GRAPHICSAPITYPE GetGraphicsAPIType() { return _graphcisAPIType; }

		//virtual void RenderMesh(ORBITMesh* meshData) = 0;

	private:
		RenderEngine::GRAPHICSAPITYPE _graphcisAPIType;

	protected:
		int							_renderingResoWidth;
		int							_renderingResoHeight;

		int							_screenResoWidth;
		int							_screenResoHeight;

		float						_fieldOfView;
		float						_viewScreenAspect;
		float						_frustumNear;
		float						_frustumFar;
	};
};