#pragma once

class CoreSystem;
class GraphicsSystem;
class RenderEngineFactoryManager;
class SceneManager;

class SurfaceMain
{
public:
	SurfaceMain();
	virtual ~SurfaceMain();
	bool Initialize();
	bool Reset();
	void Update();

	void TestInitialize_();
private:
	CoreSystem* _coreSystem;
	GraphicsSystem* _graphicsSystem;
	SceneManager* _sceneManager;

};