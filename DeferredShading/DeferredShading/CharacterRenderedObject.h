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


	virtual bool IsGotAlphaBlend()							{ return false; }
	RenderEngine::RenderedType	GetRenderedType() final		{ return RenderEngine::RenderedType::Character; }
	RenderEngine::RenderingMode GetRenderedMode() final;

	const ModelStaticData*	GetMeshStaticData()			{ return &_ModelStaticData; }
	const ModelDynamicData* GetMeshDynamicData()		{ return &_ModelDynamicData; }
private:
	ModelDynamicData	_ModelDynamicData;
	ModelStaticData		_ModelStaticData;
};