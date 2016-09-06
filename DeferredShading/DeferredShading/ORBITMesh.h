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
		void**	vertexBuffer;
		void*	indexBuffers;
		int		vertexBufferCount;
		int		vertexCount;
		int*	indices;
		int		indexCount;
		RenderEngine::ORBIT_FORMAT indexBufferFormat;

	};
	enum class SUBSETINDEXMAPPINGTYPE
	{
		LINEAR,
		STORED,
	};

	ORBITMesh(MeshInitialData& initialData);
	virtual ~ORBITMesh();

	ID3D11Buffer* const * GetVertexBuffersDX11()	const	{ return _vertexBufferDX11; }
	int GetVertexBufferCount() const						{ return _vertexBufferCount; }
	int GetVertexCount() const								{ return _vertexCount; }
	const int* GetIndices() const							{ return _indices; }
	int GetIndexCount()	const								{ return _indexCount; }
	const UINT* GetStrides() const							{ return _strides; }
	const UINT* GetOffsets() const							{ return _offsets; }
	ID3D11Buffer* GetIndexBufferDX11()						{ return _indexBuffersDX11; }

	ID3D11Buffer** GetWriteableVertexBuffersDX11() const	{ return _vertexBufferDX11; }
	int GetWriteableVertexCount() const						{ return _vertexCount; }
	int* GetWriteableIndices() const						{ return _indices; }
	int GetWriteableIndexCount() const						{ return _indexCount; }
	int GetSubsetCount() const								{ return _subsetCount; }
	
	SUBSETINDEXMAPPINGTYPE	GetSubsetIndexMappingType() const	{ return _subsetIndexMappingType; }
	const ORBITMeshSubset*	GetSubset()	const				{ return _meshSubset; }
	RenderEngine::ORBIT_FORMAT	GetIndexBufferFormat()			{ return _indexBufferFormat; }
private:

	SUBSETINDEXMAPPINGTYPE	_subsetIndexMappingType;

	union
	{
		ID3D11Buffer** _vertexBufferDX11;
	};
	union
	{
		ID3D11Buffer* _indexBuffersDX11;
	};
	//ORBITVertex*	_vertexArray;
	int				_vertexBufferCount;
	int				_vertexCount;
	int*			_indices;
	int				_indexCount;
	UINT*			_strides;
	UINT*			_offsets;

	int				_subsetCount;
	ORBITMeshSubset* _meshSubset;
	RenderEngine::ORBIT_FORMAT _indexBufferFormat;


	//int*			_subsetIndex;
};
