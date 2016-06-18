#pragma once
class GraphicsSystem;
class ShaderManager
{
public :
	ShaderManager(GraphicsSystem* pGraphicSystem);
	virtual ~ShaderManager();

	void Initialize();
	void Reset();

	void Update(float fDeltaTime);
private:
	GraphicsSystem* m_pGraphicSystem;
};