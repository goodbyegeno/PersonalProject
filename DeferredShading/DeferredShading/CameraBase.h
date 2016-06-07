#pragma once
#include <directxmath.h>
#include <d3d11.h>

class CameraBase
{
public:
	CameraBase();
	virtual ~CameraBase();

	bool Initialize();
	bool Reset();

	void Update(float fDelta);
	
	DirectX::XMMATRIX GetViewMatrix()	{ return m_matViewMatrix; }
	DirectX::XMVECTOR GetPosition()		{ return m_vecPosition; }
	DirectX::XMVECTOR GetDirection()	{ return m_vecDirection; }
	DirectX::XMVECTOR GetUpVector()		{ return m_vecUpVector; }
	DirectX::XMVECTOR GetRightVector()	{ return m_vecRightVector; }
private:

	DirectX::XMMATRIX m_matViewMatrix;
	DirectX::XMVECTOR m_vecPosition;
	DirectX::XMVECTOR m_vecDirection;
	DirectX::XMVECTOR m_vecUpVector;
	DirectX::XMVECTOR m_vecRightVector;

};