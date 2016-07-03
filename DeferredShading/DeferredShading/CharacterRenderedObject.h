#pragma once
#include "RenderEngineCommon.h"
#include "ModelData_Dynamic.h"
#include "ModelData_Static.h"
#include "IRenderedObject.h"

class CharacterRenderedObject : public IRenderedObject
{
public:

	CharacterRenderedObject();
	virtual ~CharacterRenderedObject();


	virtual bool IsGotAlphaBlend()							{ return false; }
	RenderEngine::RenderedType GetRenderedType() final		{ return RenderEngine::RenderedType::Character; }
	RenderEngine::RenderingMode GetRenderedMode() final;

private:
	ModelData_Static	m_ModelData_Static;
	ModelData_Dynamic	m_ModelData_Dynamic;
};