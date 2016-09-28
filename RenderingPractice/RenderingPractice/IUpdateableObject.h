#pragma once
class IUpdateableObject
{
public:
	IUpdateableObject() {};
	virtual ~IUpdateableObject() {};

	//UNDONE: thread safe
	virtual void PreUpdate(float deltaTime) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void PostUpdate(float deltaTime) = 0;
	
	//DONT NEED TO BE THREAD SAFE
	virtual void PhaseReady(float deltaTime) = 0;
	virtual void PhaseEnd(float deltaTime) = 0;

};