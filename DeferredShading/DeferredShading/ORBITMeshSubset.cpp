#include "stdafx.h"
#include "ORBITMeshSubset.h"

ORBITMeshSubset::ORBITMeshSubset(int indexCount, int indexStart, int vertexStart) :
	_indexCount(indexCount),
	_indexStart(indexStart),
	_vertexStart(vertexStart),
	_subsetMaterial(nullptr)
{

}

ORBITMeshSubset::~ORBITMeshSubset()
{

	_subsetMaterial = nullptr;
}

