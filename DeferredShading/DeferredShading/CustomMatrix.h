#pragma once
#include <cstring>
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

	inline XMFLOAT4X4& XMFLOAT4X4::operator=
		(
			const XMFLOAT4X4& Float4x4
			)
	{
		XMVECTOR V1 = XMLoadFloat4((const XMFLOAT4*)&Float4x4._11);
		XMVECTOR V2 = XMLoadFloat4((const XMFLOAT4*)&Float4x4._21);
		XMVECTOR V3 = XMLoadFloat4((const XMFLOAT4*)&Float4x4._31);
		XMVECTOR V4 = XMLoadFloat4((const XMFLOAT4*)&Float4x4._41);

		XMStoreFloat4((XMFLOAT4*)&_11, V1);
		XMStoreFloat4((XMFLOAT4*)&_21, V2);
		XMStoreFloat4((XMFLOAT4*)&_31, V3);
		XMStoreFloat4((XMFLOAT4*)&_41, V4);

		return *this;
	}

	ORBITMATRIX4x4 operator=(const ORBITMATRIX4x4& rMatrix)
	{
		//### should change later.
		ORBITMATRIX4x4 temp;
		memcpy(this->m, rMatrix.m, sizeof(float) * 16);

		/*for (int matrixFirstIndex = 0; matrixFirstIndex < 4; matrixFirstIndex++)
		{
			for (int matrixSecondIndex = 0; matrixSecondIndex < 4; matrixSecondIndex++)
			{
				temp.m[matrixFirstIndex][matrixSecondIndex] = m[matrixFirstIndex][matrixSecondIndex] + rMatrix.m[matrixFirstIndex][matrixSecondIndex];
			}
		}*/
		return temp;
	}
	ORBITMATRIX4x4 operator+(const ORBITMATRIX4x4& rMatrix) const
	{
		ORBITMATRIX4x4 temp;
		for (int matrixFirstIndex = 0; matrixFirstIndex < 4; matrixFirstIndex++)
		{
			for (int matrixSecondIndex = 0; matrixSecondIndex < 4; matrixSecondIndex++)
			{
				temp.m[matrixFirstIndex][matrixSecondIndex] = m[matrixFirstIndex][matrixSecondIndex] + rMatrix.m[matrixFirstIndex][matrixSecondIndex];
			}
		}
		return temp;
	}

	ORBITMATRIX4x4 operator-(const ORBITMATRIX4x4& rMatrix) const
	{
		ORBITMATRIX4x4 temp;
		for (int matrixFirstIndex = 0; matrixFirstIndex < 4; matrixFirstIndex++)
		{
			for (int matrixSecondIndex = 0; matrixSecondIndex < 4; matrixSecondIndex++)
			{
				temp.m[matrixFirstIndex][matrixSecondIndex] = m[matrixFirstIndex][matrixSecondIndex] - rMatrix.m[matrixFirstIndex][matrixSecondIndex];
			}
		}
		return temp;
	}
};