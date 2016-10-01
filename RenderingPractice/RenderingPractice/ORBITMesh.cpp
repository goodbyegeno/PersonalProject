#include "stdafx.h"
#include "ORBITMesh.h"
#include "ORBITVertex.h"

ORBITMesh::ORBITMesh(MeshInitialData& initialData) :
	_vertexBuffersDX11(initialData.vertexBuffersDX11),
	_vertexBufferCount(initialData.vertexBufferCount),
	_vertexCount(initialData.vertexCount),
	_indices(initialData.indices),
	_indexCount(initialData.indexCount),
	_indexBufferFormat(initialData.indexBufferFormat),
	_strides(initialData.strides),
	_offsets(initialData.offsets),
	_subsetCount(initialData.subsetCount),
	_meshSubset(initialData.meshSubset)
{
}

ORBITMesh::~ORBITMesh()
{
}