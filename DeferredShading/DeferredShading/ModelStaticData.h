#pragma once

class ORBITMesh;
class ModelStaticData
{
public:
	ModelStaticData();
	virtual ~ModelStaticData();

	const ORBITMesh* const* GetMeshDatas() const	{ return _meshData; }
	int			GetMeshCount() const				{ return _meshCount; }

	void		SetMeshDatas(ORBITMesh** meshDatas) { _meshData = meshDatas; }
	void		SetMeshCount(int meshCount)			{ _meshCount = meshCount; }
private:
	ORBITMesh**	_meshData;
	int			_meshCount;

	//bone Data;

};
