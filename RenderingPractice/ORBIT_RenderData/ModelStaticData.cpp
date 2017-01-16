#include "stdafx.h"
#include "ModelStaticData.h"


ModelStaticData::ModelStaticData(size_t hashCode, ORBITMesh** meshDatas, int meshCount, size_t renderingMethodHash, RenderEngine::RENDERTYPE renderType) :
	_hashCode(hashCode),
	_renderingMethodHash(renderingMethodHash),
	_meshData(meshDatas),
	_meshCount(meshCount),
	_renderType(renderType)
{

}

ModelStaticData::~ModelStaticData()
{

}