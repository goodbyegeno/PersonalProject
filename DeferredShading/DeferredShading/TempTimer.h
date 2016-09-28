#pragma once

class TimerObject
{
public:
	TimerObject();
	virtual ~TimerObject();
	void PreUpdate();
	void Update();
	void PostUpdate();

	bool Initialize();
	bool Reset();

	float GetDeltaTime() { return _deltaTime; }
private:

	float _previousTickTime;
	float _deltaTime;


};