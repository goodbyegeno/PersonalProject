#pragma once
namespace RenderEngineTest
{

	struct Vector2_Test
	{
		float x;
		float y;
	};
	struct Vector3_Test
	{
		float x;
		float y;
		float z;
	};
	struct Vector4_Test
	{
		float x;
		float y;
		float z;
		float w;
	};

	struct MeshVertex_Test
	{
		Vector4_Test Position;
		Vector4_Test Color;

		Vector2_Test TextureCoord;
		Vector2_Test NormalCoord;
		Vector2_Test SpecularCoord;
	};
}