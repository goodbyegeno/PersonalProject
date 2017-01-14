#include "stdafx.h"
#include "CustomMatrix.h"

ORBITMATRIX4x4::ORBITMATRIX4x4()
{

}
ORBITMATRIX4x4::~ORBITMATRIX4x4()
{

}

ORBITMATRIX4x4 ORBITMATRIX4x4::operator=(const ORBITMATRIX4x4& rMatrix)
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
ORBITMATRIX4x4 ORBITMATRIX4x4::operator+(const ORBITMATRIX4x4& rMatrix) const
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

ORBITMATRIX4x4 ORBITMATRIX4x4::operator-(const ORBITMATRIX4x4& rMatrix) const
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
ORBITMATRIX4x4 ORBITMATRIX4x4::operator=(const DirectX::XMFLOAT4X4& rMatrix)
{
	this->_11 = rMatrix._11;
	this->_12 = rMatrix._12;
	this->_13 = rMatrix._13;
	this->_14 = rMatrix._14;
	this->_21 = rMatrix._21;
	this->_22 = rMatrix._22;
	this->_23 = rMatrix._23;
	this->_24 = rMatrix._24;
	this->_31 = rMatrix._31;
	this->_32 = rMatrix._32;
	this->_33 = rMatrix._33;
	this->_34 = rMatrix._34;
	this->_41 = rMatrix._41;
	this->_42 = rMatrix._42;
	this->_43 = rMatrix._43;
	this->_44 = rMatrix._44;
}
void ORBITMATRIX4x4::ConvertTo(DirectX::XMFLOAT4X4& lMatrix)
{
	lMatrix._11 = this->_11;
	lMatrix._12 = this->_12;
	lMatrix._13 = this->_13;
	lMatrix._14 = this->_14;
	lMatrix._21 = this->_21;
	lMatrix._22 = this->_22;
	lMatrix._23 = this->_23;
	lMatrix._24 = this->_24;
	lMatrix._31 = this->_31;
	lMatrix._32 = this->_32;
	lMatrix._33 = this->_33;
	lMatrix._34 = this->_34;
	lMatrix._41 = this->_41;
	lMatrix._42 = this->_42;
	lMatrix._43 = this->_43;
	lMatrix._44 = this->_44;
}
