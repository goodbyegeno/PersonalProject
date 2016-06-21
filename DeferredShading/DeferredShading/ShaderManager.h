#pragma once
class GraphicsSystem;
class IShaderObject;

class ShaderManager
{
public :
	ShaderManager(GraphicsSystem* pGraphicSystem);
	virtual ~ShaderManager();

	bool Initialize();
	bool PostInitialize();
	bool Reset();
	bool PostReset();
	void PreUpdate(float fDeltaTime);
	void PostUpdate(float fDeltaTime);

	void Update(float fDeltaTime);
	IShaderObject* GetShaderObject(size_t nShaderHash);
private:
	GraphicsSystem* m_pGraphicSystem;
};