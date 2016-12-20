#pragma once
#include <d3d11_4.h>
#include "RenderEngineCommon.h"
#include "RenderingMethod.h"

class ShaderManager;
class DeviceManager;
class RenderingManager;
class IForwardShadingMethodImpl;
class GraphicsDevice;
class GraphicsSystem;

class ForwardShadingMethod : public RenderMethod
{
public:
	ForwardShadingMethod(GraphicsSystem* graphicsSystem);
	virtual ~ForwardShadingMethod();

	virtual bool Initialize();
	virtual bool Reset();
	virtual void Render(DeviceManager* deviceManager, ShaderManager* shaderManager, std::vector<IRenderableObject*>& renderRequestObjects, float deltaTime);
	virtual bool CreateVertexBuffer(int vertexCount, int indexCount, ORBITVertex* verticesOrigin, UINT* indicesOrigin, ORBITMesh* outMeshData);

private:
	bool	CreateRenderingMethodImpl_();

private:
	GraphicsSystem*				_graphicsSystem;
	IForwardShadingMethodImpl*	_renderingMethodImpl;
	RenderingManager*			_renderingMananger;
	bool						_VSync;
	float						_mSecPerFrame;
	float						_currentMSecPerFrame;
	int							_FPS;
	GraphicsDevice *			_graphicsDevice;


};