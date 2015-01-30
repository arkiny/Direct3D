#include "stdafx.h"
#include "cBox.h"
#include "cTile.h"
#include <sstream>

cBox::cBox()
	:m_vPosition(0, 2.5f, 0),
	m_stGridPosition(0, 0, 0),
	m_p3DFont(NULL),
	m_pF(NULL),
	m_pG(NULL),
	m_pH(NULL)
{
	ZeroMemory(&m_stFMtl, sizeof(m_stFMtl));
}


cBox::~cBox()
{
	SAFE_RELEASE(m_p3DFont);
	SAFE_RELEASE(m_pF);
	SAFE_RELEASE(m_pG);
	SAFE_RELEASE(m_pH);
}

void cBox::init(){
	m_stFMtl.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	m_stFMtl.Diffuse = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);
	m_stFMtl.Specular = D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f);

	// rectangle hard corded version
	ST_PC_VERTEX v;

	float left = -0.5f;
	float top = 0.5f;
	float right = 0.5f;
	float bottom = -0.5f;
	float frontdepth = 0.5f;
	float backdepth = -0.5f;

	//front
	std::vector<ST_PC_VERTEX> plane;
	v.c = D3DCOLOR_XRGB(255, 255, 255);
	v.p = D3DXVECTOR3(left, top, 0);
	plane.push_back(v);
	v.p = D3DXVECTOR3(right, top, 0);
	plane.push_back(v);
	v.p = D3DXVECTOR3(left, bottom, 0);
	plane.push_back(v);
	v.p = D3DXVECTOR3(left, bottom, 0);
	plane.push_back(v);
	v.p = D3DXVECTOR3(right, top, 0);
	plane.push_back(v);
	v.p = D3DXVECTOR3(right, bottom, 0);
	plane.push_back(v);

	//D3DXMATRIXA16 matTrans;
	D3DXMATRIXA16 matScale, matRotate, matTrans, matFinal;
	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		D3DXMatrixRotationY(&matRotate, D3DXToRadian(180.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		D3DXVec3TransformCoord(&v.p, &v.p, &matRotate);
		v.p.z = v.p.z + frontdepth;
		v.c = D3DCOLOR_XRGB(255, 0, 0);
		m_vecVertex.push_back(v);
	}

	// right
	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		D3DXMatrixRotationY(&matRotate, D3DXToRadian(270.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		D3DXVec3TransformCoord(&v.p, &v.p, &matRotate);
		v.p.x = v.p.x + right;
		v.c = D3DCOLOR_XRGB(0, 255, 0);
		m_vecVertex.push_back(v);
	}

	//back
	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		//D3DXMatrixRotationY(&matRotate, D3DXToRadian(0.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		//D3DXVec3TransformCoord(&v.p, &v.p, &matRotate);
		v.p.z = v.p.z + backdepth;
		v.c = D3DCOLOR_XRGB(0, 0, 255);
		m_vecVertex.push_back(v);
	}
	//left
	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		D3DXMatrixRotationY(&matRotate, D3DXToRadian(90.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		D3DXVec3TransformCoord(&v.p, &v.p, &matRotate);
		v.p.x = v.p.x + left;
		v.c = D3DCOLOR_XRGB(255, 255, 0);
		m_vecVertex.push_back(v);
	}

	//top
	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		D3DXMatrixRotationX(&matRotate, D3DXToRadian(90.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		D3DXVec3TransformCoord(&v.p, &v.p, &matRotate);
		v.p.y = v.p.y + top;
		v.c = D3DCOLOR_XRGB(255, 0, 255);
		m_vecVertex.push_back(v);
	}

	// bottom
	// lefttop righttop leftbottom leftbottom righttop rightbottom
	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		D3DXMatrixRotationX(&matRotate, D3DXToRadian(270.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		D3DXVec3TransformCoord(&v.p, &v.p, &matRotate);
		v.p.y = v.p.y + bottom;
		v.c = D3DCOLOR_XRGB(0, 255, 255);
		m_vecVertex.push_back(v);
	}

	for (UINT i = 0; i < m_vecVertex.size(); i++){
		D3DXMatrixScaling(&matScale, m_vSize, m_vSize, m_vSize);
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &matScale);
	}


	
}

void cBox::setTile(cTile* pTile){ 
	m_pTile = pTile;
	cTile::eTILETYPE type = m_pTile->GetType();
	std::stringstream s;
	switch (type)
	{
	case cTile::TILE_EMPTY:
		for (size_t i = 0; i < m_vecVertex.size(); i++){
			m_vecVertex[i].c = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		s << "e";
		break;
	case cTile::TILE_BLOCK:
		for (size_t i = 0; i < m_vecVertex.size(); i++){
			m_vecVertex[i].c = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
		}
		s << "b";
		break;
	case cTile::TILE_START:
		for (size_t i = 0; i < m_vecVertex.size(); i++){
			m_vecVertex[i].c = D3DXCOLOR(0.4f, 1.0f, 0.4f, 1.0f);
		}
		s << "S";
		break;
	case cTile::TILE_DEST:
		for (size_t i = 0; i < m_vecVertex.size(); i++){
			m_vecVertex[i].c = D3DXCOLOR(0.4f, 1.0f, 0.4f, 1.0f);
		}
		s << "D";
		break;
	case cTile::TILE_OPENED:
		for (size_t i = 0; i < m_vecVertex.size(); i++){
			m_vecVertex[i].c = D3DXCOLOR(0.4f, 0.4f, 1.0f, 1.0f);
		}
		s << "O";
		break;
	case cTile::TILE_CLOSED:
		for (size_t i = 0; i < m_vecVertex.size(); i++){
			m_vecVertex[i].c = D3DXCOLOR(1.0f, 0.4f, 0.4f, 1.0f);
		}
		s << "C";
		break;
	case cTile::TILE_PATH:
		for (size_t i = 0; i < m_vecVertex.size(); i++){
			m_vecVertex[i].c = D3DXCOLOR(0.4f, 1.0f, 0.4f, 1.0f);
		}
		s << "P";
		break;
	default:
		break;
	}

	HDC hdc = CreateCompatibleDC(0);
	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));

	lf.lfHeight = 40;    // in logical units
	lf.lfWidth = 20;    // in logical units
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
	ST_FGHINFO info = m_pTile->GetFGH();


	/*s.precision(2);
	GRIDPOSITION playercord = m_pPlayer->getGridCoord();
	s << std::fixed << "x : " << playercord.x << std::endl
		<< "y : " << playercord.y << std::endl
		<< "z : " << playercord.z << std::endl
		<< "TimeLeft : " << m_fTimeLeft << std::endl
		<< "Score : " << m_nScore << std::endl;*/

	
	std::stringstream f;
	f.precision(2);
	f  << std::fixed << info.m_fF;
	std::stringstream g;
	g.precision(2);
	g << std::fixed << info.m_fG;
	std::stringstream h;
	h.precision(2);
	h << std::fixed << info.m_fH;

	D3DXCreateText(g_pD3DDevice, hdc, s.str().c_str(), 0.001f, 0.4f, &m_p3DFont, 0, 0);

	D3DXCreateText(g_pD3DDevice, hdc, g.str().c_str(), 0.001f, 0.4f, &m_pG, 0, 0);
	D3DXCreateText(g_pD3DDevice, hdc, h.str().c_str(), 0.001f, 0.4f, &m_pH, 0, 0);
	D3DXCreateText(g_pD3DDevice, hdc, f.str().c_str(), 0.001f, 0.4f, &m_pF, 0, 0);

	SelectObject(hdc, hFontOld);
	DeleteObject(hFont);
	DeleteDC(hdc);
	//if (m_pTile->GetType())

	ST_PC_VERTEX v;
	v.p = D3DXVECTOR3(0, 0, 0);
	v.c = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	m_vecLineVertex.push_back(v);

	v.p.x = (m_pTile->GetParentPosition().x - m_pTile->GetPosition().x);
	v.p.y = 0.0f;
	v.p.z = -(m_pTile->GetParentPosition().y - m_pTile->GetPosition().y);
	m_vecLineVertex.push_back(v);
}

void cBox::update(float delta){

}

void cBox::render(){
	if (m_hp > 0){
		D3DXMATRIXA16 matWorld, matS, matR, matT;
		D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y - 2.0f, m_vPosition.z);
		D3DXMatrixScaling(&matS, 1.0f, 0.2f, 1.0f);
		matWorld = matS*matT;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			m_vecVertex.size() / 3,
			&m_vecVertex[0],
			sizeof(ST_PC_VERTEX));

		D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
		//D3DXMatrixRotationZ(&matR, D3DXToRadian(-180.0f));
		matWorld = matT;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
			m_vecLineVertex.size() / 2,
			&m_vecLineVertex[0],
			sizeof(ST_PC_VERTEX));

		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

		D3DXMatrixIdentity(&matWorld);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		D3DXMatrixScaling(&matS, 2.0f, 2.0f, 2.0f);
		D3DXMatrixRotationX(&matR, D3DXToRadian(90.0f));
		D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y - 1.5f, m_vPosition.z);
		matWorld = matS * matR * matT;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetMaterial(&m_stFMtl);
		m_p3DFont->DrawSubset(0);

		D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
		D3DXMatrixRotationX(&matR, D3DXToRadian(90.0f));
		D3DXMatrixTranslation(&matT, m_vPosition.x - 2.0f, m_vPosition.y - 1.5f, m_vPosition.z - 2.0f);
		matWorld = matS * matR * matT;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		m_pG->DrawSubset(0);

		D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
		D3DXMatrixRotationX(&matR, D3DXToRadian(90.0f));
		D3DXMatrixTranslation(&matT, m_vPosition.x + 1.0f, m_vPosition.y - 1.5f, m_vPosition.z - 2.0f);
		matWorld = matS * matR * matT;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		m_pH->DrawSubset(0);

		D3DXMatrixScaling(&matS, 1.0f, 1.0f, 1.0f);
		D3DXMatrixRotationX(&matR, D3DXToRadian(90.0f));
		D3DXMatrixTranslation(&matT, m_vPosition.x - 2.0f, m_vPosition.y - 1.5f, m_vPosition.z + 1.0f);
		matWorld = matS * matR * matT;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		m_pF->DrawSubset(0);
		
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		
		D3DXMatrixIdentity(&matWorld);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	}
}

