#include "ORBITMeshSubset.h"


ORBITMeshSubset::ORBITMeshSubset( int vertexCount, int vertexStart, int* vertexIndices) :
	_vertexCount(vertexCount),
	_vertexStart(vertexStart),
	_vertexIndices(vertexIndices),
	_subsetMaterial(nullptr)
{

}

ORBITMeshSubset::~ORBITMeshSubset()
{
	if (_vertexIndices)
		delete _vertexIndices;

	_vertexIndices = nullptr;
}

