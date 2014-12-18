#include "StdAfx.h"
#include <sstream>
#include "cMainGame.h"
#include "cObjectCircle.h"
#include "cObjectPlayer.h"
#include "cObjectShit.h"
#include "cObjectRectangle.h"

cMainGame::cMainGame(void):
	m_pFont(NULL)
{
	m_oPlayer = new cObjectPlayer;
	m_nDifficulty = 5;
	m_recFontRect = { 0, 0, 0, 0 };
	//v_buffer = NULL;
	//m_cCircle1 = new cObjectCircle(D3DXVECTOR4(400.0f, 400.0f, 0, 1.0f), 100.0f);
	//m_cCircle2 = new cObjectCircle(D3DXVECTOR4(0.0f, 0.0f, 0, 1.0f), 50.0f);
	
	for (int i = 0; i < 6; i++){
		std::wstring src;
		switch (i)
		{
		case 0:
			src = L"../Resource/blue.png";
			break;
		case 1:
			src = L"../Resource/green.png";
			break;
		case 2:
			src = L"../Resource/orange.png";
			break;
		case 3:
			src = L"../Resource/purple.png";
			break;
		case 4:
			src = L"../Resource/topview.png";
			break;
		case 5:
			src = L"../Resource/yellogreen.png";
			break;
		default:
			src = L"../Resource/blue.png";
			break;
		}

		D3DXCreateTextureFromFileEx(g_pD3DDevice
			, src.c_str()
			, D3DX_DEFAULT_NONPOW2
			, D3DX_DEFAULT_NONPOW2
			, 1
			, 0
			, D3DFMT_UNKNOWN
			, D3DPOOL_MANAGED
			, 0x0000001
			, 0x0000001
			, D3DCOLOR_XRGB(255, 255, 255)
			, NULL
			, NULL
			, &m_pArrShitTexture[i]);
	}

	//	m_vecoShit.resize(50, nullptr);
	for (int i = 0; i < 50; i++){
		IObject* pShit = new cObjectShit(m_pArrShitTexture[rand() % 6]);
		m_vecoShit.push_back(pShit);
	}

	//m_vecoShit.push_back(pShit);
	for (int i = 0; i < 5; i++){
		IObject* pLine = new cObjectRectangle(
			D3DXVECTOR4(i *100.0f, 0.0f, 0.0f, 1.0f), { 20.0f, 100.0f });
		m_vecoRoadLine.push_back(pLine);
	}

	for (int i = 0; i < 5; i++){
		IObject* pLine = new cObjectRectangle(
			D3DXVECTOR4(i*100.0f, -400.0f, 0.0f, 1.0f), { 20.0f, 100.0f });
		m_vecoRoadLine.push_back(pLine);
	}

	for (int i = 0; i < 5; i++){
		IObject* pLine = new cObjectRectangle(
			D3DXVECTOR4(i*100.0f, -800.0f, 0.0f, 1.0f), { 20.0f, 100.0f });
		m_vecoRoadLine.push_back(pLine);
	}
}


cMainGame::~cMainGame(void)
{
	//delete m_cCircle1;
	//delete m_cCircle2;
	delete m_oPlayer;
	while (!m_vecoShit.empty()){
		IObject* pShit = m_vecoShit.back();
		m_vecoShit.pop_back();
		delete pShit;
	}

	while (!m_vecoRoadLine.empty()){
		IObject* p = m_vecoRoadLine.back();
		m_vecoRoadLine.pop_back();
		delete p;
	}

	for (int i = 0; i < 6; i++){
		SAFE_RELESE(m_pArrShitTexture[i]);
	}
	//delete m_oShit;
	//SAFE_RELESE(m_pTexture);
	//SAFE_RELESE(v_buffer);
	cDeviceManager* pDevice = cDeviceManager::GetInstance();
	pDevice->Destroy();
}

