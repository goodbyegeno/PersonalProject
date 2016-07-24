#pragma once


class ICameraMovement
{
public:
	ICameraMovement() {}

	virtual ~ICameraMovement() {}

private:
	virtual void Update(float deltaTime) = 0;


};