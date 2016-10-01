#pragma once
class GraphicsDevice;
class GraphicsSystem;
class DeviceManager
{
public:
	DeviceManager(GraphicsSystem* graphicSystem);
	virtual ~DeviceManager();

	bool Initialize(HWND hwnd);
	bool PostInitialize();

	bool Reset();
	bool PostReset();
	void PreUpdate(float deltaTime);
	void PostUpdate(float deltaTime);
	void Update(float deltaTime);

	GraphicsDevice* GetDevice() { return _device; }
private:

	GraphicsDevice* _device;
	GraphicsSystem* _graphicSystem;
};