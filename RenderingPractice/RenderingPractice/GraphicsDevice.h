#pragma once
#include "RenderEngineCommon.h"
class ORBITMesh;

class GraphicsDevice
{
public:
	GraphicsDevice() {};
	virtual ~GraphicsDevice() {};

	virtual bool Initialize() = 0;
	virtual bool Reset() = 0;
	
	virtual void* GetShader() = 0;
	virtual void* GetBuffer() = 0;
	
	RenderEngine::GRAPHICSAPITYPE GetGraphicsAPIType() { return _graphcisAPIType; }

	//virtual void RenderMesh(ORBITMesh* meshData) = 0;

private:
	RenderEngine::GRAPHICSAPITYPE _graphcisAPIType;

};