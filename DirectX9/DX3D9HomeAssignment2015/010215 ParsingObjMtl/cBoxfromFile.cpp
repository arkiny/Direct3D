#include "stdafx.h"
#include "cBoxfromFile.h"
#include "cObjectParser.h"

cBoxfromFile::cBoxfromFile()
	:
	m_pTexture(NULL),
	m_hp(3),
	m_vPosition(0, 0, 0),
	m_stGridPosition(0, 0, 0),
	m_pObjectParser(NULL)
{
}


cBoxfromFile::~cBoxfromFile()
{
	SAFE_DELETE(m_pObjectParser);
	SAFE_RELEASE(m_pTexture);
}

void cBoxfromFile::init(){
	m_pObjectParser = new cObjectParser("../Resource/obj/box.obj");
	m_pObjectParser->LoadAndParse();
	m_vecVertex = m_pObjectParser->getObjectInfo();
	m_pTexture = m_pObjectParser->getTexture();
	m_pTexture->AddRef();
}

void cBoxfromFile::update(float delta){

}

void cBoxfromFile::render(){
	if (m_hp > 0){
		D3DXMATRIXA16 matWorld, matT;
		D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);


		D3DMATERIAL9 stMtl;
		ZeroMemory(&stMtl, sizeof(D3DMATERIAL9));
		stMtl = m_pObjectParser->getMTL();
		stMtl.Emissive = D3DXCOLOR(0, 0, 0, 1.0f);
		stMtl.Power = 5.0f;
	
		g_pD3DDevice->SetMaterial(&stMtl);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matT);
		g_pD3DDevice->SetTexture(0, m_pTexture);
	//	g_pD3DDevice->SetTexture(0, NULL);

		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			m_vecVertex.size() / 3,
			&m_vecVertex[0],
			sizeof(ST_PNT_VERTEX));

		//reset
		D3DXMatrixIdentity(&matWorld);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	}
}

D3DXVECTOR3& cBoxfromFile::getWorldPosition(){
	return m_vPosition;
}

GRIDPOSITION& cBoxfromFile::getGridPosition(){
	return m_stGridPosition;
}

void cBoxfromFile::setPositionByGrid(GRIDPOSITION& gridpos){
	m_stGridPosition = gridpos;
	m_vPosition = D3DXVECTOR3(gridpos.x * 5.0f - 50.0f, m_vPosition.y, gridpos.z*5.0f - 50.0f);
}

void cBoxfromFile::setPositionByWorldCoord(D3DXVECTOR3& pos){

}