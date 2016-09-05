#pragma once
class GraphicsSystem;
class RenderedObjectManager
{
public:
	RenderedObjectManager(GraphicsSystem* graphicSystem);
	virtual ~RenderedObjectManager();

	bool Initialize();
	bool Reset();

	void Render();
	void PreUpdate(float deltaTime);
	void PostUpdate(float deltaTime);

	void Update(float deltaTime);
private:
	GraphicsSystem* _graphicSystem;
};