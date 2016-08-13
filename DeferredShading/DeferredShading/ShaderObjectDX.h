#pragma once
#include <string>
#include <d3d11_2.h>
#include "IShaderObejct.h"
class ShaderObjectDX : public IShaderObject
{
public:

	ShaderObjectDX(std::string shaderName, ID3D11Device* deviceDX, ID3DBlob* shaderBuffer, ID3D11DeviceChild* shaderData);
	ShaderObjectDX() = delete;
	virtual ~ShaderObjectDX();
	
	virtual bool Initialize()					{ return true; }
	virtual bool Reset()						{ return true; }

	void* GetShader()							{ return _shaderData; }
	void* GetBuffer()							{ return _shaderBuffer; }
	size_t GetHashcode()						{ return _shaderNameHash; }
	virtual RenderEngine::SHADERTYPE GetShaderType()	{ return RenderEngine::SHADERTYPE::MAX; }
	const std::string& GetName()				{ return _shaderName; }
protected:

	std::string					_shaderName;
	size_t						_shaderNameHash;
	ID3D11DeviceChild*			_shaderData;
	ID3DBlob*					_shaderBuffer;
	ID3D11Device*				_device;
	//ID3D11InputLayout*			_inputLayout;

};