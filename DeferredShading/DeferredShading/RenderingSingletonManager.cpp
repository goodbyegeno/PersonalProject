#include "stdafx.h"
#include "RenderingSingletonManager.h"
#include "DXHelper11.h"
RenderingSingletonManager* RenderingSingletonManager::_instance = nullptr;

RenderingSingletonManager::RenderingSingletonManager()
{
	_dxHelper11 = new DXHelper11();
}

RenderingSingletonManager::~RenderingSingletonManager()
{
	delete _dxHelper11;
}

