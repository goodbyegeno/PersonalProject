#pragma once
#include "CoreEngineCommon.h"
#include "RenderEngineCommon.h"
#include "IDeferredShadingMethodImpl.h"
#include <d3d11_4.h>
#include <DirectXMath.h>
#include <vector>
class DeviceManager;
class ShaderManager;
class IRenderedObject;
class ShaderRenderTargetDX;
class ShaderRenderTarget;
class IRenderedObject;
class DXDevice;

struct ShaderConstVariables
{
	DirectX::XMMATRIX				_worldMatrix;
	DirectX::XMMATRIX				_viewMatrix;
	DirectX::XMMATRIX				_projMatrix;
	DirectX::XMMATRIX				_viewProjMatrix;
};

class DeferredShadingMethodDX : public IDeferredShadingMethodImpl
{
private:
	class DrawVariables
	{
	public:
		DrawVariables();
		~DrawVariables();

		void SetIndexData(int indexCount, int indexStart, int vertexStart);
		int GetIndexCount() const { return _indexCount; }
		int GetIndexStart() const { return _indexStart; }
		int GetVertexStart() const { return _vertexStart; }

	private:
		int _indexCount;
		int _indexStart;
		int _vertexStart;

		
	};

public:
	DeferredShadingMethodDX();
	virtual ~DeferredShadingMethodDX();

	bool Initialize(DeviceManager* deviceManager, ShaderManager* shaderManager);
	bool Reset(DeviceManager* deviceManager, ShaderManager* shaderManager);

	bool InitRenderTargets(ShaderRenderTarget** renderTargets, int renderTargetNum);

	virtual CoreEngine::GRAPHICSAPITYPE GetMiddleWareType() { return CoreEngine::GRAPHICSAPITYPE::DIRECTX11_2; }

	virtual bool SetCameraMatrix();
	virtual bool SettingShaderOptions();
	virtual bool SetConstVariables();
	virtual bool SetRenderTarget();
	virtual bool ResetRenderTarget();
	virtual bool SetVertexBuffer(ORBITMesh* mesh);
	virtual bool SetSubsetVBIndicesInfo(const ORBITMeshSubset* subsetData);
	virtual bool SetMaterial(const ORBITMaterial* material);
	virtual bool RenderMesh();
	virtual bool RenderLighting(std::vector<IRenderedObject*>& renderRequestObjects);

private:
	bool SetShader_(ShaderManager* shaderManager, ID3D11Device3* deviceDX);
private:

	ShaderManager*					_shaderManager;
	
	DXDevice*						_deviceWrapper;
	ID3D11Device3*					_device;
	ID3D11DeviceContext3*			_deviceContext;
	
	ShaderRenderTargetDX*			_renderTargets		[static_cast<int>(INDEXEDDEFERREDSHADINGRT::MAX)];
	
	ID3D11Texture2D*				_renderTargetTex	[static_cast<int>(INDEXEDDEFERREDSHADINGRT::MAX)];
	ID3D11ShaderResourceView*		_shaderRenderView	[static_cast<int>(INDEXEDDEFERREDSHADINGRT::MAX)];
	ID3D11RenderTargetView*			_renderingTargetView[static_cast<int>(INDEXEDDEFERREDSHADINGRT::MAX)];
	ID3D11DepthStencilView*			_depthStencilView;
	ID3D11DepthStencilState*		_depthStencilState;

	int								_renderTargetCount;

	ID3D11InputLayout*				_inputLayout;
	ID3D11VertexShader*				_vertexShader;
	ID3D11PixelShader*				_pixelShader;
	ID3D11ComputeShader*			_computeShader;
									
	size_t							_vertexShaderHash;
	size_t							_pixelShaderHash;
	size_t							_computeShaderHash;
	
	ShaderConstVariables			_vsConstVariables;
	ShaderConstVariables			_psConstVariables;
	ID3D11Buffer*					_vsConstVariableBuffer;
	ID3D11Buffer*					_psConstVariableBuffer;

	D3D11_VIEWPORT*					_viewPort;
	ID3D11BlendState1*				_blendState;
	DrawVariables					_drawVariables;

	int								_srDiffuseSlot;
	int								_srSpecularSlot;
	int								_srNormalSlot;
	
};

