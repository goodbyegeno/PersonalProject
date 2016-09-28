#pragma once

class IRenderableObject;
class ModelStaticData;

class IGraphicsSystemFacade
{
public:
	IGraphicsSystemFacade() {};
	virtual ~IGraphicsSystemFacade() {};

	virtual bool AddRenderingRequest(IRenderableObject* renderObject) = 0;
	virtual ModelStaticData* GetStaticModel(size_t modelHashCode) = 0;
};