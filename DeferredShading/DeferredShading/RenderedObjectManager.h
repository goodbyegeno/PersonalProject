#pragma once
class GraphicsSystem;
class RenderedObjectManager
{
public:
	RenderedObjectManager(GraphicsSystem* pGraphicSystem);
	virtual ~RenderedObjectManager();

	void Initialize();
	void Reset();

	void Render();
	void PreUpdate(float fDeltaTime);
	void PostUpdate(float fDeltaTime);

	void Update(float fDeltaTime);
private:
	GraphicsSystem* m_pGraphicSystem;
};