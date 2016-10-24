#include "stdafx.h"
#include "ORBITMesh.h"
#include "ORBITVertex.h"

ORBITMesh::ORBITMesh(MeshInitialData& initialData) :
	_vertexCount(initialData.vertexCount),
	_indices(initialData.indices),
	_indexCount(initialData.indexCount),
	_strides(initialData.strides),
	_offsets(initialData.offsets),
	_subsetCount(initialData.subsetCount),
	_meshSubset(initialData.meshSubset),
	_subsetIndexMappingType(initialData.subsetIndexMappingType)
{
}

ORBITMesh::~ORBITMesh()
{
}