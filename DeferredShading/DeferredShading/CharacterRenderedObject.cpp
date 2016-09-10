#include "stdafx.h"
#include "CharacterRenderedObject.h"

CharacterRenderedObject::CharacterRenderedObject() :
	_renderedMode( RenderEngine::RENDERINGMODE::FORWARD)
{

}
CharacterRenderedObject::~CharacterRenderedObject()
{

}
bool CharacterRenderedObject::IsGotAlphaBlend() 
{ 
	return false; 
}
/*
void CharacterRenderedObject::FlushRender()
{

}
*/