#include "stdafx.h"
#include "cCard.h"
#include "cObjLoader.h"
#include "cMtlTex.h"
#include "cTextureManager.h"

cCard::cCard():
m_vPosition(0,0,0),
m_pDrawMesh(NULL),
m_pMtlTex(NULL),
m_bStepped(false),
m_bMatched(false),
m_nCardType(0)
{
}

cCard::~cCard()
{
	SAFE_RELEASE(m_pMtlTex);
	SAFE_RELEASE(m_pDrawMesh);
	SAFE_RELEASE(m_VertexBuffer);
}

void cCard::Setup(int nType){
	ST_PNT_VERTEX v;

	float left = -0.5f;
	float top = 0.5f;
	float right = 0.5f;
	float bottom = -0.5f;
	//float frontdepth = 0.5f;
	//float backdepth = -0.5f;
	v.t = D3DXVECTOR2(0.f, 0.f);
	v.p = D3DXVECTOR3(left, top, 0);	
	m_vecPlane.push_back(v);
	v.p = D3DXVECTOR3(right, top, 0);
	m_vecPlane.push_back(v);
	v.p = D3DXVECTOR3(left, bottom, 0);
	m_vecPlane.push_back(v);
	v.p = D3DXVECTOR3(left, bottom, 0);
	m_vecPlane.push_back(v);
	v.p = D3DXVECTOR3(right, top, 0);
	m_vecPlane.push_back(v);
	v.p = D3DXVECTOR3(right, bottom, 0);
	m_vecPlane.push_back(v);

	m_vecPlane[0].t = D3DXVECTOR2(0.5, 0.0f);
	m_vecPlane[1].t = D3DXVECTOR2(1.0f, 0.0f);
	m_vecPlane[2].t = D3DXVECTOR2(0.5f, 1.0f);
	m_vecPlane[3].t = D3DXVECTOR2(0.5f, 1.0f);
	m_vecPlane[4].t = D3DXVECTOR2(1.0f, 0.0f);
	m_vecPlane[5].t = D3DXVECTOR2(1.0f, 1.0f);

	D3DXVECTOR3 vector1 = m_vecPlane[0].p - m_vecPlane[1].p;
	D3DXVECTOR3 vector2 = m_vecPlane[0].p - m_vecPlane[2].p;
	D3DXVECTOR3 vectorN;
	D3DXVec3Cross(&vectorN, &vector1, &vector2);
	D3DXVec3Normalize(&vectorN, &vectorN);
	m_vecPlane[0].n = vectorN;
	m_vecPlane[3].n = vectorN;

	vector1 = m_vecPlane[1].p - m_vecPlane[0].p;
	vector2 = m_vecPlane[1].p - m_vecPlane[2].p;
	D3DXVec3Cross(&vectorN, &vector1, &vector2);
	D3DXVec3Normalize(&vectorN, &vectorN);
	m_vecPlane[1].n = vectorN;
	m_vecPlane[4].n = vectorN;
	vector1 = m_vecPlane[2].p - m_vecPlane[0].p;
	vector2 = m_vecPlane[2].p - m_vecPlane[1].p;
	D3DXVec3Cross(&vectorN, &vector1, &vector2);
	D3DXVec3Normalize(&vectorN, &vectorN);
	m_vecPlane[2].n = vectorN;
	m_vecPlane[5].n = vectorN;

	D3DXMATRIXA16 matR, matT, matF;
	D3DXMatrixRotationX(&matR, D3DXToRadian(90.0f));
	D3DXMatrixTranslation(&matT, 0, 0.01f, 0);
	matF = matR * matT;
	for (int i = 0; i < (int)m_vecPlane.size(); i++){
		D3DXVec3TransformCoord(&m_vecPlane[i].p, &m_vecPlane[i].p, &matF);
		D3DXVec3TransformNormal(&m_vecPlane[i].n, &m_vecPlane[i].n, &matF);
	}

	D3DXMatrixRotationX(&matR, D3DXToRadian(180.0f));
	D3DXMatrixTranslation(&matT, 0, -0.01f, 0);
	matF = matR * matT;
	v.t = D3DXVECTOR2(0, 0);
	size_t size = m_vecPlane.size();
	
	for (size_t i = 0; i < size; i++){
		D3DXVec3TransformCoord(&v.p, &m_vecPlane[i].p, &matF);
		D3DXVec3TransformNormal(&v.n, &m_vecPlane[i].n, &matF);
		m_vecPlane.push_back(v);
	}

	m_vecPlane[6].t = D3DXVECTOR2(0.0f, 1.0f);
	m_vecPlane[7].t = D3DXVECTOR2(0.5f, 1.0f);
	m_vecPlane[8].t = D3DXVECTOR2(0.0f, 0.0f);
	m_vecPlane[9].t = D3DXVECTOR2(0.0f, 0.0f);
	m_vecPlane[10].t = D3DXVECTOR2(0.5f, 1.0f);
	m_vecPlane[11].t = D3DXVECTOR2(0.5f, 0.0f);

	g_pD3DDevice->CreateVertexBuffer(
		m_vecPlane.size() * sizeof(ST_PNT_VERTEX),
		D3DUSAGE_WRITEONLY,
		ST_PNT_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_VertexBuffer,
		0
		);

	ST_PNT_VERTEX* buffy;

	m_VertexBuffer->Lock(0, 0, (void**)&buffy, 0);
	for (size_t i = 0; i < m_vecPlane.size(); i++){
		buffy[i] = m_vecPlane[i];
	}
	m_VertexBuffer->Unlock();
	buffy = NULL;
	
	D3DXCreateBox(g_pD3DDevice, 1.0f, 0.2f, 1.0f, &m_pDrawMesh, NULL);
	
	m_pMtlTex = new cMtlTex;
	
	m_pMtlTex->stMtl.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_pMtlTex->stMtl.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_pMtlTex->stMtl.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_nCardType = nType;
	if (m_nCardType == 0){
		m_pMtlTex->pTex = g_pTextureManager->GetTexture("../Resource/Texture/1.jpg");
	}
	else if (m_nCardType == 1){
		m_pMtlTex->pTex = g_pTextureManager->GetTexture("../Resource/Texture/2.jpg");
	}
	else if (m_nCardType == 2){
		m_pMtlTex->pTex = g_pTextureManager->GetTexture("../Resource/Texture/3.jpg");
	}
	else if (m_nCardType == 3){
		m_pMtlTex->pTex = g_pTextureManager->GetTexture("../Resource/Texture/4.jpg");
	}
	m_pTransform->SetZAxisAngle(D3DXToRadian(-180.0f));
}

