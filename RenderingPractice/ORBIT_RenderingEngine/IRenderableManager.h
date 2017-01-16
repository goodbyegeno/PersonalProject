#pragma once
class IRenderableManager
{
public:
	IRenderableManager() {};
	virtual ~IRenderableManager() {};

	virtual void Render(float deltaTime) = 0;
};