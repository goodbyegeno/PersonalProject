#pragma once
class GraphicsSystem;
class IShaderObject;

class ShaderManager
{
public :
	ShaderManager(GraphicsSystem* graphicSystem);
	virtual ~ShaderManager();

	bool Initialize();
	bool PostInitialize();
	bool Reset();
	bool PostReset();
	void PreUpdate(float deltaTime);
	void PostUpdate(float deltaTime);

	void Update(float deltaTime);
	IShaderObject* GetShaderObject(size_t shaderHash);
private:
	GraphicsSystem* _graphicSystem;
};