#include "stdafx.h"
#include "ShaderManager.h"

ShaderManager::ShaderManager(GraphicsSystem* graphicSystem)
{
	_shaderObjectMap.clear();
	_shaderObjectMap.reserve(10);
}
ShaderManager::~ShaderManager()
{

}
bool ShaderManager::Initialize()
{

	return true;
}
bool ShaderManager::PostInitialize()
{
	return true;
}
bool ShaderManager::Reset()
{
	return true;
}
bool ShaderManager::PostReset()
{
	return true;
}
void ShaderManager::PreUpdate(float deltaTime)
{

}
void ShaderManager::PostUpdate(float deltaTime)
{

}

void ShaderManager::Update(float deltaTime)
{

}

IShaderObject* ShaderManager::GetShaderObject(size_t shaderHash)
{
	IShaderObject* result = nullptr;

	std::unordered_map<size_t, IShaderObject*>::iterator foundItor = _shaderObjectMap.find(shaderHash);
	if (_shaderObjectMap.end() != foundItor)
	{
		result = foundItor->second;
	}

	return result;
}
