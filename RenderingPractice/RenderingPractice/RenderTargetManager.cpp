#include "stdafx.h"
#include "RenderTargetManager.h"
#include "ShaderRenderTarget.h"
RenderTargetManager::RenderTargetManager()
{
}
RenderTargetManager::~RenderTargetManager()
{
	//only this manager Terminate when program close. so don't need to release rendertarget.

	_renderTargetMap.clear();
}
bool RenderTargetManager::Initialize()
{
	_renderTargetMap.clear();
	return true;

}
bool RenderTargetManager::PostInitialize()
{
	
	return true;
}

bool RenderTargetManager::Reset()
{
	for (std::unordered_map<size_t, ShaderRenderTarget*>::iterator itor = _renderTargetMap.begin(); itor != _renderTargetMap.end(); itor++)
	{
		delete itor->second;
	}
	_renderTargetMap.clear();
	return true;
}
bool RenderTargetManager::PostReset()
{
	return true;
}

ShaderRenderTarget* RenderTargetManager::GetRenderTarget(size_t renderTargetHashCode)
{
	std::unordered_map<size_t, ShaderRenderTarget*>::iterator itor = _renderTargetMap.find(renderTargetHashCode);
	if (itor != _renderTargetMap.end())
		return itor->second;

	return nullptr;
}

bool RenderTargetManager::AddRenderTarget(size_t renderTargetHashCode, ShaderRenderTarget* renderTarget)
{
	_renderTargetMap.insert(std::unordered_map<size_t, ShaderRenderTarget*>::value_type(renderTargetHashCode, renderTarget));
	
	return true;

}
