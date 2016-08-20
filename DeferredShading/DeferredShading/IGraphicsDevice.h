#pragma once
class IGraphcisDevice
{
public:
	IGraphcisDevice() {}
	virtual ~IGraphcisDevice() = 0;

	virtual void* GetShader() = 0;
	virtual void* GetBuffer() = 0;
	virtual RenderEngine::MiddlewareType GetMiddlewareType() = 0;

	virtual void RenderMesh(ORBITMesh* meshData) = 0;
};