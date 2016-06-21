#include "DeferredShadingMethodDX.h"
#include "ShaderManager.h"
#include "IShaderObejct.h"
#include "DeviceManager.h"
#include "IGraphicsDevice.h"
DeferredShadingMethodDX::DeferredShadingMethodDX()
{
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
	IGraphcisDevice* pDevice = pDeviceManager->GetDevice();
	if (pDevice == nullptr || pDevice->GetMiddlewareType() != RenderEngine::MiddlewareType::DirectX)
		return false;

	ID3D11Device* pDeviceDX = static_cast<ID3D11Device*>(pDevice->GetBuffer());
	if (pDeviceDX == nullptr)
	{
		return false;
	}
	m_pVertexShader			= nullptr;
	m_pPixelShader			= nullptr;
	m_pComputeShader		= nullptr;

	m_nVertexShaderHash		= 0;
	m_nPixelShaderHash		= 0;
	m_nComputeShaderHash	= 0;

	if (SetShader_(pShaderManager, pDeviceDX) == false)
		return false;

	
}
bool DeferredShadingMethodDX::Reset(DeviceManager* pDeviceManager, ShaderManager* pShaderManager)
{
	m_pVertexShader			= nullptr;
	m_pPixelShader			= nullptr;
	m_pComputeShader		= nullptr;

	m_nVertexShaderHash		= 0;
	m_nPixelShaderHash		= 0;
	m_nComputeShaderHash	= 0;

	SetShader_(pShaderManager);
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
void DeferredShadingMethodDX::SetConstVariables()
{

}
void DeferredShadingMethodDX::SetRenderTarget()
{

}