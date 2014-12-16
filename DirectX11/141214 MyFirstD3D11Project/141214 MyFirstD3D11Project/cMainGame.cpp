#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"


cMainGame::cMainGame()
{
}


cMainGame::~cMainGame()
{
	cDeviceManager* pDevice = cDeviceManager::GetInstance();
	SAFE_RELEASE(pVS);
	SAFE_RELEASE(pPS);
	pDevice->Destroy();
}

void cMainGame::init(){
	//////////////////////////////////
	// init pipline
	// load and compile the two shaders
	ID3D10Blob *VS;
	ID3D10Blob* PS;
	D3DX11CompileFromFile(L"shader.shader", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, 0, 0);
	D3DX11CompileFromFile(L"shader.shader", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, 0, 0);

	// encapsulate both shaders into shader objects
	g_pDevice->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVS);
	g_pDevice->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPS);

	g_pDeviceContext->VSSetShader(pVS, 0, 0);
	g_pDeviceContext->PSSetShader(pPS, 0, 0);

	D3D11_INPUT_ELEMENT_DESC ied[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
		D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,
		0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	g_pDevice->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &pLayout);
	g_pDeviceContext->IASetInputLayout(pLayout);
	///////////// end pipeline

	////////////
	ST_VERTEX1 v = { -0.5f, 0.5f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f) };
	m_vecdata.push_back(v);
	v = { 0.0f, 0.5f, 0.0f, D3DXCOLOR(0, 1.0f, 0, 1.0f) };
	m_vecdata.push_back(v);
	v = { 0.0f, -0.5f, 0.0f, D3DXCOLOR(1.0f, 0, 0, 1.0f) };
	m_vecdata.push_back(v);

	//ST_VERTEX1 OurVertices[] =
	//{
	//	{ -0.5f, 0.5f, 0.0f, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f) },
	//	{ 0.5f, 0.5f, 0.0f, D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f) },
	//	{ 0.5f, -0.5f, 0.0f, D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f) }
	//};
	//
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));

	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(ST_VERTEX1) * 3;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	g_pDevice->CreateBuffer(&bd, NULL, &pVBuffer);

	D3D11_MAPPED_SUBRESOURCE ms;
	// map the buffer
	g_pDeviceContext->Map(pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
	memcpy(ms.pData, &m_vecdata[0], sizeof(ST_VERTEX1)*m_vecdata.size());
	g_pDeviceContext->Unmap(pVBuffer, NULL);

	
}

void cMainGame::update(float delta){

}

void cMainGame::render(){
	assert(g_pDeviceContext);
	assert(g_pSwapChain);

	g_pDeviceContext->
		ClearRenderTargetView(g_pRTView, reinterpret_cast<const float*>(&Colors::Blue));
	g_pDeviceContext->
		ClearDepthStencilView(g_pDSView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	
	///
	UINT stride = sizeof(ST_VERTEX1);
	UINT offset = 0;
	g_pDeviceContext->IASetVertexBuffers(0, 1, &pVBuffer, &stride, &offset);
	g_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	g_pDeviceContext->Draw(3, 0);
	///

	HR(g_pSwapChain->Present(0, 0));
}
