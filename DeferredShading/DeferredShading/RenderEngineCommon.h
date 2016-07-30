#pragma once

namespace RenderEngine
{
	/*
	enum class RENDERTARGETTYPE
	{
		//deferred
		ALBEDO,
		NORMAL,
		SPECULAR,
		POSITION,
		MAX
	};
	*/
	enum class INDEXEDDEFERREDSHADINGRT
	{
		ALBEDO,
		NORMAL,
		POSITION,
		SPECULAR,
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

	enum class SHADERTYPE
	{
		VERTEXSHADER,
		PIXELSHADER,				//FRAGMENT SHADER
		DOMAINSHADER,				//DXONLY
		GEOMETRYSHADER,
		HULLSHADER,					//DXONLY
		COMPUTESHADER,
		MAX
	};
};
