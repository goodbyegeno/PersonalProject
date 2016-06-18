#pragma once
#include "IRenderedObject.h"
#include "IShaderObejct.h"
#include "IRenderingMethod.h"
#include "IGraphicsDevice.h"
class CameraBase;

namespace RenderEngine
{
	enum class RenderTargetIndex
	{
		//deferred
		ALBEDO,
		NORMAL,
		SPECULAR,
		POSITION,
		MAX
	};

	enum class RenderingMode
	{
		Deferred_Lighting,
		Deferred_Shading,
		Indexed_Deferred,
		Forward,
		Forward_Plus,

		MAX
	};

	enum class RenderedType
	{
		Character,
		SkyBox,
		MAX
	};
};
namespace CommonVariable
{
	CameraBase* g_pCameraObject;

};
