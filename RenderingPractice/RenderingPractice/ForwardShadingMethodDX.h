#pragma once
#include "IForwardShadingMethodImpl.h"
#include "CoreEngineCommon.h"
#include "RenderEngineCommon.h"
#include "IDeferredShadingMethodImpl.h"
#include <d3d11_4.h>
#include <DirectXMath.h>
#include <vector>

class DeviceManager;
class ShaderManager;
class RenderTargetManager;
class IRenderableObject;
class ShaderRenderTargetDX;
class ShaderRenderTarget;
class DXDevice11_4;
class ORBITVertex;

class ForwardShadingMethodDX : public IForwardShadingMethodImpl
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
	enum class FORWARDSHADINGRT
	{
		DIFFUSE,
		MAX
	};


	struct ShaderConstVariables
	{
		DirectX::XMMATRIX				_worldMatrix;
		DirectX::XMMATRIX				_viewMatrix;
		DirectX::XMMATRIX				_projMatrix;
		DirectX::XMMATRIX				_viewProjMatrix;
	};

	struct ShaderVertexInput
	{
		DirectX::XMFLOAT3				_position;
		DirectX::XMFLOAT2				_texcoord;
		DirectX::XMFLOAT3				_normal;

	};
	ForwardShadingMethodDX();
	virtual ~ForwardShadingMethodDX();

	virtual bool Initialize(DeviceManager* deviceManager, ShaderManager* shaderManager, RenderTargetManager* renderTargetManager);
	virtual bool Reset(DeviceManager* deviceManager, ShaderManager* shaderManager);
		    
	virtual bool SetWorldMatrix(const ORBITMATRIX4x4* worldMatrix);
	virtual bool SetCameraMatrix();
	virtual bool SettingShaderOptions();
	virtual bool SetConstVariables();
	virtual bool SetRenderTarget();
	virtual bool SetVertexBuffer(const ORBITMesh* mesh) const;
	virtual bool SetSubsetVBIndicesInfo(const ORBITMeshSubset* subsetData);
	virtual bool SetMaterial(const ORBITMaterial* material);
	virtual bool RenderMesh();
	virtual bool ResetRenderTarget();
	virtual bool CreateVertexBuffer(int vertexCount, int indexCount, ORBITVertex* verticesOrigin, UINT* indicesOrigin, ORBITMesh* outMeshData);

	bool InitRenderTargets(RenderTargetManager* renderTargetManager);

private:
	bool							LoadShader_();
	bool							SetShader_(ID3D11Device3* deviceDX, ID3DBlob* psShaderBuffer, ID3DBlob* vsShaderBuffer);

	ShaderManager*					_shaderManager;
	RenderTargetManager*			_renderTargetManager;

	DXDevice11_4*					_deviceWrapper;
	ID3D11Device3*					_device;
	ID3D11DeviceContext3*			_deviceContext;

	ShaderRenderTargetDX*			_renderTargets[static_cast<int>(FORWARDSHADINGRT::MAX)];

	ID3D11Texture2D*				_renderTargetTex[static_cast<int>(FORWARDSHADINGRT::MAX)];
	ID3D11ShaderResourceView*		_shaderResourceView[static_cast<int>(FORWARDSHADINGRT::MAX)];
	ID3D11RenderTargetView*			_renderingTargetView[static_cast<int>(FORWARDSHADINGRT::MAX)];
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

	size_t							_renderTargetHash;

};
