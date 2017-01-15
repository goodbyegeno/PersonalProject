#pragma once
class SystemConfig;
namespace RenderEngine
{
	class GraphicsDevice;
	class DeviceManager
	{
	public:
		DeviceManager();
		virtual ~DeviceManager();

		bool Initialize(HWND hwnd, GRAPHICSAPITYPE apiType, SystemConfig* systemConfig);
		bool PostInitialize();

		bool Reset();
		bool PostReset();
		void PreUpdate(float deltaTime);
		void PostUpdate(float deltaTime);
		void Update(float deltaTime);

		GraphicsDevice* GetDevice() { return _device; }
	private:

		GraphicsDevice* _device;
		//GraphicsSystem* _graphicSystem;
	};
}