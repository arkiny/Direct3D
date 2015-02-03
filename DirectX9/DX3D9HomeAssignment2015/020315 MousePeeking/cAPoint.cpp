#include "stdafx.h"
#include "cAPoint.h"
#include "cTransform.h"
#include <sstream>

cAPoint::cAPoint()
	:m_pMesh(NULL),
	m_nPointInfo(99),
	m_p3DFont(NULL)
{
	ZeroMemory(&m_stMtl, sizeof(m_stMtl));
	ZeroMemory(&m_stFMtl, sizeof(m_stFMtl));
}


cAPoint::~cAPoint()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_p3DFont);
}

void cAPoint::Setup(D3DXCOLOR& c, D3DXVECTOR3& pos){
	D3DXCreateSphere(g_pD3DDevice, 0.25f, 10, 10, &m_pMesh, NULL);
	m_pTransform->SetPosition(pos);
	m_stMtl.Ambient = c;
	m_stMtl.Diffuse = c;
	m_stMtl.Specular = c;

	m_stFMtl.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stFMtl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stFMtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
}

void cAPoint::SetPointInfo(int n){ 
	m_nPointInfo = n; 
	HDC hdc = CreateCompatibleDC(0);
	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));

	lf.lfHeight = 25;    // in logical units
	lf.lfWidth = 12;    // in logical units
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfWeight = 500;   // boldness, range 0(light) - 1000(bold)
	lf.lfItalic = false;
	lf.lfUnderline = false;
	lf.lfStrikeOut = false;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfOutPrecision = 0;
	lf.lfClipPrecision = 0;
	lf.lfQuality = 0;
	lf.lfPitchAndFamily = 0;
	strcpy(lf.lfFaceName, "Times New Roman"); // font style

	//
	// Create an ID3DXFont based on 'lf'.
	//
	HFONT hFont;
	HFONT hFontOld;
	hFont = CreateFontIndirect(&lf);
	hFontOld = (HFONT)SelectObject(hdc, hFont);
	std::stringstream s;
	s << m_nPointInfo;
	D3DXCreateText(g_pD3DDevice, hdc, s.str().c_str(), 0.001f, 0.4f, &m_p3DFont, 0, 0);

	SelectObject(hdc, hFontOld);
	DeleteObject(hFont);
	DeleteDC(hdc);
}

void cAPoint::Update(float delta){
	// currently do nothing
}

void cAPoint::Render(){
	D3DXMATRIXA16 matReset;
	D3DXMatrixIdentity(&matReset);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matReset);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, GetTransformMatrix());
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTexture(0, NULL);
	m_pMesh->DrawSubset(0);
	g_pD3DDevice->SetMaterial(&m_stFMtl);
	m_p3DFont->DrawSubset(0);
}