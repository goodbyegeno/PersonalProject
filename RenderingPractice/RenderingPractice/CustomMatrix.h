#pragma once
namespace DirectX
{
	class XMFLOAT4X4;
};
class ORBITMATRIX4x4
{
public:
	ORBITMATRIX4x4();
	virtual ~ORBITMATRIX4x4();
	union {
		struct {
			float _11;
			float _12;
			float _13;
			float _14;
			float _21;
			float _22;
			float _23;
			float _24;
			float _31;
			float _32;
			float _33;
			float _34;
			float _41;
			float _42;
			float _43;
			float _44;
		};
		float m[4][4];
	};

	void ConvertTo(DirectX::XMFLOAT4X4& lMatrix);
	ORBITMATRIX4x4 operator=(const ORBITMATRIX4x4& rMatrix);
	ORBITMATRIX4x4 operator=(const DirectX::XMFLOAT4X4& rMatrix);
	ORBITMATRIX4x4 operator+(const ORBITMATRIX4x4& rMatrix) const;
	ORBITMATRIX4x4 operator-(const ORBITMATRIX4x4& rMatrix) const;
	

};