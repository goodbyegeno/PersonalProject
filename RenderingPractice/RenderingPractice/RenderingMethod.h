#pragma once
#include "RenderEngineCommon.h"

class ShaderManager;
class DeviceManager;
class RenderingManager;
class IRenderableObject;
class ORBITVertex;
class ORBITMesh;

class RenderMethod
{
public:
	RenderMethod(size_t methodHash) : _methodHash(methodHash) {}
	RenderMethod() = delete;

	virtual ~RenderMethod() {};
	virtual size_t GetHashcode() { return _methodHash; }

	virtual bool Initialize() = 0;
	virtual bool Reset() = 0;
	virtual void Render(DeviceManager* deviceManager, ShaderManager* shaderManager, std::vector<IRenderableObject*>& renderRequestObjects, float deltaTime) = 0;
	virtual bool CreateVertexBuffer(int vertexCount, int indexCount, ORBITVertex* verticesOrigin, UINT* indicesOrigin, ORBITMesh* outMeshData) = 0;
	//virtual RenderEngine::RENDERINGMODE GetRenderingMode() { return RenderEngine::RENDERINGMODE::FORWARD; }
private:
	size_t _methodHash;

};