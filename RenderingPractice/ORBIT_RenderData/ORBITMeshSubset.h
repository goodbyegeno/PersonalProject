#pragma once
class ORBITMaterial;

class ORBITMeshSubset
{

public:
	ORBITMeshSubset(int indexCount, int indexStart, int vertexStart);
	ORBITMeshSubset() = delete;
	virtual ~ORBITMeshSubset();

	int					GetVertexStart() const		{ return _vertexStart; }
	int					GetIndexCount() const		{ return _indexCount; }
	int					GetIndexStart() const		{ return _indexStart; }
	/*
	const int*			GetVertexIndices() const	{ return _vertexIndices; }
	*/
	const ORBITMaterial* GetMaterial() const		{ return _subsetMaterial; }
private:

	int					_indexStart;
	int					_indexCount;
	int					_vertexStart;
	//int*				_vertexIndices;

	ORBITMaterial* _subsetMaterial;

};
