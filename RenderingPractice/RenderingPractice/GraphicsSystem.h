#pragma once
#include "RenderEngineCommon.h"
#include "IUpdateableObject.h"
#include "IRenderableManager.h"
#include "IGraphicsSystemFacade.h"
#include <unordered_map>
class RenderingManager;
class DeviceManager;
class ModelManager;
class ShaderManager;
class RenderEngineFactoryBase;
class RenderMethod;
class IRenderableObject;

class  GraphicsSystem : public IUpdateableObject, public IRenderableManager, public IGraphicsSystemFacade
{
public:

	struct GraphicsSystemInitialData
	{
	public:
		RenderEngine::GRAPHICSAPITYPE	graphicsAPIType;
		RenderEngineFactoryBase*		renderEngineFactory;
	};
	GraphicsSystem(GraphicsSystemInitialData& data);
	GraphicsSystem() = delete;
	GraphicsSystem(const GraphicsSystem&) = delete;
	virtual ~GraphicsSystem();

	bool Initialize(HWND hwnd);
	bool Reset();
	virtual void PreUpdate	(float deltaTime);
	virtual void Update		(float deltaTime);
	virtual void PostUpdate	(float deltaTime);
	virtual void Render(float deltaTime);
	virtual void PhaseReady(float deltaTime);
	virtual void PhaseEnd(float deltaTime);

	bool InitializeSingleton_();

	RenderEngine::GRAPHICSAPITYPE GetGraphicsAPIType()			{ return _graphicsAPIType; }
	RenderingManager*		GetRenderingManager()				{ return _renderingMananger; }
	DeviceManager*			GetDeviceManager()					{ return _deviceManager; }
	ModelManager*			GetModelManager()					{ return _modelManager; }
	ShaderManager*			GetShaderManager()					{ return _shaderManager; }
	RenderEngineFactoryBase*	GetRenderEngineFactory()		{ return _renderEngineFactory; }

	//From class IGraphicsSystemFacade
	virtual bool AddRenderingRequest(IRenderableObject* renderObject);
	virtual ModelStaticData* GetStaticModel(size_t modelHashCode);

private:
	
	RenderEngine::GRAPHICSAPITYPE _graphicsAPIType;

	RenderingManager*		_renderingMananger;
	DeviceManager*			_deviceManager;
	ModelManager*			_modelManager;
	ShaderManager*			_shaderManager;
	RenderEngineFactoryBase* _renderEngineFactory;
};