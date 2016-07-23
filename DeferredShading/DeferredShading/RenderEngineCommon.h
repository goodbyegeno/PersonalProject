#pragma once

namespace RenderEngine
{

	enum class RENDERTARGETTYPE
	{
		//deferred
		ALBEDO,
		NORMAL,
		SPECULAR,
		POSITION,
		MAX
	};

	enum class RENDERINGMODE
	{
		DEFERRED_LIGHTING,
		DEFERRED_SHADING,
		INDEXED_DEFERRED_SHADING,
		FORWARD,
		FORWARD_PLUS,
		MAX
	};

	enum class RENDERTYPE
	{
		CHARACTER,
		SKYBOX,
		MAX
	};
};
