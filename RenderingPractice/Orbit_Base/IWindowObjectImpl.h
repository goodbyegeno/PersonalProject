#pragma once

class IWindowObjectImpl
{
public:
	IWindowObjectImpl() {}
	virtual ~IWindowObjectImpl() {}

	virtual bool Initialize();
	virtual bool Reset();
};