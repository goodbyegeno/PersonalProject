#pragma once
#include "RenderEngineCommon.h"
#include "ModelDynamicData.h"
#include "IRenderableObject.h"
class ModelStaticData;

class RenderedObject : public IRenderableObject
{
public:
	RenderedObject();
	virtual ~RenderedObject();

	virtual bool IsGotAlphaBlend();
	virtual RenderEngine::RENDERTYPE	GetRenderedType() final;// { return RenderEngine::RENDERTYPE::CHARACTER; }

	virtual size_t GetRenderMethodHashCode();

	virtual const ORBITMATRIX4x4*	GetWorldMatrix()									{ return &_modelDynamicData.modelWorldPosition; }

	virtual const ModelStaticData*	GetModelStaticData()								{ return _modelStaticData; }
	virtual const void				SetModelStaticData(ModelStaticData* staticData)		{ _modelStaticData = staticData; }
	virtual ModelDynamicData*		GetModelDynamicData()								{ return &_modelDynamicData; }

private:
	ModelDynamicData		_modelDynamicData;
	ModelStaticData*		_modelStaticData;

};