#include "stdafx.h"
#include "cCharacter.h"


cCharacter::cCharacter() :
m_vecPos(0,0,0),
m_fSpeed(10.0f),
m_fAngleDegree(0.0f),
m_vecForward(0, 0, 1)
{
}

cCharacter::cCharacter(D3DXVECTOR3 origin) :
m_vecPos(origin),
m_fSpeed(10.0f),
m_fAngleDegree(0.0f),
m_vecForward(0,0,1)
{

}


cCharacter::~cCharacter()
{
	SAFE_RELESE(m_pTexture);
}

void cCharacter::init(){
	D3DXCreateTextureFromFile(
		g_pD3DDevice,
		L"../Resource/Iron_Man_Skin_2.png",
		&m_pTexture);

	ST_PT_VERTEX v;
	D3DXMATRIXA16 matScale, matRotate, matTrans, matFinal;

	float left = -0.5f;
	float top = 0.5f;
	float right = 0.5f;
	float bottom = -0.5f;


	//front
	std::vector<ST_PT_VERTEX> plane;
	v.p = D3DXVECTOR3(left, top, 0);
	v.t = D3DXVECTOR2(128.0f / 1024.0f, 128.0f / 512.0f);
	plane.push_back(v);
	v.p = D3DXVECTOR3(right, top, 0);
	v.t = D3DXVECTOR2((128.0f*2) / 1024.0f, 128.0f / 512.0f);
	plane.push_back(v);
	v.p = D3DXVECTOR3(left, bottom, 0);
	v.t = D3DXVECTOR2(128.0f / 1024.0f, (128.0f*2) / 512.0f);
	plane.push_back(v);
	v.p = D3DXVECTOR3(left, bottom, 0);
	v.t = D3DXVECTOR2(128.0f / 1024.0f, (128.0f * 2) / 512.0f);
	plane.push_back(v);
	v.p = D3DXVECTOR3(right, top, 0);
	v.t = D3DXVECTOR2((128.0f * 2) / 1024.0f, 128.0f / 512.0f);
	plane.push_back(v);
	v.p = D3DXVECTOR3(right, bottom, 0);
	v.t = D3DXVECTOR2((128.0f * 2) / 1024.0f, (128.0f*2) / 512.0f);
	plane.push_back(v);
	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		D3DXMatrixRotationY(&matRotate, D3DXToRadian(180.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		D3DXVec3TransformCoord(&v.p, &v.p, &matRotate);
		v.p.z = v.p.z + 0.5f;
		m_vecVertex.push_back(v);
	}

	// right
	plane[0].t = D3DXVECTOR2(0.0f, 128.0f / 512.0f);
	plane[1].t = D3DXVECTOR2(128.0f / 1024.0f, 128.0f / 512.0f);
	plane[2].t = D3DXVECTOR2(0.0f / 1024.0f, (128.0f * 2) / 512.0f);
	plane[3].t = D3DXVECTOR2(0.0f / 1024.0f, (128.0f * 2) / 512.0f);
	plane[4].t = D3DXVECTOR2(128.0f / 1024.0f, 128.0f / 512.0f);
	plane[5].t = D3DXVECTOR2(128.0f / 1024.0f / 1024.0f, (128.0f * 2) / 512.0f);
	
	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		D3DXMatrixRotationY(&matRotate, D3DXToRadian(270.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		D3DXVec3TransformCoord(&v.p, &v.p, &matRotate);
		v.p.x = v.p.x + 0.5f;
		m_vecVertex.push_back(v);
	}

	//back
	plane[0].t = D3DXVECTOR2((128.0f * 3) / 1024.0f, (128.0f * 1) / 512.0f);
	plane[1].t = D3DXVECTOR2(((128.0f * 4)-1.0f) / 1024.0f, (128.0f * 1) / 512.0f);
	plane[2].t = D3DXVECTOR2((128.0f * 3) / 1024.0f, (128.0f * 2) / 512.0f);
	plane[3].t = D3DXVECTOR2((128.0f * 3) / 1024.0f, (128.0f * 2) / 512.0f);
	plane[4].t = D3DXVECTOR2(((128.0f * 4) - 1.0f) / 1024.0f, (128.0f * 1) / 512.0f);
	plane[5].t = D3DXVECTOR2(((128.0f * 4) - 1.0f) / 1024.0f, (128.0f * 2) / 512.0f);
	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		//D3DXMatrixRotationY(&matRotate, D3DXToRadian(0.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		//D3DXVec3TransformCoord(&v.p, &v.p, &matRotate);
		v.p.z = v.p.z - 0.5f;
		m_vecVertex.push_back(v);
	}	
	//left
	plane[0].t = D3DXVECTOR2((128.0f * 2) / 1024.0f, (128.0f * 1) / 512.0f);
	plane[1].t = D3DXVECTOR2((128.0f * 3) / 1024.0f, (128.0f * 1) / 512.0f);
	plane[2].t = D3DXVECTOR2((128.0f * 2) / 1024.0f, (128.0f * 2) / 512.0f);
	plane[3].t = D3DXVECTOR2((128.0f * 2) / 1024.0f, (128.0f * 2) / 512.0f);
	plane[4].t = D3DXVECTOR2((128.0f * 3) / 1024.0f, (128.0f * 1) / 512.0f);
	plane[5].t = D3DXVECTOR2((128.0f * 3) / 1024.0f, (128.0f * 2) / 512.0f);
	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		D3DXMatrixRotationY(&matRotate, D3DXToRadian(90.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		D3DXVec3TransformCoord(&v.p, &v.p, &matRotate);
		v.p.x = v.p.x - 0.5f;
		m_vecVertex.push_back(v);
	}

	//top
	plane[0].t = D3DXVECTOR2((128.0f * 1) / 1024.0f, (128.0f * 0) / 512.0f);
	plane[1].t = D3DXVECTOR2((128.0f * 2) / 1024.0f, (128.0f * 0) / 512.0f);
	plane[2].t = D3DXVECTOR2((128.0f * 1) / 1024.0f, (128.0f * 1) / 512.0f);
	plane[3].t = D3DXVECTOR2((128.0f * 1) / 1024.0f, (128.0f * 1) / 512.0f);
	plane[4].t = D3DXVECTOR2((128.0f * 2) / 1024.0f, (128.0f * 0) / 512.0f);
	plane[5].t = D3DXVECTOR2((128.0f * 2) / 1024.0f, (128.0f * 1) / 512.0f);
	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		D3DXMatrixRotationX(&matRotate, D3DXToRadian(90.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		D3DXVec3TransformCoord(&v.p, &v.p, &matRotate);
		v.p.y = v.p.y + 0.5f;
		m_vecVertex.push_back(v);
	}

	// bottom
	// lefttop righttop leftbottom leftbottom righttop rightbottom
	plane[0].t = D3DXVECTOR2((128.0f * 2)/ 1024.0f, (128.0f * 0) / 512.0f);
	plane[1].t = D3DXVECTOR2((128.0f * 3) / 1024.0f, (128.0f * 0) / 512.0f);
	plane[2].t = D3DXVECTOR2((128.0f * 2) / 1024.0f, (128.0f * 1) / 512.0f);
	plane[3].t = D3DXVECTOR2((128.0f * 2) / 1024.0f, (128.0f * 1) / 512.0f);
	plane[4].t = D3DXVECTOR2((128.0f * 3) / 1024.0f, (128.0f * 0) / 512.0f);
	plane[5].t = D3DXVECTOR2((128.0f * 3) / 1024.0f, (128.0f * 1) / 512.0f);
	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		D3DXMatrixRotationX(&matRotate, D3DXToRadian(270.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		D3DXVec3TransformCoord(&v.p, &v.p, &matRotate);
		v.p.y = v.p.y - 0.5f;
		m_vecVertex.push_back(v);
	}

	std::vector<ST_PT_VERTEX> cube, originalcube;
	cube = m_vecVertex;
	originalcube = m_vecVertex;
	D3DXMatrixTranslation(&matTrans, 0.0f, 1.25f, 0.0f);
	
	for (UINT i = 0; i < m_vecVertex.size(); i++){
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &matTrans);		
	}

	///body
	D3DXMatrixScaling(&matScale, 0.8f, 1.5f, 0.5f);

	//front
	// lefttop righttop leftbottom leftbottom righttop rightbottom
	cube[0].t = D3DXVECTOR2(320.0f / 1024.0f, 320.0f / 512.0f);
	cube[1].t = D3DXVECTOR2((128.0f+320.0f) / 1024.0f, 320.0f / 512.0f);
	cube[2].t = D3DXVECTOR2(320.0f / 1024.0f, 512.0f / 512.0f);
	cube[3].t = D3DXVECTOR2(320.0f / 1024.0f, 512.0f / 512.0f);
	cube[4].t = D3DXVECTOR2((128.0f + 320.0f) / 1024.0f, 320.0f / 512.0f);
	cube[5].t = D3DXVECTOR2((128.0f + 320.0f) / 1024.0f, 512.0f / 512.0f);
	//left
	cube[6].t = D3DXVECTOR2(256.0f / 1024.0f, 320.0f / 512.0f);
	cube[7].t = D3DXVECTOR2(320.0f / 1024.0f, 320.0f / 512.0f);
	cube[8].t = D3DXVECTOR2(256.0f / 1024.0f, 512.0f / 512.0f);
	cube[9].t = D3DXVECTOR2(256.0f / 1024.0f, 512.0f / 512.0f);
	cube[10].t = D3DXVECTOR2(320.0f / 1024.0f, 320.0f / 512.0f);
	cube[11].t = D3DXVECTOR2(320.0f/1024.0f, 512.0f / 512.0f);
	//back
	cube[12].t = D3DXVECTOR2(510.0f / 1024.0f, 320.0f / 512.0f);
	cube[13].t = D3DXVECTOR2(640.0f / 1024.0f, 320.0f / 512.0f);
	cube[14].t = D3DXVECTOR2(510.0f / 1024.0f, 512.0f / 512.0f);
	cube[15].t = D3DXVECTOR2(510.0f / 1024.0f, 512.0f / 512.0f);
	cube[16].t = D3DXVECTOR2(640.0f / 1024.0f, 320.0f / 512.0f);
	cube[17].t = D3DXVECTOR2(640.0f / 1024.0f, 512.0f / 512.0f);
	//right
	cube[18].t = D3DXVECTOR2(448.0f / 1024.0f, 320.0f / 512.0f);
	cube[19].t = D3DXVECTOR2(560.0f / 1024.0f, 320.0f / 512.0f);
	cube[20].t = D3DXVECTOR2(448.0f / 1024.0f, 512.0f / 512.0f);
	cube[21].t = D3DXVECTOR2(448.0f / 1024.0f, 512.0f / 512.0f);
	cube[22].t = D3DXVECTOR2(560.0f / 1024.0f, 320.0f / 512.0f);
	cube[23].t = D3DXVECTOR2(560.0f / 1024.0f, 512.0f / 512.0f);
	//top
	cube[24].t = D3DXVECTOR2(320.0f / 1024.0f,				(128.0f * 2) / 512.0f);
	cube[25].t = D3DXVECTOR2((128.0f + 320.0f) / 1024.0f,	(128.0f * 2) / 512.0f);
	cube[26].t = D3DXVECTOR2(320.0f / 1024.0f,				320.0f / 512.0f);
	cube[27].t = D3DXVECTOR2(320.0f / 1024.0f,				320.0f / 512.0f);
	cube[28].t = D3DXVECTOR2((128.0f + 320.0f) / 1024.0f,	(128.0f * 2) / 512.0f);
	cube[29].t = D3DXVECTOR2((128.0f + 320.0f) / 1024.0f,	320.0f / 512.0f);
	// bottom
	// lefttop righttop leftbottom leftbottom righttop rightbottom
	cube[30].t = D3DXVECTOR2((128.0f + 320.0f) / 1024.0f,		(128.0f * 2) / 512.0f);
	cube[31].t = D3DXVECTOR2((128.0f * 2 + 320.0f) / 1024.0f,	(128.0f * 2) / 512.0f);
	cube[32].t = D3DXVECTOR2((128.0f + 320.0f) / 1024.0f, 320.0f / 512.0f);
	cube[33].t = D3DXVECTOR2((128.0f + 320.0f) / 1024.0f, 320.0f / 512.0f);
	cube[34].t = D3DXVECTOR2((128.0f * 2 + 320.0f) / 1024.0f, (128.0f * 2) / 512.0f);
	cube[35].t = D3DXVECTOR2((128.0f * 2 + 320.0f) / 1024.0f, 320.0f / 512.0f);

	for (UINT i = 0; i < cube.size(); i++){
		D3DXVec3TransformCoord(&cube[i].p, &originalcube[i].p, &matScale);
		m_vecVertex.push_back(cube[i]);
	}

	/// Arm
	//front 
	// lefttop righttop leftbottom leftbottom righttop rightbottom
	// 704 320
	// 768 512
	cube[0].t = D3DXVECTOR2(704.0f / 1024.0f, 320.0f / 512.0f);
	cube[1].t = D3DXVECTOR2(768.0f / 1024.0f, 320.0f / 512.0f);
	cube[2].t = D3DXVECTOR2(704.0f / 1024.0f, 512.0f / 512.0f);
	cube[3].t = D3DXVECTOR2(704.0f / 1024.0f, 512.0f / 512.0f);
	cube[4].t = D3DXVECTOR2(768.0f / 1024.0f, 320.0f / 512.0f);
	cube[5].t = D3DXVECTOR2(768.0f / 1024.0f, 512.0f / 512.0f);
	//left
	cube[6].t = D3DXVECTOR2(768.0f / 1024.0f, 320.0f / 512.0f);
	cube[7].t = D3DXVECTOR2(832.0f / 1024.0f, 320.0f / 512.0f);
	cube[8].t = D3DXVECTOR2(768.0f / 1024.0f, 512.0f / 512.0f);
	cube[9].t = D3DXVECTOR2(768.0f / 1024.0f, 512.0f / 512.0f);
	cube[10].t = D3DXVECTOR2(832.0f / 1024.0f, 320.0f / 512.0f);
	cube[11].t = D3DXVECTOR2(768.0f / 1024.0f, 512.0f / 512.0f);
	//back
	cube[12].t = D3DXVECTOR2(832.0f / 1024.0f, 320.0f / 512.0f);
	cube[13].t = D3DXVECTOR2(896.0f / 1024.0f, 320.0f / 512.0f);
	cube[14].t = D3DXVECTOR2(832.0f / 1024.0f, 512.0f / 512.0f);
	cube[15].t = D3DXVECTOR2(832.0f / 1024.0f, 512.0f / 512.0f);
	cube[16].t = D3DXVECTOR2(896.0f / 1024.0f, 320.0f / 512.0f);
	cube[17].t = D3DXVECTOR2(896.0f / 1024.0f, 512.0f / 512.0f);
	//right
	cube[18].t = D3DXVECTOR2(640.0f / 1024.0f, 320.0f / 512.0f);
	cube[19].t = D3DXVECTOR2(704.0f / 1024.0f, 320.0f / 512.0f);
	cube[20].t = D3DXVECTOR2(640.0f / 1024.0f, 512.0f / 512.0f);
	cube[21].t = D3DXVECTOR2(640.0f / 1024.0f, 512.0f / 512.0f);
	cube[22].t = D3DXVECTOR2(704.0f / 1024.0f, 320.0f / 512.0f);
	cube[23].t = D3DXVECTOR2(704.0f / 1024.0f, 512.0f / 512.0f);
	//top
	cube[24].t = D3DXVECTOR2(704.0f / 1024.0f, (128.0f * 2) / 512.0f);
	cube[25].t = D3DXVECTOR2(768.0f / 1024.0f, (128.0f * 2) / 512.0f);
	cube[26].t = D3DXVECTOR2(704.0f / 1024.0f, 320.0f / 512.0f);
	cube[27].t = D3DXVECTOR2(704.0f / 1024.0f, 320.0f / 512.0f);
	cube[28].t = D3DXVECTOR2(768.0f / 1024.0f, (128.0f * 2) / 512.0f);
	cube[29].t = D3DXVECTOR2(768.0f / 1024.0f, 320.0f / 512.0f);
	// bottom
	// lefttop righttop leftbottom leftbottom righttop rightbottom
	cube[30].t = D3DXVECTOR2(768.0f / 1024.0f, (128.0f * 2) / 512.0f);
	cube[31].t = D3DXVECTOR2(832.0f / 1024.0f, (128.0f * 2) / 512.0f);
	cube[32].t = D3DXVECTOR2(768.0f / 1024.0f, 320.0f / 512.0f);
	cube[33].t = D3DXVECTOR2(768.0f / 1024.0f, 320.0f / 512.0f);
	cube[34].t = D3DXVECTOR2(832.0f / 1024.0f, (128.0f * 2) / 512.0f);
	cube[35].t = D3DXVECTOR2(832.0f / 1024.0f, 320.0f / 512.0f);
	D3DXMatrixScaling(&matScale, 0.4f, 1.5f, 0.5f);
	D3DXMatrixTranslation(&matTrans, -0.6f, 0.0, 0.0f);
	matFinal = matScale*matTrans;
	for (UINT i = 0; i < cube.size(); i++){
		D3DXVec3TransformCoord(&cube[i].p, &originalcube[i].p, &matFinal);
		m_vecVertex.push_back(cube[i]);
	}

	//front
	cube[0].t = D3DXVECTOR2(768.0f / 1024.0f, 320.0f / 512.0f);
	cube[1].t = D3DXVECTOR2(704.0f / 1024.0f, 320.0f / 512.0f);
	cube[2].t = D3DXVECTOR2(768.0f / 1024.0f, 512.0f / 512.0f);
	cube[3].t = D3DXVECTOR2(768.0f / 1024.0f, 512.0f / 512.0f);
	cube[4].t = D3DXVECTOR2(704.0f / 1024.0f, 320.0f / 512.0f);
	cube[5].t = D3DXVECTOR2(704.0f / 1024.0f, 512.0f / 512.0f);
	//left
	cube[6].t = D3DXVECTOR2(768.0f / 1024.0f, 320.0f / 512.0f);
	cube[7].t = D3DXVECTOR2(832.0f / 1024.0f, 320.0f / 512.0f);
	cube[8].t = D3DXVECTOR2(768.0f / 1024.0f, 512.0f / 512.0f);
	cube[9].t = D3DXVECTOR2(768.0f / 1024.0f, 512.0f / 512.0f);
	cube[10].t = D3DXVECTOR2(832.0f / 1024.0f, 320.0f / 512.0f);
	cube[11].t = D3DXVECTOR2(768.0f / 1024.0f, 512.0f / 512.0f);
	//back
	cube[12].t = D3DXVECTOR2(896.0f / 1024.0f, 320.0f / 512.0f);
	cube[13].t = D3DXVECTOR2(832.0f / 1024.0f, 320.0f / 512.0f);
	cube[14].t = D3DXVECTOR2(896.0f / 1024.0f, 512.0f / 512.0f);
	cube[15].t = D3DXVECTOR2(896.0f / 1024.0f, 512.0f / 512.0f);
	cube[16].t = D3DXVECTOR2(832.0f / 1024.0f, 320.0f / 512.0f);
	cube[17].t = D3DXVECTOR2(832.0f / 1024.0f, 512.0f / 512.0f);
	//right
	cube[18].t = D3DXVECTOR2(640.0f / 1024.0f, 320.0f / 512.0f);
	cube[19].t = D3DXVECTOR2(704.0f / 1024.0f, 320.0f / 512.0f);
	cube[20].t = D3DXVECTOR2(640.0f / 1024.0f, 512.0f / 512.0f);
	cube[21].t = D3DXVECTOR2(640.0f / 1024.0f, 512.0f / 512.0f);
	cube[22].t = D3DXVECTOR2(704.0f / 1024.0f, 320.0f / 512.0f);
	cube[23].t = D3DXVECTOR2(704.0f / 1024.0f, 512.0f / 512.0f);
	D3DXMatrixScaling(&matScale, 0.4f, 1.5f, 0.5f);
	D3DXMatrixTranslation(&matTrans, 0.6f, 0.0, 0.0f);
	matFinal = matScale*matTrans;
	for (UINT i = 0; i < cube.size(); i++){
		D3DXVec3TransformCoord(&cube[i].p, &originalcube[i].p, &matFinal);
		m_vecVertex.push_back(cube[i]);
	}

	D3DXMatrixTranslation(&matTrans, 0.0f, 1.5f, 0.0f);
	for (UINT i = 0; i < m_vecVertex.size(); i++){
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &matTrans);
	}	

	/// leg

	//front 
	// lefttop righttop leftbottom leftbottom righttop rightbottom
	// 704 320
	// 768 512
	cube[0].t = D3DXVECTOR2(64.0f / 1024.0f, 320.0f / 512.0f);
	cube[1].t = D3DXVECTOR2(128.0f / 1024.0f, 320.0f / 512.0f);
	cube[2].t = D3DXVECTOR2(64.0f / 1024.0f, 512.0f / 512.0f);
	cube[3].t = D3DXVECTOR2(64.0f / 1024.0f, 512.0f / 512.0f);
	cube[4].t = D3DXVECTOR2(128.0f / 1024.0f, 320.0f / 512.0f);
	cube[5].t = D3DXVECTOR2(128.0f / 1024.0f, 512.0f / 512.0f);
	//left
	cube[6].t = D3DXVECTOR2(192.0f / 1024.0f, 320.0f / 512.0f);
	cube[7].t = D3DXVECTOR2(256.0f / 1024.0f, 320.0f / 512.0f);
	cube[8].t = D3DXVECTOR2(192.0f / 1024.0f, 512.0f / 512.0f);
	cube[9].t = D3DXVECTOR2(192.0f / 1024.0f, 512.0f / 512.0f);
	cube[10].t = D3DXVECTOR2(256.0f / 1024.0f, 320.0f / 512.0f);
	cube[11].t = D3DXVECTOR2(256.0f / 1024.0f, 512.0f / 512.0f);
	//back
	cube[12].t = D3DXVECTOR2(128.0f / 1024.0f, 320.0f / 512.0f);
	cube[13].t = D3DXVECTOR2(192.0f / 1024.0f, 320.0f / 512.0f);
	cube[14].t = D3DXVECTOR2(128.0f / 1024.0f, 512.0f / 512.0f);
	cube[15].t = D3DXVECTOR2(128.0f / 1024.0f, 512.0f / 512.0f);
	cube[16].t = D3DXVECTOR2(192.0f / 1024.0f, 320.0f / 512.0f);
	cube[17].t = D3DXVECTOR2(192.0f / 1024.0f, 512.0f / 512.0f);
	//right
	cube[18].t = D3DXVECTOR2(0 / 1024.0f, 320.0f / 512.0f);
	cube[19].t = D3DXVECTOR2(64.0f / 1024.0f, 320.0f / 512.0f);
	cube[20].t = D3DXVECTOR2(0 / 1024.0f, 512.0f / 512.0f);
	cube[21].t = D3DXVECTOR2(0 / 1024.0f, 512.0f / 512.0f);
	cube[22].t = D3DXVECTOR2(64.0f / 1024.0f, 320.0f / 512.0f);
	cube[23].t = D3DXVECTOR2(64.0f / 1024.0f, 512.0f / 512.0f);
	//top
	cube[24].t = D3DXVECTOR2(64.0f / 1024.0f, (128.0f * 2) / 512.0f);
	cube[25].t = D3DXVECTOR2(128.0f / 1024.0f, (128.0f * 2) / 512.0f);
	cube[26].t = D3DXVECTOR2(64.0f / 1024.0f, 320.0f / 512.0f);
	cube[27].t = D3DXVECTOR2(64.0f / 1024.0f, 320.0f / 512.0f);
	cube[28].t = D3DXVECTOR2(128.0f / 1024.0f, (128.0f * 2) / 512.0f);
	cube[29].t = D3DXVECTOR2(128.0f / 1024.0f, 320.0f / 512.0f);
	// bottom
	// lefttop righttop leftbottom leftbottom righttop rightbottom
	cube[30].t = D3DXVECTOR2(128.0f / 1024.0f, (128.0f * 2) / 512.0f);
	cube[31].t = D3DXVECTOR2(192.0f / 1024.0f, (128.0f * 2) / 512.0f);
	cube[32].t = D3DXVECTOR2(128.0f / 1024.0f, 320.0f / 512.0f);
	cube[33].t = D3DXVECTOR2(128.0f / 1024.0f, 320.0f / 512.0f);
	cube[34].t = D3DXVECTOR2(192.0f / 1024.0f, (128.0f * 2) / 512.0f);
	cube[35].t = D3DXVECTOR2(192.0f / 1024.0f, 320.0f / 512.0f);

	D3DXMatrixScaling(&matScale, 0.4f, 1.5f, 0.5f);
	D3DXMatrixTranslation(&matTrans, -0.2f, 0.0, 0.0f);
	matFinal = matScale*matTrans;
	for (UINT i = 0; i < cube.size(); i++){
		D3DXVec3TransformCoord(&cube[i].p, &originalcube[i].p, &matFinal);
		m_vecVertex.push_back(cube[i]);
	}
	

	//front 
	// lefttop righttop leftbottom leftbottom righttop rightbottom
	// 704 320
	// 768 512
	cube[0].t = D3DXVECTOR2(128.0f/ 1024.0f, 320.0f / 512.0f);
	cube[1].t = D3DXVECTOR2(64.0f / 1024.0f, 320.0f / 512.0f);
	cube[2].t = D3DXVECTOR2(128.0f / 1024.0f, 512.0f / 512.0f);
	cube[3].t = D3DXVECTOR2(128.0f / 1024.0f, 512.0f / 512.0f);
	cube[4].t = D3DXVECTOR2(64.0f / 1024.0f, 320.0f / 512.0f);
	cube[5].t = D3DXVECTOR2(64.0f / 1024.0f, 512.0f / 512.0f);
	//left
	cube[6].t = D3DXVECTOR2(192.0f / 1024.0f, 320.0f / 512.0f);
	cube[7].t = D3DXVECTOR2(256.0f / 1024.0f, 320.0f / 512.0f);
	cube[8].t = D3DXVECTOR2(192.0f / 1024.0f, 512.0f / 512.0f);
	cube[9].t = D3DXVECTOR2(192.0f / 1024.0f, 512.0f / 512.0f);
	cube[10].t = D3DXVECTOR2(256.0f / 1024.0f, 320.0f / 512.0f);
	cube[11].t = D3DXVECTOR2(256.0f / 1024.0f, 512.0f / 512.0f);
	//back
	cube[12].t = D3DXVECTOR2(192.0f / 1024.0f, 320.0f / 512.0f);
	cube[13].t = D3DXVECTOR2(128.0f / 1024.0f, 320.0f / 512.0f);
	cube[14].t = D3DXVECTOR2(192.0f / 1024.0f, 512.0f / 512.0f);
	cube[15].t = D3DXVECTOR2(192.0f / 1024.0f, 512.0f / 512.0f);
	cube[16].t = D3DXVECTOR2(128.0f / 1024.0f, 320.0f / 512.0f);
	cube[17].t = D3DXVECTOR2(128.0f / 1024.0f, 512.0f / 512.0f);
	//right
	cube[18].t = D3DXVECTOR2(0 / 1024.0f, 320.0f / 512.0f);
	cube[19].t = D3DXVECTOR2(64.0f / 1024.0f, 320.0f / 512.0f);
	cube[20].t = D3DXVECTOR2(0 / 1024.0f, 512.0f / 512.0f);
	cube[21].t = D3DXVECTOR2(0 / 1024.0f, 512.0f / 512.0f);
	cube[22].t = D3DXVECTOR2(64.0f / 1024.0f, 320.0f / 512.0f);
	cube[23].t = D3DXVECTOR2(64.0f / 1024.0f, 512.0f / 512.0f);
	//top
	cube[24].t = D3DXVECTOR2(64.0f / 1024.0f, (128.0f * 2) / 512.0f);
	cube[25].t = D3DXVECTOR2(128.0f / 1024.0f, (128.0f * 2) / 512.0f);
	cube[26].t = D3DXVECTOR2(64.0f / 1024.0f, 320.0f / 512.0f);
	cube[27].t = D3DXVECTOR2(64.0f / 1024.0f, 320.0f / 512.0f);
	cube[28].t = D3DXVECTOR2(128.0f / 1024.0f, (128.0f * 2) / 512.0f);
	cube[29].t = D3DXVECTOR2(128.0f / 1024.0f, 320.0f / 512.0f);
	// bottom
	// lefttop righttop leftbottom leftbottom righttop rightbottom
	cube[30].t = D3DXVECTOR2(128.0f / 1024.0f, (128.0f * 2) / 512.0f);
	cube[31].t = D3DXVECTOR2(192.0f / 1024.0f, (128.0f * 2) / 512.0f);
	cube[32].t = D3DXVECTOR2(128.0f / 1024.0f, 320.0f / 512.0f);
	cube[33].t = D3DXVECTOR2(128.0f / 1024.0f, 320.0f / 512.0f);
	cube[34].t = D3DXVECTOR2(192.0f / 1024.0f, (128.0f * 2) / 512.0f);
	cube[35].t = D3DXVECTOR2(192.0f / 1024.0f, 320.0f / 512.0f);
	D3DXMatrixTranslation(&matTrans, 0.2f, 0.0, 0.0f);
	matFinal = matScale*matTrans;
	for (UINT i = 0; i < cube.size(); i++){
		D3DXVec3TransformCoord(&cube[i].p, &originalcube[i].p, &matFinal);
		m_vecVertex.push_back(cube[i]);
	}
}

void cCharacter::update(float delta){
	D3DXMATRIXA16 matR;
	if (GetKeyState('A') & 0x8000){
		m_fAngleDegree -= 90.0f * delta;
		D3DXMatrixRotationY(&matR, D3DXToRadian(m_fAngleDegree));
		m_vecForward = D3DXVECTOR3(0, 0, 1);
		D3DXVec3TransformNormal(&m_vecForward, &m_vecForward, &matR);
		//m_vec3Origin.x = m_vec3Origin.x - 10.0f*delta;
	}
	if (GetKeyState('D') & 0x8000){
		m_fAngleDegree += 90.0f * delta;
		D3DXMatrixRotationY(&matR, D3DXToRadian(m_fAngleDegree));
		m_vecForward = D3DXVECTOR3(0, 0, 1);
		D3DXVec3TransformNormal(&m_vecForward, &m_vecForward, &matR);
		//m_vec3Origin.x = m_vec3Origin.x + 10.0f*delta;
	}
	if (GetKeyState('W') & 0x8000){
		//m_fAngleDegree += 10.0f * delta;
		m_vecPos += m_vecForward*m_fSpeed*delta;
	}
	if (GetKeyState('S') & 0x8000){
		//m_fAngleDegree += 10.0f * delta;
		/*m_vec3Origin.y;
		m_vec3Origin.x = m_vec3Origin.x - 10.0f * delta * sinf(D3DXToRadian(m_fAngleDegree));
		m_vec3Origin.z = m_vec3Origin.z - 10.0f * delta * cosf(D3DXToRadian(m_fAngleDegree));*/
		m_vecPos -= m_vecForward*m_fSpeed*delta;
	}
}

void cCharacter::render(){
	D3DXMATRIXA16 matWorld, matR, matT;
	D3DXMatrixRotationY(&matR, D3DXToRadian(m_fAngleDegree));
	D3DXMatrixTranslation(&matT, m_vecPos.x, m_vecPos.y, m_vecPos.z);

	matWorld = matR * matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PT_VERTEX));

	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
}