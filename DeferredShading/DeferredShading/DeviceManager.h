#pragma once
class IGraphicsDevice;
class GraphicsSystem;
class DeviceManager
{
public:
	DeviceManager(GraphicsSystem* graphicSystem);
	virtual ~DeviceManager();

	bool Initialize();
	bool PostInitialize();

	bool Reset();
	bool PostReset();
	void PreUpdate(float deltaTime);
	void PostUpdate(float deltaTime);
	void Update(float deltaTime);

	IGraphicsDevice* GetDevice() { return _device; }
private:

	IGraphicsDevice* _device;
	GraphicsSystem* _graphicSystem;
};