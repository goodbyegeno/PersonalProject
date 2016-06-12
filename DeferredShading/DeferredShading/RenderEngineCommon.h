#pragma once
#include "IModelObject.h"
#include "IShaderObejct.h"
#include "IRenderingMethod.h"
#include "IGraphicsDevice.h"
class CameraBase;

namespace RenderEngine
{
	enum class DeferredShadingRenderTarget
	{
		ALBEDO,
		NORMAL,
		SPECULAR,
		MOTIONVECTOR,
		MAX
	};

	enum class RenderingMode
	{
		Deferred,
		indexed_Deferred,
		Forward,
		MAX
	};
};
namespace CommonVariable
{
	CameraBase* g_pCameraObject;

};
