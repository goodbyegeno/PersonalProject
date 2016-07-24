#pragma once


class IORBITFLOAT
{
public:
	IORBITFLOAT() {}
	virtual ~IORBITFLOAT() {}

};


class ORBITFLOAT2 : public IORBITFLOAT
{
public:
	ORBITFLOAT2();
	ORBITFLOAT2(float x, float y);

	virtual ~ORBITFLOAT2();


	ORBITFLOAT2 operator*(const int& rNum) const
	{
		return ORBITFLOAT2(_x * rNum, _y * rNum);
	}
	ORBITFLOAT2 operator+(const ORBITFLOAT2& rParam) const
	{
		return ORBITFLOAT2(_x + rParam._x, _y + rParam._y);
	}
	ORBITFLOAT2 operator-(const ORBITFLOAT2& rParam) const
	{
		return ORBITFLOAT2(_x - rParam._x, _y - rParam._y);
	}
private:
	float _x;
	float _y;

};
class ORBITFLOAT3 : public IORBITFLOAT
{
public:
	ORBITFLOAT3();
	ORBITFLOAT3(float x, float y, float z);

	virtual ~ORBITFLOAT3();


	ORBITFLOAT3 operator*(const int& rNum) const
	{
		return ORBITFLOAT3(_x * rNum, _y * rNum, _z * rNum);
	}
	ORBITFLOAT3 operator+(const ORBITFLOAT3& rParam) const
	{
		return ORBITFLOAT3(_x + rParam._x, _y + rParam._y, _z + rParam._z);
	}

	ORBITFLOAT3 operator-(const ORBITFLOAT3& rParam) const
	{
		return ORBITFLOAT3(_x - rParam._x, _y - rParam._y, _z - rParam._z);
	}
private:
	float _x;
	float _y;
	float _z;

};
class ORBITFLOAT4 : public IORBITFLOAT
{
public:
	ORBITFLOAT4();
	ORBITFLOAT4(float x, float y, float z, float w);

	virtual ~ORBITFLOAT4();

	ORBITFLOAT4 operator*(const int &rNum) const
	{
		return ORBITFLOAT4(_x * rNum, _y + rNum, _z + rNum, _w + rNum);
	}

	ORBITFLOAT4 operator+(const ORBITFLOAT4& rParam) const
	{
		return ORBITFLOAT4(_x + rParam._x, _y + rParam._y, _z + rParam._z, _w + rParam._w);
	}

	ORBITFLOAT4 operator-(const ORBITFLOAT4& rParam) const
	{
		return ORBITFLOAT4(_x - rParam._x, _y - rParam._y, _z - rParam._z, _w - rParam._w);
	}
private:
	float _x;
	float _y;
	float _z;
	float _w;
};

