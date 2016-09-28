#pragma once
#include <unordered_map>
#include "RenderEngineCommon.h"
class GraphicsSystem;
class IShaderObject;

class ShaderManager
{

public :
	struct ShaderFileHeader
	{
	public:
		size_t hash;
		RenderEngine::GRAPHICSAPITYPE apiType;
		size_t size;
	};
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
	void LoadShaderObject_();

	GraphicsSystem* _graphicSystem;
	std::unordered_map <size_t, IShaderObject*> _shaderObjectMap;

};