#pragma once
#include <d3d11_4.h>
class ORBITMaterial
{
public:
	ORBITMaterial();
	virtual ~ORBITMaterial();

	ID3D11ShaderResourceView1* GetDiffuseRVDX11() const { return _diffuseRV11; }
	ID3D11ShaderResourceView1* GetSpecularRVDX11() const { return _specularRV11; }
	ID3D11ShaderResourceView1* GetNormalRVDX11() const { return _normalRV11; }

private:
	union
	{
		ID3D11ShaderResourceView1* _diffuseRV11;
	};
	union
	{
		ID3D11ShaderResourceView1* _specularRV11;
	};
	union
	{
		ID3D11ShaderResourceView1* _normalRV11;
	};
};