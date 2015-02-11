#include "stdafx.h"
#include <sstream>
#include "cSkinnedMeshObject.h"
#include "cSkinnedMesh.h"
#include "cSphere.h"

cSkinnedMeshObject::cSkinnedMeshObject()
	:m_pSkinnedMesh(NULL),
	m_pSphere(NULL),
	m_pFontMesh(NULL)
{
	ZeroMemory(&m_stFontMtl, sizeof(D3DMATERIAL9));
}


cSkinnedMeshObject::~cSkinnedMeshObject()
{
	SAFE_DELETE(m_pSkinnedMesh);
	SAFE_RELEASE(m_pSphere);
	SAFE_RELEASE(m_pFontMesh);
	
}

void cSkinnedMeshObject::Setup(){
	m_stFontMtl.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_stFontMtl.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_stFontMtl.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	
	m_pSkinnedMesh = new cSkinnedMesh;
	m_pSkinnedMesh->Setup("../Resource/Zealot/", "zealot.X");
	m_pSkinnedMesh->SetAnimationLoop(0, false);
	m_pSkinnedMesh->SetAnimationLoop(1, false);
	m_pSkinnedMesh->SetAnimationLoop(2, false);
	m_pSkinnedMesh->SetAnimationLoop(3, true);
	m_pSkinnedMesh->SetAnimationLoop(4, true);
	m_pSkinnedMesh->SetAnimationIndex(4);
	

	m_pSphere = new cSphere;
	m_pSphere->Setup();
	D3DXVECTOR3 pos = m_pTransform->GetPosition();
	pos.y = pos.y + 0.5f;
	m_pSphere->SetPosition(pos);


	HDC hdc = CreateCompatibleDC(0);
	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));

	lf.lfHeight = 15;    // in logical units
	lf.lfWidth = 10;    // in logical units
	lf.lfEscapement = 0;
	lf.lfOrientation = 0;
	lf.lfWeight = 0;   // boldness, range 0(light) - 1000(bold)
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

	std::string f = "Zealot";
	D3DXCreateText(g_pD3DDevice, hdc, f.c_str(), 0.001f, 0.01f, &m_pFontMesh, 0, 0);

	SelectObject(hdc, hFontOld);
	DeleteObject(hFont);
	DeleteDC(hdc);

	//m_bIsLoaded = true;
	//if (ST_PN_VERTEX::FVF == m_pFontMesh->GetFVF())
}

void cSkinnedMeshObject::Update(float delta){
	if (m_pSkinnedMesh){
		m_pSkinnedMesh->Update(delta);
		cGameObject::Update(delta);
		/*D3DXMATRIXA16 worldMat;
		D3DXMatrixRotationY(&worldMat, m_fAngle);
		worldMat._41 = GetTransformMatrix()->_41;
		worldMat._42 = GetTransformMatrix()->_42;
		worldMat._43 = GetTransformMatrix()->_43;*/
		D3DXVECTOR3 pos = m_pTransform->GetPosition();
		pos.y = pos.y + 0.5f;
		m_pSphere->SetPosition(pos);
	}
	
}

void cSkinnedMeshObject::Render(){
	if (m_pSkinnedMesh){
		m_pSkinnedMesh->Render(GetTransformMatrix());
			

		D3DXMATRIXA16 w = *GetTransformMatrix();


		D3DXMATRIXA16 lf;
		D3DXMatrixTranslation(&lf, -1.0f, 1.5f, 0.0f);
	
		//w = lf * w;

		D3DXMATRIXA16 v;
		
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &v);
		D3DXMatrixInverse(&v, NULL, &v);

		v._41 = w._41;
		v._42 = w._42;
		v._43 = w._43;

		v = lf * v;

		g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, false);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &v);
		g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
		g_pD3DDevice->SetTexture(0, NULL);
		g_pD3DDevice->SetMaterial(&m_stFontMtl);
		m_pFontMesh->DrawSubset(0);
	}

	//if (m_pSphere){
	//	m_pSphere->Render();
	//}
}
void cSkinnedMeshObject::SetAnimationIndex(DWORD dwIndex){
	if (m_pSkinnedMesh){
		m_pSkinnedMesh->SetAnimationIndex(dwIndex);
	}
}

void cSkinnedMeshObject::SetSelcted(bool in){
	if (m_pSphere){
		m_pSphere->SetSelcted(in);
	}
}