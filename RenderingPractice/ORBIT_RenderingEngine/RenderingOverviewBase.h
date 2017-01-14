#pragma once
class RenderingManager;
class DeviceManager;
class ShaderManager;
class RenderMethod;
class IRenderableObject;
class RenderingOverviewBase
{
public:
	RenderingOverviewBase(RenderingManager* renderingManager);
	RenderingOverviewBase() = delete;
	virtual ~RenderingOverviewBase();

	virtual bool Initialize();
	virtual bool Reset();

	virtual void Render(DeviceManager* deviceManager, ShaderManager* shaderManager, std::unordered_map<size_t, std::vector<IRenderableObject*>>* renderingRequestMap, std::unordered_map<size_t, RenderMethod*>* renderingMethodMap);

protected:
	RenderingManager* GetRenderingManager_() { return _renderingManager; }
	std::unordered_map<size_t, RenderMethod*>* GetRenderingMethodMap_() { return _renderingMethodMap; }
private:
	RenderingManager* _renderingManager;
	std::unordered_map<size_t, RenderMethod*>*	_renderingMethodMap;		//from RenderingManager

};