#pragma once
#include "CoreEngineCommon.h"
class ORBITMesh;

class IGraphicsDevice
{
public:
	IGraphicsDevice() {}
	virtual ~IGraphicsDevice() = 0;

	virtual void* GetShader() = 0;
	virtual void* GetBuffer() = 0;
	virtual CoreEngine::GRAPHICSAPITYPE GetGraphicsAPIType() = 0;

	virtual void RenderMesh(ORBITMesh* meshData) = 0;
};