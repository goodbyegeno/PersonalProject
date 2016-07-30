#pragma once
#include "ShaderObjectDX.h"

class ShaderObjIdxDfdGbufferVSDX : public ShaderObjectDX
{
public:
	ShaderObjIdxDfdGbufferVSDX(std::string shaderName, ID3D11Device* deviceDX, ID3DBlob* shaderBuffer);
	ShaderObjIdxDfdGbufferVSDX() = delete;
	virtual ~ShaderObjIdxDfdGbufferVSDX();

	virtual bool Initialize();
	virtual bool Reset();
private:
	bool InitInputLayout_();

};