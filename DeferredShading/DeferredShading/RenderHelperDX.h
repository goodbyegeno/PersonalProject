#pragma once
#include "IRenderHelper.h"
class IGraphicsDevice;

class RenderHelperDX : public IRenderHelper
{
public:
	RenderHelperDX(IGraphicsDevice* graphicDevice);
	RenderHelperDX() = delete;
	virtual ~RenderHelperDX();

	bool RenderMesh(IGraphicDevice* graphicDevice);

private:
	
};