#pragma once

class IDeferredShadingMethodImpl
{
public:
	IDeferredShadingMethodImpl() {}
	virtual ~IDeferredShadingMethodImpl() {}

	virtual bool Initialize(ShaderManager* pShaderManager) = 0;
	virtual bool Reset(ShaderManager* pShaderManager) = 0;

};