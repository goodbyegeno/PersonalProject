#pragma once
class IGraphcisDevice;
class GraphicsSystem;
class DeviceManager
{
public:
	DeviceManager(GraphicsSystem* pGraphicSystem);
	virtual ~DeviceManager();

	bool Initialize();
	bool Reset();
	void PreUpdate(float fDeltaTime);
	void PostUpdate(float fDeltaTime);
	void Update(float fDeltaTime);

	IGraphcisDevice* GetDevice() { return m_Device; }
private:

	IGraphcisDevice* m_Device;
	GraphicsSystem* m_pGraphicSystem;
};