void cCard::Update(float delta){
	if (m_fAccum <= 2.0f){
		m_fAccum += delta;
		m_pTransform->SetZAxisAngle(D3DXToRadian(-180.0f));
	}
	else{
		if (m_bStepped){
			if (m_pTransform->GetZAxisAngle() > D3DXToRadian(-180.0f)){
				m_pTransform->SetZAxisAngle(m_pTransform->GetZAxisAngle() - 4.0f * delta);
			}
			else {
				m_pTransform->SetZAxisAngle(D3DXToRadian(-180.0f));
			}
		}
		else {
			if (m_bMatched == false){
				if (m_pTransform->GetZAxisAngle() < D3DXToRadian(0.0f)){
					m_pTransform->SetZAxisAngle(m_pTransform->GetZAxisAngle() + 4.0f * delta);
				}
				else {
					m_pTransform->SetZAxisAngle(D3DXToRadian(0.0f));
				}
			}
		}
	}
}

void cCard::Render(){
	g_pD3DDevice->SetTransform(D3DTS_WORLD, m_pTransform->GetTransformMatrix());
	g_pD3DDevice->SetMaterial(&m_pMtlTex->stMtl);
	g_pD3DDevice->SetTexture(0, m_pMtlTex->pTex);
	g_pD3DDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(ST_PNT_VERTEX));
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST,
		0,
		m_vecPlane.size() / 3);
}