#include "StdAfx.h"
#include "cMainGame.h"
#include "cObjectCircle.h"

cMainGame::cMainGame(void)
	: m_pTexture(NULL)
{
	//v_buffer = NULL;
	m_cCircle1 = new cObjectCircle(D3DXVECTOR4(400.0f, 400.0f, 0, 1.0f), 100.0f);
	m_cCircle2 = new cObjectCircle(D3DXVECTOR4(0.0f, 0.0f, 0, 1.0f), 50.0f);
}


cMainGame::~cMainGame(void)
{
	delete m_cCircle1;
	delete m_cCircle2;
	SAFE_RELEASE(m_pTexture);
	//SAFE_RELEASE(v_buffer);
	cDeviceManager* pDevice = cDeviceManager::GetInstance();
	pDevice->Destroy();
}

void cMainGame::Setup()
{
	/*HRESULT hr = D3DXCreateTextureFromFile(g_pD3DDevice, "../../Resources/Texture/box.jpg", &m_pTexture);
	_ASSERT(hr == S_OK);*/
	//HRESULT hr = D3DXCreateTextureFromFileEx(g_pD3DDevice
	//	, L"../../Resources/Texture/char.png"
	//	, D3DX_DEFAULT
	//	, D3DX_DEFAULT
	//	, 1
	//	, 0
	//	, D3DFMT_UNKNOWN
	//	, D3DPOOL_MANAGED
	//	, 0x0000001
	//	, 0x0000001
	//	, D3DCOLOR_XRGB(215, 226, 210)
	//	, NULL
	//	, NULL
	//	, &m_pTexture);
	//_ASSERT(hr == S_OK);

	/*ST_RHW_VERTEX v2[3];*/
	/*v2[0] = ST_RHW_VERTEX{ D3DXVECTOR4(100, 100, 0, 1.0f), D3DCOLOR_XRGB(0, 0, 255) };
	v2[1] = ST_RHW_VERTEX{ D3DXVECTOR4(400, 100, 0, 1.0f), D3DCOLOR_XRGB(0, 255, 0) };
	v2[2] = ST_RHW_VERTEX{ D3DXVECTOR4(400, 400, 0, 1.0f), D3DCOLOR_XRGB(255, 0, 0) };*/

	//g_pD3DDevice->CreateVertexBuffer(
	//	3 * sizeof(ST_RHW_VERTEX),
	//	0,
	//	ST_RHW_VERTEX::FVF,
	//	D3DPOOL_MANAGED,
	//	&v_buffer,
	//	NULL
	//	);

	//VOID* pVoid;    // a void pointer

	//// lock v_buffer and load the vertices into it
	//v_buffer->Lock(0, 0, (void**)&pVoid, 0);
	//memcpy(pVoid, v2, sizeof(v2));
	//v_buffer->Unlock();

	/*ST_RHW_VERTEX v;
	v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.t = D3DXVECTOR2(0, 0);
	v.p = D3DXVECTOR4(100, 100, 0, 1.0f);
	m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 255, 0);
	v.t = D3DXVECTOR2(1, 0);
	v.p = D3DXVECTOR4(400, 100, 0, 1.0f);
	m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.t = D3DXVECTOR2(1, 1);
	v.p = D3DXVECTOR4(400, 400, 0, 1.0f);
	m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(255, 0, 255);
	v.t = D3DXVECTOR2(0, 0);
	v.p = D3DXVECTOR4(100, 100, 0, 1.0f);
	m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 255, 255);
	v.t = D3DXVECTOR2(1, 1);
	v.p = D3DXVECTOR4(400, 400, 0, 1.0f);
	m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(255, 255, 0);
	v.t = D3DXVECTOR2(0, 1);
	v.p = D3DXVECTOR4(100, 400, 0, 1.0f);
	m_vecVertex.push_back(v);

	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 1);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);*/
	
	m_cCircle1->init();
	m_cCircle2->init();
}


void cMainGame::Update()
{
	if (cControl::GetInstance()->getKeyControlInfo(VK_LBUTTON)){
		float x = cControl::GetInstance()->getClickPosition().x;
		float y = cControl::GetInstance()->getClickPosition().y;
		m_cCircle2->ChangeOrigin(x, y);
	}
	//m_cCircle->update(0.0f);
	if (m_cCircle1->isCollide(m_cCircle2)){
		m_cCircle1->ChangeColor(D3DCOLOR_XRGB(255, 0, 0));
	}
	else {
		m_cCircle1->ChangeColor(D3DCOLOR_XRGB(255, 255, 255));
	}
}

void cMainGame::Render()
{
	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		//D3DCOLOR_XRGB(47, 121, 112),
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f, 0);
	g_pD3DDevice->BeginScene();

	// 그림을 그린다.

	/*g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_RHW_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, &m_vecVertex[0], sizeof(ST_RHW_VERTEX));
	*/
	
	m_cCircle1->render();
	m_cCircle2->render();
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, &v2, sizeof(ST_RHW_VERTEX));
	/*g_pD3DDevice->SetStreamSource(0, v_buffer, 0, sizeof(ST_RHW_VERTEX));
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);*/

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
