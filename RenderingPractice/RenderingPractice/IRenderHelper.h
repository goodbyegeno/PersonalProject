#pragma once
class IGraphicDevice;

class IRenderHelper
{
public:
	IRenderHelper() {}
	virtual ~IRenderHelper() {}

	virtual bool RenderMesh(IGraphicDevice* graphicDevice) = 0;

};