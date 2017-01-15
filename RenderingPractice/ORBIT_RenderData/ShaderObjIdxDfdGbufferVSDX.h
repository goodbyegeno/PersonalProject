#pragma once
#include "ShaderObjectDX.h"

class ShaderObjIdxDfdGbufferVSDX : public ShaderObjectDX
{
public:
	ShaderObjIdxDfdGbufferVSDX(std::wstring shaderName, ID3D11Device3* deviceDX, ID3DBlob* shaderBuffer, ID3D11DeviceChild* shaderData);
	ShaderObjIdxDfdGbufferVSDX() = delete;
	virtual ~ShaderObjIdxDfdGbufferVSDX();

	virtual bool Initialize();
	virtual bool Reset();
private:
	//bool InitInputLayout_();

};