bool cBox::collidewith(gIObject* obj){
	//@todo
	return true;
}

// return world space coord
D3DXVECTOR3& cBox::getWorldPosition(){
	//@todo
	return m_vPosition;
}
// return grid space position
GRIDPOSITION& cBox::getGridPosition(){
	//@todo
	return m_stGridPosition;
}

// set position using grid system
void cBox::setPositionByGrid(GRIDPOSITION& gridpos){
	m_stGridPosition = gridpos;
	m_vPosition = D3DXVECTOR3(gridpos.x * 5.0f - 50.0f, m_vPosition.y, gridpos.z*5.0f - 50.0f);
}

// set position using worldCoordSystem
void cBox::setPositionByWorldCoord(D3DXVECTOR3& pos){

}

bool cBox::collidewithPoint(D3DXVECTOR3& pos){
	float half = m_vSize / 2.0f;
	if (pos.x > m_vPosition.x - half && pos.x < m_vPosition.x + half
		&& pos.y > m_vPosition.y - half && pos.y < m_vPosition.y + half
		&& pos.z > m_vPosition.z - half && pos.z < m_vPosition.z + half){
		return true;
	}
	else {
		return false;
	}
}

void cBox::getHit(int dmg){ 
	for (UINT i = 0; i < m_vecVertex.size(); i++){
		m_vecVertex[i].c += 100;
	}
	m_hp -= dmg; 
}