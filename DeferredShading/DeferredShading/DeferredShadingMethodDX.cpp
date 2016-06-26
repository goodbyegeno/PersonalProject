#include "DeferredShadingMethodDX.h"
#include "ShaderManager.h"
#include "IShaderObejct.h"
#include "DeviceManager.h"
#include "IGraphicsDevice.h"
DeferredShadingMethodDX::DeferredShadingMethodDX()
{
	m_pDevice				= nullptr;
	m_pDeviceContext		= nullptr;

	m_pVertexShader			= nullptr;
	m_pPixelShader			= nullptr;
	m_pComputeShader		= nullptr;
	m_nVertexShaderHash		= 0;
	m_nPixelShaderHash		= 0;
	m_nComputeShaderHash	= 0;
}
DeferredShadingMethodDX::~DeferredShadingMethodDX()
{

}
bool DeferredShadingMethodDX::Initialize(DeviceManager* pDeviceManager, ShaderManager* pShaderManager)
{
	m_pShaderManager = pShaderManager;
	IGraphcisDevice* pDevice = pDeviceManager->GetDevice();
	if (pDevice == nullptr || pDevice->GetMiddlewareType() != RenderEngine::MiddlewareType::DirectX)
		return false;

	m_pDevice = static_cast<ID3D11Device*>(pDevice->GetBuffer());
	if (m_pDevice == nullptr)
	{
		return false;
	}
	m_pDeviceContext		= nullptr;

	m_pVertexShader			= nullptr;
	m_pPixelShader			= nullptr;
	m_pComputeShader		= nullptr;

	m_nVertexShaderHash		= 0;
	m_nPixelShaderHash		= 0;
	m_nComputeShaderHash	= 0;

	if (SetShader_(pShaderManager, m_pDevice) == false)
		return false;

	
}
bool DeferredShadingMethodDX::Reset(DeviceManager* pDeviceManager, ShaderManager* pShaderManager)
{
	m_pShaderManager = pShaderManager;
	IGraphcisDevice* pDevice = pDeviceManager->GetDevice();
	if (pDevice == nullptr || pDevice->GetMiddlewareType() != RenderEngine::MiddlewareType::DirectX)
		return false;

	m_pDevice = static_cast<ID3D11Device*>(pDevice->GetBuffer());

	m_pVertexShader			= nullptr;
	m_pPixelShader			= nullptr;
	m_pComputeShader		= nullptr;

	m_nVertexShaderHash		= 0;
	m_nPixelShaderHash		= 0;
	m_nComputeShaderHash	= 0;

	SetShader_(pShaderManager, m_pDevice);
}
bool DeferredShadingMethodDX::SetShader_(ShaderManager* pShaderManager, ID3D11Device* pDeviceDX)
{
	IShaderObject* pTempShaderObject = nullptr;
	pTempShaderObject = pShaderManager->GetShaderObject(m_nVertexShaderHash);
	if (pTempShaderObject == nullptr)
		return false;
	if (pTempShaderObject->GetMiddlewareType() != RenderEngine::MiddlewareType::DirectX)
		return false;

	m_pVertexShader = static_cast<ID3D11VertexShader*>(pTempShaderObject->GetShader());
	ID3DBlob* pVertexShaderBuffer = static_cast<ID3DBlob*>(pTempShaderObject->GetBuffer());
	HRESULT Result;
	D3D11_INPUT_ELEMENT_DESC PolygonLayout[4];
	UINT nNumElements = sizeof(PolygonLayout) / sizeof(PolygonLayout[0]);
	PolygonLayout[0].AlignedByteOffset;
	PolygonLayout[0].Format;
	PolygonLayout[0].InputSlot;
	PolygonLayout[0].InputSlotClass;
	PolygonLayout[0].InstanceDataStepRate;
	PolygonLayout[0].SemanticIndex;
	PolygonLayout[0].SemanticName =;

	Result = pDeviceDX->CreateInputLayout(PolygonLayout, nNumElements, pVertexShaderBuffer->GetBufferPointer(),
		pVertexShaderBuffer->GetBufferSize(), &m_pInputLayout);

	if (FAILED(Result))
	{
		return false;
	}
	pTempShaderObject = nullptr;

	pTempShaderObject = pShaderManager->GetShaderObject(m_nPixelShaderHash);
	if (pTempShaderObject == nullptr)
		return false;
	if (pTempShaderObject->GetMiddlewareType() != RenderEngine::MiddlewareType::DirectX)
		return false;

	m_pPixelShader = static_cast<ID3D11PixelShader*>(pTempShaderObject->GetShader());
	pTempShaderObject = nullptr;

	pTempShaderObject = pShaderManager->GetShaderObject(m_nComputeShaderHash);
	if (pTempShaderObject == nullptr)
		return false;
	if (pTempShaderObject->GetMiddlewareType() != RenderEngine::MiddlewareType::DirectX)
		return false;

	m_pComputeShader = static_cast<ID3D11ComputeShader*>(pTempShaderObject->GetShader());
	pTempShaderObject = nullptr;
}
bool DeferredShadingMethodDX::SetMatrix()
{
	return false;
}
bool DeferredShadingMethodDX::SetShader()
{
	return false;
}
bool DeferredShadingMethodDX::SetConstVariables()
{
	return false;
}
bool DeferredShadingMethodDX::SetRenderTarget()
{
	return false;
}
bool DeferredShadingMethodDX::RenderMesh()
{
	return false;
}
bool DeferredShadingMethodDX::RenderLighting()
{
	return false;
}