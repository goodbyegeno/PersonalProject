#pragma once

class ORBITVertex;

class IORBITReadonlyMesh
{
public:
	IORBITReadonlyMesh() {};
	virtual ~IORBITReadonlyMesh() {};

	virtual const ORBITVertex* const GetVertices() const = 0;
	virtual int GetVertexCount() = 0;
	virtual const int* const GetIndices() const = 0;
	virtual int GetIndexCount() = 0;
};