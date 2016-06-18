#pragma once
#include "RenderEngineCommon.h"
class CharacterRenderedObject : public IRenderedObject
{
public:

	CharacterRenderedObject();
	virtual ~CharacterRenderedObject();

	virtual bool IsGotAlphaBlend()							{ return false; }
	RenderEngine::RenderedType GetRenderedType() final	{ return RenderEngine::RenderedType::Character; }

	void FlushRender() final;
private:

};