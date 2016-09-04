#pragma once
class IGraphcisDevice;
class GraphicsSystem;
class DeviceManager
{
public:
	DeviceManager(GraphicsSystem* pGraphicSystem);
	virtual ~DeviceManager();

	bool Initialize();
	bool PostInitialize();

	bool Reset();
	bool PostReset();
	void PreUpdate(float fDeltaTime);
	void PostUpdate(float fDeltaTime);
	void Update(float fDeltaTime);

	IGraphcisDevice* GetDevice() { return m_Device; }
private:

	IGraphcisDevice* _device;
	GraphicsSystem* _graphicSystem;
};