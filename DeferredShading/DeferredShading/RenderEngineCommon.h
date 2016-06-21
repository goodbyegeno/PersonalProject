#pragma once

namespace RenderEngine
{
	enum class MiddlewareType
	{
		DirectX,
		OpenGL,
		MAX
	};
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
