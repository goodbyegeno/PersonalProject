#pragma once
#include "IRenderHelper.h"
class GraphicsDevice;

class RenderHelperDX : public IRenderHelper
{
public:
	RenderHelperDX(GraphicsDevice* graphicDevice);
	RenderHelperDX() = delete;
	virtual ~RenderHelperDX();

	bool RenderMesh(IGraphicDevice* graphicDevice);

private:
	
};