#include "stdafx.h"
#include "WindowObject.h"
#include "IWindowObjectImpl.h"
#include "WindowObjectImpl.h"

WindowObject::WindowObject()
{
}

WindowObject::~WindowObject()
{
	delete windowObjectImpl;
}

// TODO: create different Impl object depend os
bool WindowObject::Initialize()
{
	windowObjectImpl = new WindowObjectImpl_Windows();
	bool result = false;
	result = windowObjectImpl->Initialize();

	return result;
}

bool WindowObject::Reset()
{
	bool result = false;
	result = windowObjectImpl->Reset();

	return result;

}
