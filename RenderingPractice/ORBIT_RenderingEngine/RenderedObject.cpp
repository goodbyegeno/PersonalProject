#include "stdafx.h"
#include "RenderedObject.h"
#include "ModelStaticData.h"
RenderedObject::RenderedObject() 
{

}
RenderedObject::~RenderedObject()
{

}
bool RenderedObject::IsGotAlphaBlend() 
{ 
	return false; 
}

RenderEngine::RENDERTYPE RenderedObject::GetRenderedType() 
{
	if (_modelStaticData)
		return _modelStaticData->GetRenderedType();
	else
		return RenderEngine::RENDERTYPE::MAX;
}

size_t RenderedObject::GetRenderMethodHashCode()
{
	if (_modelStaticData)
		return _modelStaticData->GetRenderMethodHashCode();
	else
		return 0;
}