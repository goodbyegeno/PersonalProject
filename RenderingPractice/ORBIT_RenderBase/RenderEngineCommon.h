#pragma once
namespace RenderEngine
{
	enum class GRAPHICSAPITYPE
	{
		DIRECTX11_4,
		OPENGL,
		MAX
	};
	enum class FPSMODE
	{
		FLEXIBLE30,
		FLEXIBLE60,
		FIXED60,
		MONITOR,
		MAX
	};
	
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
	/*
	enum class INDEXEDDEFERREDSHADINGRT
	{
		ALBEDO,
		NORMAL,
		POSITION,
		SPECULAR,
		MAX
	};
	enum class FORWARDSHADINGRT
	{
		DIFFUSE,
		MAX
	};
	*/
	/*
	enum class RENDERINGMODE
	{
		DEFERRED_LIGHTING,
		DEFERRED_SHADING,
		INDEXED_DEFERRED_SHADING,
		FORWARD,
		FORWARD_PLUS,
		MAX
	};
	*/
	enum class PROJECTIONMODE
	{
		ISOMETRIC,
		PERSPECTIVE,
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


	//From DXGI_FORMAT. just rename for opengl compatible
	enum class ORBIT_FORMAT : unsigned int
	{
		ORBIT_FORMAT_UNKNOWN = 0,
		ORBIT_FORMAT_R32G32B32A32_TYPELESS = 1,
		ORBIT_FORMAT_R32G32B32A32_FLOAT = 2,
		ORBIT_FORMAT_R32G32B32A32_UINT = 3,
		ORBIT_FORMAT_R32G32B32A32_SINT = 4,
		ORBIT_FORMAT_R32G32B32_TYPELESS = 5,
		ORBIT_FORMAT_R32G32B32_FLOAT = 6,
		ORBIT_FORMAT_R32G32B32_UINT = 7,
		ORBIT_FORMAT_R32G32B32_SINT = 8,
		ORBIT_FORMAT_R16G16B16A16_TYPELESS = 9,
		ORBIT_FORMAT_R16G16B16A16_FLOAT = 10,
		ORBIT_FORMAT_R16G16B16A16_UNORM = 11,
		ORBIT_FORMAT_R16G16B16A16_UINT = 12,
		ORBIT_FORMAT_R16G16B16A16_SNORM = 13,
		ORBIT_FORMAT_R16G16B16A16_SINT = 14,
		ORBIT_FORMAT_R32G32_TYPELESS = 15,
		ORBIT_FORMAT_R32G32_FLOAT = 16,
		ORBIT_FORMAT_R32G32_UINT = 17,
		ORBIT_FORMAT_R32G32_SINT = 18,
		ORBIT_FORMAT_R32G8X24_TYPELESS = 19,
		ORBIT_FORMAT_D32_FLOAT_S8X24_UINT = 20,
		ORBIT_FORMAT_R32_FLOAT_X8X24_TYPELESS = 21,
		ORBIT_FORMAT_X32_TYPELESS_G8X24_UINT = 22,
		ORBIT_FORMAT_R10G10B10A2_TYPELESS = 23,
		ORBIT_FORMAT_R10G10B10A2_UNORM = 24,
		ORBIT_FORMAT_R10G10B10A2_UINT = 25,
		ORBIT_FORMAT_R11G11B10_FLOAT = 26,
		ORBIT_FORMAT_R8G8B8A8_TYPELESS = 27,
		ORBIT_FORMAT_R8G8B8A8_UNORM = 28,
		ORBIT_FORMAT_R8G8B8A8_UNORM_SRGB = 29,
		ORBIT_FORMAT_R8G8B8A8_UINT = 30,
		ORBIT_FORMAT_R8G8B8A8_SNORM = 31,
		ORBIT_FORMAT_R8G8B8A8_SINT = 32,
		ORBIT_FORMAT_R16G16_TYPELESS = 33,
		ORBIT_FORMAT_R16G16_FLOAT = 34,
		ORBIT_FORMAT_R16G16_UNORM = 35,
		ORBIT_FORMAT_R16G16_UINT = 36,
		ORBIT_FORMAT_R16G16_SNORM = 37,
		ORBIT_FORMAT_R16G16_SINT = 38,
		ORBIT_FORMAT_R32_TYPELESS = 39,
		ORBIT_FORMAT_D32_FLOAT = 40,
		ORBIT_FORMAT_R32_FLOAT = 41,
		ORBIT_FORMAT_R32_UINT = 42,
		ORBIT_FORMAT_R32_SINT = 43,
		ORBIT_FORMAT_R24G8_TYPELESS = 44,
		ORBIT_FORMAT_D24_UNORM_S8_UINT = 45,
		ORBIT_FORMAT_R24_UNORM_X8_TYPELESS = 46,
		ORBIT_FORMAT_X24_TYPELESS_G8_UINT = 47,
		ORBIT_FORMAT_R8G8_TYPELESS = 48,
		ORBIT_FORMAT_R8G8_UNORM = 49,
		ORBIT_FORMAT_R8G8_UINT = 50,
		ORBIT_FORMAT_R8G8_SNORM = 51,
		ORBIT_FORMAT_R8G8_SINT = 52,
		ORBIT_FORMAT_R16_TYPELESS = 53,
		ORBIT_FORMAT_R16_FLOAT = 54,
		ORBIT_FORMAT_D16_UNORM = 55,
		ORBIT_FORMAT_R16_UNORM = 56,
		ORBIT_FORMAT_R16_UINT = 57,
		ORBIT_FORMAT_R16_SNORM = 58,
		ORBIT_FORMAT_R16_SINT = 59,
		ORBIT_FORMAT_R8_TYPELESS = 60,
		ORBIT_FORMAT_R8_UNORM = 61,
		ORBIT_FORMAT_R8_UINT = 62,
		ORBIT_FORMAT_R8_SNORM = 63,
		ORBIT_FORMAT_R8_SINT = 64,
		ORBIT_FORMAT_A8_UNORM = 65,
		ORBIT_FORMAT_R1_UNORM = 66,
		ORBIT_FORMAT_R9G9B9E5_SHAREDEXP = 67,
		ORBIT_FORMAT_R8G8_B8G8_UNORM = 68,
		ORBIT_FORMAT_G8R8_G8B8_UNORM = 69,
		ORBIT_FORMAT_BC1_TYPELESS = 70,
		ORBIT_FORMAT_BC1_UNORM = 71,
		ORBIT_FORMAT_BC1_UNORM_SRGB = 72,
		ORBIT_FORMAT_BC2_TYPELESS = 73,
		ORBIT_FORMAT_BC2_UNORM = 74,
		ORBIT_FORMAT_BC2_UNORM_SRGB = 75,
		ORBIT_FORMAT_BC3_TYPELESS = 76,
		ORBIT_FORMAT_BC3_UNORM = 77,
		ORBIT_FORMAT_BC3_UNORM_SRGB = 78,
		ORBIT_FORMAT_BC4_TYPELESS = 79,
		ORBIT_FORMAT_BC4_UNORM = 80,
		ORBIT_FORMAT_BC4_SNORM = 81,
		ORBIT_FORMAT_BC5_TYPELESS = 82,
		ORBIT_FORMAT_BC5_UNORM = 83,
		ORBIT_FORMAT_BC5_SNORM = 84,
		ORBIT_FORMAT_B5G6R5_UNORM = 85,
		ORBIT_FORMAT_B5G5R5A1_UNORM = 86,
		ORBIT_FORMAT_B8G8R8A8_UNORM = 87,
		ORBIT_FORMAT_B8G8R8X8_UNORM = 88,
		ORBIT_FORMAT_R10G10B10_XR_BIAS_A2_UNORM = 89,
		ORBIT_FORMAT_B8G8R8A8_TYPELESS = 90,
		ORBIT_FORMAT_B8G8R8A8_UNORM_SRGB = 91,
		ORBIT_FORMAT_B8G8R8X8_TYPELESS = 92,
		ORBIT_FORMAT_B8G8R8X8_UNORM_SRGB = 93,
		ORBIT_FORMAT_BC6H_TYPELESS = 94,
		ORBIT_FORMAT_BC6H_UF16 = 95,
		ORBIT_FORMAT_BC6H_SF16 = 96,
		ORBIT_FORMAT_BC7_TYPELESS = 97,
		ORBIT_FORMAT_BC7_UNORM = 98,
		ORBIT_FORMAT_BC7_UNORM_SRGB = 99,
		ORBIT_FORMAT_AYUV = 100,
		ORBIT_FORMAT_Y410 = 101,
		ORBIT_FORMAT_Y416 = 102,
		ORBIT_FORMAT_NV12 = 103,
		ORBIT_FORMAT_P010 = 104,
		ORBIT_FORMAT_P016 = 105,
		ORBIT_FORMAT_420_OPAQUE = 106,
		ORBIT_FORMAT_YUY2 = 107,
		ORBIT_FORMAT_Y210 = 108,
		ORBIT_FORMAT_Y216 = 109,
		ORBIT_FORMAT_NV11 = 110,
		ORBIT_FORMAT_AI44 = 111,
		ORBIT_FORMAT_IA44 = 112,
		ORBIT_FORMAT_P8 = 113,
		ORBIT_FORMAT_A8P8 = 114,
		ORBIT_FORMAT_B4G4R4A4_UNORM = 115,
		ORBIT_FORMAT_P208 = 130,
		ORBIT_FORMAT_V208 = 131,
		ORBIT_FORMAT_V408 = 132,
		ORBIT_FORMAT_FORCE_UINT = 0xffffffff
	};

};
