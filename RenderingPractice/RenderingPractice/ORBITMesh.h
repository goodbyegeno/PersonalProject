#pragma once
#include "IORBITReadonlyMesh.h"
#include "RenderEngineCommon.h"
#include <d3d11_4.h>
class ORBITVertex;
class ORBITMeshSubset;

class ORBITMesh
{

public:
	struct MeshInitialData
	{
		union
		{
			ID3D11Buffer** vertexBuffersDX11;
		};
		union
		{
			ID3D11Buffer* indexBuffersDX;
		};
		int		vertexBufferCount;
		int		vertexCount;
		UINT*	indices;
		int				indexCount;
		UINT*	strides;
		UINT*	offsets;
		int				subsetCount;
		ORBITMeshSubset** meshSubset;
		RenderEngine::ORBIT_FORMAT indexBufferFormat;

	};
	enum class SUBSETINDEXMAPPINGTYPE
	{
		LINEAR,
		STORED,
	};

	ORBITMesh(MeshInitialData& initialData);
	virtual ~ORBITMesh();

	ID3D11Buffer* const * GetVertexBuffersDX11()	const	{ return _vertexBuffersDX11; }
	int GetVertexBufferCount() const						{ return _vertexBufferCount; }
	int GetVertexCount() const								{ return _vertexCount; }
	const UINT* GetIndices() const							{ return _indices; }
	int GetIndexCount()	const								{ return _indexCount; }
	const UINT* GetStrides() const							{ return _strides; }
	const UINT* GetOffsets() const							{ return _offsets; }
	ID3D11Buffer* GetIndexBufferDX11() const				{ return _indexBuffersDX11; }

	ID3D11Buffer** GetWriteableVertexBuffersDX11() const	{ return _vertexBuffersDX11; }
	int GetWriteableVertexCount() const						{ return _vertexCount; }
	UINT* GetWriteableIndices() const						{ return _indices; }
	int GetWriteableIndexCount() const						{ return _indexCount; }
	int GetSubsetCount() const								{ return _subsetCount; }
	
	SUBSETINDEXMAPPINGTYPE		GetSubsetIndexMappingType() const	{ return _subsetIndexMappingType; }
	ORBITMeshSubset**			GetSubset()	const					{ return _meshSubset; }
	RenderEngine::ORBIT_FORMAT	GetIndexBufferFormat() const		{ return _indexBufferFormat; }
private:

	SUBSETINDEXMAPPINGTYPE	_subsetIndexMappingType;

	union
	{
		ID3D11Buffer** _vertexBuffersDX11;
	};
	union
	{
		ID3D11Buffer* _indexBuffersDX11;
	};
	//ORBITVertex*	_vertexArray;
	int				_vertexBufferCount;
	int				_vertexCount;
	UINT*			_indices;
	int				_indexCount;
	UINT*			_strides;
	UINT*			_offsets;
	int				_subsetCount;
	ORBITMeshSubset** _meshSubset;
	RenderEngine::ORBIT_FORMAT _indexBufferFormat;


	//int*			_subsetIndex;
};
