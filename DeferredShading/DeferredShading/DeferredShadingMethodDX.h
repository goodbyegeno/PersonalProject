#include "IDeferredShadingMethodImpl.h"
#pragma once
class DeferredShadingMethodDX : public IDeferredShadingMethodImpl
{
public:
	DeferredShadingMethodDX();
	virtual ~DeferredShadingMethodDX();



	void SetConstVariables();
	void SetRenderTarget();
private:

};