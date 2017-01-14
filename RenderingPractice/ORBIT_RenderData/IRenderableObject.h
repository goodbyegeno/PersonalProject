#pragma once
#include "RenderEngineCommon.h"

class ModelStaticData;
class ModelDynamicData;
class ORBITMATRIX4x4;

class IRenderableObject
{

public:
	IRenderableObject() {};
	virtual ~IRenderableObject() {};

	virtual bool IsGotAlphaBlend() = 0;
	virtual size_t GetRenderMethodHashCode() = 0;
	virtual RenderEngine::RENDERTYPE GetRenderedType() = 0;
	//virtual RenderEngine::RENDERINGMODE GetRenderedMode() = 0;

	virtual const ModelStaticData*	GetModelStaticData() = 0;
	virtual const ModelDynamicData* GetModelDynamicData() = 0;

	virtual const ORBITMATRIX4x4*	GetWorldMatrix() = 0;

};