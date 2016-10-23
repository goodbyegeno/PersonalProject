#pragma once
#include "RenderEngineCommon.h"
class ORBITMesh;

class GraphicsDevice
{
public:
	GraphicsDevice(RenderEngine::GRAPHICSAPITYPE graphcisAPIType) : _graphcisAPIType(graphcisAPIType){};
	virtual ~GraphicsDevice() {};

	virtual bool	Initialize(HWND hwnd) = 0;
	virtual bool	Reset() = 0;
	
	virtual void*	GetShader() = 0;
	virtual void*	GetBuffer() = 0;
	virtual bool	UpdateRenderResolution() = 0;
	virtual bool	UpdateBackBufferResolution() = 0;
	RenderEngine::GRAPHICSAPITYPE GetGraphicsAPIType() { return _graphcisAPIType; }

	//virtual void RenderMesh(ORBITMesh* meshData) = 0;

private:
	RenderEngine::GRAPHICSAPITYPE _graphcisAPIType;

};