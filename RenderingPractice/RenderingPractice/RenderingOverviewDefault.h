#pragma once
#include "RenderingOverviewBase.h"


class RenderMethod;
class IRenderableObject;

class RenderingOverviewDefault : public RenderingOverviewBase
{
public:
	RenderingOverviewDefault(RenderingManager* renderingManager);
	RenderingOverviewDefault() = delete;

	virtual ~RenderingOverviewDefault();

	virtual bool Initialize();
	virtual bool Reset();
	virtual void Render(DeviceManager* deviceManager, ShaderManager* shaderManager, std::unordered_map<size_t, std::vector<IRenderableObject*>>* renderingRequestMap, std::unordered_map<size_t, RenderMethod*>* renderingMethodMap);

private:

	size_t _forwardHashCode;
	size_t _deferredHashCode;

};