#pragma once
#include "RenderEngineCommon.h"

class IRenderedObject
{

public:
	IRenderedObject() {};
	virtual ~IRenderedObject() = 0;
	
	virtual bool IsGotAlphaBlend() = 0;
	virtual RenderEngine::RenderedType GetRenderedType() = 0;
	virtual RenderEngine::RenderingMode GetRenderedMode() = 0;
};