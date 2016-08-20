#pragma once
#include "CustomVector.h"

class ORBITVertex
{
public:
	ORBITVertex();
	virtual ~ORBITVertex();

	const ORBITFLOAT4& GetPosition()	{ return _position; }
	const ORBITFLOAT4& GetNormal()		{ return _normal; }
	const ORBITFLOAT2& GetUV()			{ return _uv; }

	void SetPosition(ORBITFLOAT4 position)	{ _position = position; }
	void SetNormal(ORBITFLOAT4 normal)		{ _normal = normal; }
	void SetUV(ORBITFLOAT2 uv)				{ _uv = uv; }

private:

	ORBITFLOAT4 _position;
	ORBITFLOAT4 _normal;
	ORBITFLOAT2 _uv;

};