#pragma once
class ShaderRenderTarget;
class RenderTargetManager
{
public:
	RenderTargetManager();
	virtual ~RenderTargetManager();

	bool Initialize();
	bool PostInitialize();

	bool Reset();
	bool PostReset();

	ShaderRenderTarget* GetRenderTarget(size_t renderTargetHashCode);
	bool				AddRenderTarget(size_t renderTargetHashCode, ShaderRenderTarget* renderTarget);
private:

	std::unordered_map<size_t, ShaderRenderTarget*> _renderTargetMap;


};