#pragma once
#include "IModelObject.h"
#include "IShaderObejct.h"
#include "IRenderingMethod.h"
#include "IGraphicsDevice.h"
namespace RenderEngine
{
	enum class DeferredShadingRenderTarget
	{
		ALBEDO,
		NORMAL,
		SPACULAR,
		DEPTH,
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