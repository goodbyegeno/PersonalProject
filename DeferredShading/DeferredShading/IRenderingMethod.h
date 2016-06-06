#pragma once
class ShaderManager;
class DeviceManager;
class RenderingManager;

class IRenderMethod
{
public:

	IRenderMethod() {};
	virtual ~IRenderMethod() = 0;

	virtual bool Initialize() = 0;
	virtual bool Reset() = 0;
	virtual void Render(DeviceManager* pDeviceManager, ShaderManager* pShaderManager, float fDeltaTime);

};