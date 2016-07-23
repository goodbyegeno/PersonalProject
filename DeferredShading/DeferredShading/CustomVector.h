#pragma once


class IORBITVECTOR
{
public:
	IORBITVECTOR();
	virtual ~IORBITVECTOR();

	virtual void Normalized() = 0;
};


class ORBITVECTOR2 : public IORBITVECTOR
{
public:
	ORBITVECTOR2();
	ORBITVECTOR2(float x, float y);

	virtual ~ORBITVECTOR2();

	virtual void Normalized();
	ORBITVECTOR2 Normalize();

private:
	float _x;
	float _y;

};
class ORBITVECTOR3 : public IORBITVECTOR
{
public:
	ORBITVECTOR3();
	ORBITVECTOR3(float x, float y, float z);

	virtual ~ORBITVECTOR3();

	virtual void Normalized();
	ORBITVECTOR3 Normalize();

private:
	float _x;
	float _y;
	float _z;

};
class ORBITVECTOR4 : public IORBITVECTOR
{
public:
	ORBITVECTOR4();
	ORBITVECTOR4(float x, float y, float z, float w);

	virtual ~ORBITVECTOR4();

	virtual void Normalized();
	ORBITVECTOR4 Normalize();

private:
	float _x;
	float _y;
	float _z;
	float _w;
};

