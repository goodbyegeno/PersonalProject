#pragma once
class IGraphcisDevice;

class DeviceManager
{
public:
	DeviceManager();
	virtual ~DeviceManager();

	bool Initialize();
	bool Reset();

	IGraphcisDevice* GetDevice() { return m_Device; }
private:

	IGraphcisDevice* m_Device;
};