void cMainGame::Setup()
{
	for (unsigned int i = 0; i < m_vecoShit.size(); i++){
		m_vecoShit[i]->init();
	}
	for (UINT i = 0; i < m_vecoRoadLine.size(); i++){
		m_vecoRoadLine[i]->init();
	}

	D3DCOLOR roadColor = D3DCOLOR_XRGB(30, 30, 30);
	ST_RHW_VERTEX v;
	// left top
	//v.t = D3DXVECTOR2(1, 1);
	v.c = roadColor;
	v.p = D3DXVECTOR4(static_cast<float>(g_wndRect.left), 
		static_cast<float>(g_wndRect.top), 0, 1.0f);
	m_vecVertex.push_back(v);

	// right top
	//v.t = D3DXVECTOR2(1, 1);
	v.c = roadColor;
	v.p = D3DXVECTOR4(
		static_cast<float>(g_wndRect.right), 
		static_cast<float>(g_wndRect.top), 0, 1.0f);
	m_vecVertex.push_back(v);

	// right bottom
	//v.t = D3DXVECTOR2(1, 1);
	v.c = roadColor;
	v.p = D3DXVECTOR4(
		static_cast<float>(g_wndRect.right), 
		static_cast<float>(g_wndRect.bottom), 0, 1.0f);
	m_vecVertex.push_back(v);

	// left top
	//v.t = D3DXVECTOR2(1, 1);
	v.c = roadColor;
	v.p = D3DXVECTOR4(
		static_cast<float>(g_wndRect.left), 
		static_cast<float>(g_wndRect.top), 0, 1.0f);
	m_vecVertex.push_back(v);

	// right bottom
	//v.t = D3DXVECTOR2(1, 1);
	v.c = roadColor;
	v.p = D3DXVECTOR4(
		static_cast<float>(g_wndRect.right), 
		static_cast<float>(g_wndRect.bottom), 0, 1.0f);
	m_vecVertex.push_back(v);

	// left bottom
	//v.t = D3DXVECTOR2(1, 1);
	v.c = roadColor;
	v.p = D3DXVECTOR4(
		static_cast<float>(g_wndRect.left), 
		static_cast<float>(g_wndRect.bottom), 0, 1.0f);
	m_vecVertex.push_back(v);


	//m_cCircle1->init();
	//m_cCircle2->init();
	m_oPlayer->init();

	D3DXCreateFont(g_pD3DDevice,     //D3D Device
		40,               //Font height
		0,                //Font width
		FW_NORMAL,        //Font Weight
		1,                //MipLevels
		false,            //Italic
		DEFAULT_CHARSET,  //CharSet
		OUT_DEFAULT_PRECIS, //OutputPrecision
		ANTIALIASED_QUALITY, //Quality
		DEFAULT_PITCH | FF_DONTCARE,//PitchAndFamily
		L"Arial",          //pFacename,
		&m_pFont);         //ppFont

	SetRect(&m_recFontRect, 0, 0, 400, 200);

	
}


void cMainGame::Update(float delta)
{
	m_faccumTime += delta;
	m_fTotalTime += delta;
	std::wostringstream outs;
	outs.precision(4);
	for (int i = 0; i < m_nDifficulty; i++){
		if (m_oPlayer->isCollided(m_vecoShit[i])){
			outs << L"Your Score is " << m_fTotalTime << "sec!";
			MessageBox(g_hWnd, outs.str().c_str(), L"Game Over", MB_OK);
			PostQuitMessage(NULL);
		}
	}
	m_oPlayer->update(delta);

	if (m_faccumTime >= 2.0f){
		m_nDifficulty++;
		m_faccumTime = 0;
	}

	for (int i = 0; i < m_nDifficulty; i++){
		m_vecoShit[i]->update(delta);
	}
	for (UINT i = 0; i < m_vecoRoadLine.size(); i++){
		m_vecoRoadLine[i]->update(delta);
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
	
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetFVF(ST_RHW_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 6, &m_vecVertex[0], sizeof(ST_RHW_VERTEX));

	// 그림을 그린다.
	for (UINT i = 0; i < m_vecoRoadLine.size(); i++){
		m_vecoRoadLine[i]->render();
	}
	
	for (int i = 0; i < m_nDifficulty; i++){
		m_vecoShit[i]->render();
	}
	m_oPlayer->render();

	std::wstringstream s;
	s.precision(2);
	s << std::fixed << m_fTotalTime << " Sec" ;
	m_pFont->DrawText(NULL,				 //pSprite
					s.str().c_str(),	 //pString
					-1,					//Count
					&m_recFontRect,		//pRect
					DT_LEFT | DT_NOCLIP,//Format,
					0xFFFFFFFF);		//Color

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
