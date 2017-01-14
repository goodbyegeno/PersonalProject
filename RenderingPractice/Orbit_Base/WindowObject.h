#pragma once
class IWindowObjectImpl;

class WindowObject
{
public:
	WindowObject();
	virtual ~WindowObject();

	bool Initialize();
	bool Reset();

private:
	IWindowObjectImpl* windowObjectImpl;
};