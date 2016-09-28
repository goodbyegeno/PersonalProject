#pragma once
#include <d3d11_4.h>
#include <DirectXMath.h>
#include "RenderEngineCommon.h"
class DXHelper11
{
public:
	DXHelper11();
	virtual ~DXHelper11();

	DXGI_FORMAT GetIndexBufferFormat(RenderEngine::ORBIT_FORMAT indexFormat) const;

private:
	//no varialbes. only method
};

