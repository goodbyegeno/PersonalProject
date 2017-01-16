#pragma once


class WindowObjectImpl_Windows : public IWindowObjectImpl
{
public:
	WindowObjectImpl_Windows();
	virtual ~WindowObjectImpl_Windows();

	bool Initialize();
	bool Reset();

	
};