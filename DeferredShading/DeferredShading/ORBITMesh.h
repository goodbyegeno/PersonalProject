#pragma once
#include "IORBITReadonlyMesh.h"
class ORBITVertex;
class ORBITMesh
{
public:
	ORBITMesh(void* vertexBuffer, int vertexCount, int* indices, int indexCount);
	virtual ~ORBITMesh();

	virtual void* GetVertexBuffer()	const					{ return _vertexBuffer; }
	virtual int GetVertexCount()							{ return _vertexCount; }
	virtual int* GetIndices()								{ return _indices; }
	virtual int GetIndexCount()								{ return _indexCount; }

	void* GetWriteableVertices()							{ return _vertexBuffer; }
	int GetWriteableVertexCount()							{ return _vertexCount; }
	int* GetWriteableIndices()								{ return _indices; }
	int GetWriteableIndexCount()							{ return _indexCount; }

private:

	
	void*			_vertexBuffer;
	//ORBITVertex*	_vertexArray;
	int				_vertexCount;
	int*			_indices;
	int				_indexCount;
	int				_subsetCount;
	int*			_subsetIndex;
};
