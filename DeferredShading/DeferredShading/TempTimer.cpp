#include "stdafx.h"
#include <Windows.h>
#include "TempTimer.h"

TimerObject::TimerObject()
{

}
TimerObject::~TimerObject()
{
}
bool TimerObject::Initialize()
{
	DWORD tempTime = timeGetTime();
	_previousTickTime = tempTime * 0.001f;
	return true;
}
bool TimerObject::Reset()
{
	DWORD tempTime = timeGetTime();
	_previousTickTime = tempTime * 0.001f;
	return true;
}
void TimerObject::PreUpdate()
{
	DWORD tempTime = timeGetTime();
	float tempTimeFloat = tempTime * 0.001f;
	_previousTickTime = tempTimeFloat - _previousTickTime;
}
void TimerObject::Update()
{

}
void TimerObject::PostUpdate()
{

}
