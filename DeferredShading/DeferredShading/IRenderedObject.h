#pragma once
#include "RenderEngineCommon.h"

class ModelStaticData;
class ModelDynamicData;

class IRenderedObject
{

public:
	IRenderedObject() {};
	virtual ~IRenderedObject() = 0;
	
	virtual bool IsGotAlphaBlend() = 0;
	virtual RenderEngine::RENDERTYPE GetRenderedType() = 0;
	virtual RenderEngine::RENDERINGMODE GetRenderedMode() = 0;

	virtual const ModelStaticData*	GetModelStaticData() = 0;
	virtual const ModelDynamicData* GetModelDynamicData() = 0;

};