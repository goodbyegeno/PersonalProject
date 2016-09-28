#include "stdafx.h"
#include <Windows.h>
#include <chrono>
#include <ctime>
#include "TempTimer.h"


TimerObject::TimerObject()
{

}
TimerObject::~TimerObject()
{
}
bool TimerObject::Initialize()
{
	std::chrono::time_point<std::chrono::system_clock> tempTime = std::chrono::system_clock::now();
	std::chrono::duration<double> currentTime = tempTime.time_since_epoch();
	_previousTickTime = static_cast<float>(currentTime.count());
	return true;
}

bool TimerObject::Reset()
{
	std::chrono::time_point<std::chrono::system_clock> tempTime = std::chrono::system_clock::now();
	std::chrono::duration<double> currentTime = tempTime.time_since_epoch();
	_previousTickTime = static_cast<float>(currentTime.count());
	return true;
}

void TimerObject::PreUpdate()
{

	std::chrono::time_point<std::chrono::system_clock> tempTime = std::chrono::system_clock::now();
	std::chrono::duration<double> currentTime = tempTime.time_since_epoch();
	float tempTimeFloat = static_cast<float>(currentTime.count());

	_previousTickTime = tempTimeFloat - _previousTickTime;
}

void TimerObject::Update()
{

}
void TimerObject::PostUpdate()
{

}
