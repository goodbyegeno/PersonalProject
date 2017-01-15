#include "stdafx.h"
#include "GraphicsDevice.h"
namespace RenderEngine
{
	GraphicsDevice::GraphicsDevice(RenderEngine::GRAPHICSAPITYPE graphcisAPIType) :
		_graphcisAPIType(graphcisAPIType),
		_renderingResoWidth(0),
		_renderingResoHeight(0),
		_screenResoWidth(0),
		_screenResoHeight(0),
		_fieldOfView(0.0f),
		_viewScreenAspect(0.0f),
		_frustumNear(0.0f),
		_frustumFar(0.0f)
	{
	}
}
