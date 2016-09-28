#pragma once
#include "CoreEngineCommon.h"
#include "RenderEngineCommon.h"
#include "IDeferredShadingMethodImpl.h"
#include <d3d11_4.h>
#include <DirectXMath.h>
#include <vector>
class DeviceManager;
class ShaderManager;
class IRenderableObject;
class ShaderRenderTargetDX;
class ShaderRenderTarget;
class DXDevice11_4;

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

	virtual RenderEngine::GRAPHICSAPITYPE GetMiddleWareType() { return RenderEngine::GRAPHICSAPITYPE::DIRECTX11_4; }

	virtual bool SetWorldMatrix(const ORBITMATRIX4x4* worldMatrix);
	virtual bool SetCameraMatrix();
	virtual bool SettingShaderOptions();
	virtual bool SetConstVariables();
	virtual bool SetRenderTarget();
	virtual bool ResetRenderTarget();
	virtual bool SetVertexBuffer(const ORBITMesh* mesh) const;
	virtual bool SetSubsetVBIndicesInfo(const ORBITMeshSubset* subsetData);
	virtual bool SetMaterial(const ORBITMaterial* material);
	virtual bool RenderMesh();
	virtual bool RenderLighting(std::vector<IRenderableObject*>& renderRequestObjects);

private:
	bool SetShader_(ID3D11Device3* deviceDX, ID3DBlob* psShaderBuffer, ID3DBlob* vsShaderBuffer, ID3DBlob* csShaderBuffer);
	virtual bool LoadShader_();

private:

	ShaderManager*					_shaderManager;
	
	DXDevice11_4*					_deviceWrapper;
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

