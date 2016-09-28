#pragma once
#include "RenderEngineCommon.h"

class ORBITMesh;
class ModelStaticData
{
public:
	ModelStaticData(size_t hashCode, ORBITMesh** meshDatas, int meshCount, RenderEngine::RENDERINGMODE renderedMode, RenderEngine::RENDERTYPE _renderType);
	virtual ~ModelStaticData();

	size_t							GetHashCode() const		{ return _hashCode; }
	const ORBITMesh* const*			GetMeshDatas() const	{ return _meshData; }
	int								GetMeshCount() const { return _meshCount; }
	RenderEngine::RENDERINGMODE		GetRenderedMode() const	{ return _renderedMode; }
	RenderEngine::RENDERTYPE		GetRenderedType() const		{ return _renderType; }
	
	size_t							GetRenderMethodHashCode() const { return _shaderHash; }

	/*

	void		SetMeshDatas(ORBITMesh** meshDatas) { _meshData = meshDatas; }
	void		SetMeshCount(int meshCount)			{ _meshCount = meshCount; }
	*/
private:
	size_t		_hashCode;
	size_t		_shaderHash;

	ORBITMesh**	_meshData;
	int			_meshCount;
	RenderEngine::RENDERINGMODE _renderedMode;
	RenderEngine::RENDERTYPE _renderType;
	//bone Data;

};
