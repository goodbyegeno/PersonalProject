#pragma once
class GraphicsSystem;
class ShaderManager
{
public :
	ShaderManager(GraphicsSystem* pGraphicSystem);
	virtual ~ShaderManager();

	void Initialize();
	void Reset();
	void PreUpdate(float fDeltaTime);
	void PostUpdate(float fDeltaTime);

	void Update(float fDeltaTime);
private:
	GraphicsSystem* m_pGraphicSystem;
};