#pragma once
#include "RenderEngineCommon.h"
#include "ModelDynamicData.h"
#include "ModelStaticData.h"
#include "IRenderedObject.h"

class CharacterRenderedObject : public IRenderedObject
{
public:

	CharacterRenderedObject();
	virtual ~CharacterRenderedObject();


	virtual bool IsGotAlphaBlend();
	RenderEngine::RENDERTYPE	GetRenderedType() final	{ return RenderEngine::RENDERTYPE::CHARACTER; }
	RenderEngine::RENDERINGMODE GetRenderedMode() final { return _renderedMode; }

	const ModelStaticData*	GetMeshStaticData()			{ return &_ModelStaticData; }
	const ModelDynamicData* GetMeshDynamicData()		{ return &_ModelDynamicData; }
private:
	ModelDynamicData	_ModelDynamicData;
	ModelStaticData		_ModelStaticData;
	RenderEngine::RENDERINGMODE _renderedMode;

};