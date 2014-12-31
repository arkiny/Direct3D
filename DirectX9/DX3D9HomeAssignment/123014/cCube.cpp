#include "stdafx.h"
#include "cCube.h"


cCube::cCube()
	: m_vPosition(0, 0, 0)
	, m_vForward(0, 0, 1)
	, m_fAngle(0.0f)
	, m_fSpeed(0.5f)
	, m_pTexture(NULL)
	, m_worldMatrix(NULL)
	, m_fShakingAngle(0.0f)
{
}


cCube::~cCube()
{
	SAFE_RELEASE(m_pTexture);
}

void cCube::init(float fWidth, float fHeight, float fDepth, Cube_Part type){
	m_eType = type;

	ST_PT_VERTEX v;
	D3DXMATRIXA16 matScale, matRotate, matTrans, matFinal;

	float left = -0.5f;
	float top = 0.5f;
	float right = 0.5f;
	float bottom = -0.5f;
	float frontdepth = 0.5f;
	float backdepth = -0.5f;
	
	//front
	std::vector<ST_PT_VERTEX> plane;
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
	
	for (UINT j = 0; j < plane.size(); j++){
		v = plane[j];
		D3DXMatrixRotationY(&matRotate, D3DXToRadian(180.0f));
		//D3DXMatrixTranslation(&matTrans, m_vec3Origin.x, m_vec3Origin.y, m_vec3Origin.z);
		//matFinal = matRotate * matTrans;
		D3DXVec3TransformCoord(&v.p, &v.p, &matRotate);
		v.p.z = v.p.z + frontdepth;
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
		m_vecVertex.push_back(v);
	}

	D3DXMatrixScaling(&matScale, fWidth, fHeight, fDepth);
	for (UINT i = 0; i < m_vecVertex.size(); i++){
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &matScale);
	}

	if (type == PT_head){
		// right
		m_vecVertex[0].t = D3DXVECTOR2(128.0f / 1024.0f, 128.0f / 512.0f);
		m_vecVertex[1].t = D3DXVECTOR2((128.0f * 2) / 1024.0f, 128.0f / 512.0f);
		m_vecVertex[2].t = D3DXVECTOR2(128.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[3].t = D3DXVECTOR2(128.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[4].t = D3DXVECTOR2((128.0f * 2) / 1024.0f, 128.0f / 512.0f);
		m_vecVertex[5].t = D3DXVECTOR2((128.0f * 2) / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[6].t = D3DXVECTOR2(0.0f, 128.0f / 512.0f);
		m_vecVertex[7].t = D3DXVECTOR2(128.0f / 1024.0f, 128.0f / 512.0f);
		m_vecVertex[8].t = D3DXVECTOR2(0.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[9].t = D3DXVECTOR2(0.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[10].t = D3DXVECTOR2(128.0f / 1024.0f, 128.0f / 512.0f);
		m_vecVertex[11].t = D3DXVECTOR2(128.0f / 1024.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[12].t = D3DXVECTOR2((128.0f * 3) / 1024.0f, (128.0f * 1) / 512.0f);
		m_vecVertex[13].t = D3DXVECTOR2(((128.0f * 4) - 1.0f) / 1024.0f, (128.0f * 1) / 512.0f);
		m_vecVertex[14].t = D3DXVECTOR2((128.0f * 3) / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[15].t = D3DXVECTOR2((128.0f * 3) / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[16].t = D3DXVECTOR2(((128.0f * 4) - 1.0f) / 1024.0f, (128.0f * 1) / 512.0f);
		m_vecVertex[17].t = D3DXVECTOR2(((128.0f * 4) - 1.0f) / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[18].t = D3DXVECTOR2((128.0f * 2) / 1024.0f, (128.0f * 1) / 512.0f);
		m_vecVertex[19].t = D3DXVECTOR2((128.0f * 3) / 1024.0f, (128.0f * 1) / 512.0f);
		m_vecVertex[20].t = D3DXVECTOR2((128.0f * 2) / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[21].t = D3DXVECTOR2((128.0f * 2) / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[22].t = D3DXVECTOR2((128.0f * 3) / 1024.0f, (128.0f * 1) / 512.0f);
		m_vecVertex[23].t = D3DXVECTOR2((128.0f * 3) / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[24].t = D3DXVECTOR2((128.0f * 1) / 1024.0f, (128.0f * 0) / 512.0f);
		m_vecVertex[25].t = D3DXVECTOR2((128.0f * 2) / 1024.0f, (128.0f * 0) / 512.0f);
		m_vecVertex[26].t = D3DXVECTOR2((128.0f * 1) / 1024.0f, (128.0f * 1) / 512.0f);
		m_vecVertex[27].t = D3DXVECTOR2((128.0f * 1) / 1024.0f, (128.0f * 1) / 512.0f);
		m_vecVertex[28].t = D3DXVECTOR2((128.0f * 2) / 1024.0f, (128.0f * 0) / 512.0f);
		m_vecVertex[29].t = D3DXVECTOR2((128.0f * 2) / 1024.0f, (128.0f * 1) / 512.0f);
		m_vecVertex[30].t = D3DXVECTOR2((128.0f * 2) / 1024.0f, (128.0f * 0) / 512.0f);
		m_vecVertex[31].t = D3DXVECTOR2((128.0f * 3) / 1024.0f, (128.0f * 0) / 512.0f);
		m_vecVertex[32].t = D3DXVECTOR2((128.0f * 2) / 1024.0f, (128.0f * 1) / 512.0f);
		m_vecVertex[33].t = D3DXVECTOR2((128.0f * 2) / 1024.0f, (128.0f * 1) / 512.0f);
		m_vecVertex[34].t = D3DXVECTOR2((128.0f * 3) / 1024.0f, (128.0f * 0) / 512.0f);
		m_vecVertex[35].t = D3DXVECTOR2((128.0f * 3) / 1024.0f, (128.0f * 1) / 512.0f);
	}
	else if (type == PT_body){
		//front
		m_vecVertex[0].t = D3DXVECTOR2(320.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[1].t = D3DXVECTOR2((128.0f + 320.0f) / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[2].t = D3DXVECTOR2(320.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[3].t = D3DXVECTOR2(320.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[4].t = D3DXVECTOR2((128.0f + 320.0f) / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[5].t = D3DXVECTOR2((128.0f + 320.0f) / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[6].t = D3DXVECTOR2(256.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[7].t = D3DXVECTOR2(320.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[8].t = D3DXVECTOR2(256.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[9].t = D3DXVECTOR2(256.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[10].t = D3DXVECTOR2(320.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[11].t = D3DXVECTOR2(320.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[12].t = D3DXVECTOR2(510.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[13].t = D3DXVECTOR2(640.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[14].t = D3DXVECTOR2(510.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[15].t = D3DXVECTOR2(510.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[16].t = D3DXVECTOR2(640.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[17].t = D3DXVECTOR2(640.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[18].t = D3DXVECTOR2(448.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[19].t = D3DXVECTOR2(560.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[20].t = D3DXVECTOR2(448.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[21].t = D3DXVECTOR2(448.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[22].t = D3DXVECTOR2(560.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[23].t = D3DXVECTOR2(560.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[24].t = D3DXVECTOR2(320.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[25].t = D3DXVECTOR2((128.0f + 320.0f) / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[26].t = D3DXVECTOR2(320.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[27].t = D3DXVECTOR2(320.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[28].t = D3DXVECTOR2((128.0f + 320.0f) / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[29].t = D3DXVECTOR2((128.0f + 320.0f) / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[30].t = D3DXVECTOR2((128.0f + 320.0f) / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[31].t = D3DXVECTOR2((128.0f * 2 + 320.0f) / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[32].t = D3DXVECTOR2((128.0f + 320.0f) / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[33].t = D3DXVECTOR2((128.0f + 320.0f) / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[34].t = D3DXVECTOR2((128.0f * 2 + 320.0f) / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[35].t = D3DXVECTOR2((128.0f * 2 + 320.0f) / 1024.0f, 320.0f / 512.0f);
	}
	else if (type == PT_arm_left){
		m_vecVertex[0].t = D3DXVECTOR2(704.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[1].t = D3DXVECTOR2(768.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[2].t = D3DXVECTOR2(704.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[3].t = D3DXVECTOR2(704.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[4].t = D3DXVECTOR2(768.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[5].t = D3DXVECTOR2(768.0f / 1024.0f, 512.0f / 512.0f);
		
		m_vecVertex[6].t = D3DXVECTOR2(640.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[7].t = D3DXVECTOR2(704.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[8].t = D3DXVECTOR2(640.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[9].t = D3DXVECTOR2(640.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[10].t = D3DXVECTOR2(704.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[11].t = D3DXVECTOR2(704.0f / 1024.0f, 512.0f / 512.0f);
		
		m_vecVertex[12].t = D3DXVECTOR2(832.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[13].t = D3DXVECTOR2(896.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[14].t = D3DXVECTOR2(832.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[15].t = D3DXVECTOR2(832.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[16].t = D3DXVECTOR2(896.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[17].t = D3DXVECTOR2(896.0f / 1024.0f, 512.0f / 512.0f);
		
		m_vecVertex[18].t = D3DXVECTOR2(768.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[19].t = D3DXVECTOR2(832.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[20].t = D3DXVECTOR2(768.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[21].t = D3DXVECTOR2(768.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[22].t = D3DXVECTOR2(832.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[23].t = D3DXVECTOR2(768.0f / 1024.0f, 512.0f / 512.0f);
		
		m_vecVertex[24].t = D3DXVECTOR2(768.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[25].t = D3DXVECTOR2(704.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[26].t = D3DXVECTOR2(768.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[27].t = D3DXVECTOR2(768.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[28].t = D3DXVECTOR2(704.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[29].t = D3DXVECTOR2(704.0f / 1024.0f, 320.0f / 512.0f);

		m_vecVertex[30].t = D3DXVECTOR2(768.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[31].t = D3DXVECTOR2(832.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[32].t = D3DXVECTOR2(768.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[33].t = D3DXVECTOR2(768.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[34].t = D3DXVECTOR2(832.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[35].t = D3DXVECTOR2(832.0f / 1024.0f, 320.0f / 512.0f);
	}
	else if (type == PT_arm_right){
		m_vecVertex[0].t = D3DXVECTOR2(768.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[1].t = D3DXVECTOR2(704.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[2].t = D3DXVECTOR2(768.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[3].t = D3DXVECTOR2(768.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[4].t = D3DXVECTOR2(704.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[5].t = D3DXVECTOR2(704.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[6].t = D3DXVECTOR2(768.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[7].t = D3DXVECTOR2(832.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[8].t = D3DXVECTOR2(768.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[9].t = D3DXVECTOR2(768.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[10].t = D3DXVECTOR2(832.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[11].t = D3DXVECTOR2(768.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[12].t = D3DXVECTOR2(896.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[13].t = D3DXVECTOR2(832.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[14].t = D3DXVECTOR2(896.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[15].t = D3DXVECTOR2(896.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[16].t = D3DXVECTOR2(832.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[17].t = D3DXVECTOR2(832.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[18].t = D3DXVECTOR2(640.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[19].t = D3DXVECTOR2(704.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[20].t = D3DXVECTOR2(640.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[21].t = D3DXVECTOR2(640.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[22].t = D3DXVECTOR2(704.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[23].t = D3DXVECTOR2(704.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[24].t = D3DXVECTOR2(704.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[25].t = D3DXVECTOR2(768.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[26].t = D3DXVECTOR2(704.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[27].t = D3DXVECTOR2(704.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[28].t = D3DXVECTOR2(768.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[29].t = D3DXVECTOR2(768.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[30].t = D3DXVECTOR2(768.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[31].t = D3DXVECTOR2(832.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[32].t = D3DXVECTOR2(768.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[33].t = D3DXVECTOR2(768.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[34].t = D3DXVECTOR2(832.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[35].t = D3DXVECTOR2(832.0f / 1024.0f, 320.0f / 512.0f);
	}
	else if (type == PT_leg_left){
		m_vecVertex[0].t = D3DXVECTOR2(64.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[1].t = D3DXVECTOR2(128.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[2].t = D3DXVECTOR2(64.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[3].t = D3DXVECTOR2(64.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[4].t = D3DXVECTOR2(128.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[5].t = D3DXVECTOR2(128.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[6].t = D3DXVECTOR2(192.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[7].t = D3DXVECTOR2(256.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[8].t = D3DXVECTOR2(192.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[9].t = D3DXVECTOR2(192.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[10].t = D3DXVECTOR2(256.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[11].t = D3DXVECTOR2(256.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[12].t = D3DXVECTOR2(128.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[13].t = D3DXVECTOR2(192.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[14].t = D3DXVECTOR2(128.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[15].t = D3DXVECTOR2(128.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[16].t = D3DXVECTOR2(192.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[17].t = D3DXVECTOR2(192.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[18].t = D3DXVECTOR2(0 / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[19].t = D3DXVECTOR2(64.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[20].t = D3DXVECTOR2(0 / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[21].t = D3DXVECTOR2(0 / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[22].t = D3DXVECTOR2(64.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[23].t = D3DXVECTOR2(64.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[24].t = D3DXVECTOR2(64.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[25].t = D3DXVECTOR2(128.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[26].t = D3DXVECTOR2(64.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[27].t = D3DXVECTOR2(64.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[28].t = D3DXVECTOR2(128.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[29].t = D3DXVECTOR2(128.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[30].t = D3DXVECTOR2(128.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[31].t = D3DXVECTOR2(192.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[32].t = D3DXVECTOR2(128.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[33].t = D3DXVECTOR2(128.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[34].t = D3DXVECTOR2(192.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[35].t = D3DXVECTOR2(192.0f / 1024.0f, 320.0f / 512.0f);
	}
	else if (type == PT_leg_right){
		m_vecVertex[0].t = D3DXVECTOR2(128.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[1].t = D3DXVECTOR2(64.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[2].t = D3DXVECTOR2(128.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[3].t = D3DXVECTOR2(128.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[4].t = D3DXVECTOR2(64.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[5].t = D3DXVECTOR2(64.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[6].t = D3DXVECTOR2(192.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[7].t = D3DXVECTOR2(256.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[8].t = D3DXVECTOR2(192.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[9].t = D3DXVECTOR2(192.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[10].t = D3DXVECTOR2(256.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[11].t = D3DXVECTOR2(256.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[12].t = D3DXVECTOR2(192.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[13].t = D3DXVECTOR2(128.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[14].t = D3DXVECTOR2(192.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[15].t = D3DXVECTOR2(192.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[16].t = D3DXVECTOR2(128.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[17].t = D3DXVECTOR2(128.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[18].t = D3DXVECTOR2(0 / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[19].t = D3DXVECTOR2(64.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[20].t = D3DXVECTOR2(0 / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[21].t = D3DXVECTOR2(0 / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[22].t = D3DXVECTOR2(64.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[23].t = D3DXVECTOR2(64.0f / 1024.0f, 512.0f / 512.0f);
		m_vecVertex[24].t = D3DXVECTOR2(64.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[25].t = D3DXVECTOR2(128.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[26].t = D3DXVECTOR2(64.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[27].t = D3DXVECTOR2(64.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[28].t = D3DXVECTOR2(128.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[29].t = D3DXVECTOR2(128.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[30].t = D3DXVECTOR2(128.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[31].t = D3DXVECTOR2(192.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[32].t = D3DXVECTOR2(128.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[33].t = D3DXVECTOR2(128.0f / 1024.0f, 320.0f / 512.0f);
		m_vecVertex[34].t = D3DXVECTOR2(192.0f / 1024.0f, (128.0f * 2) / 512.0f);
		m_vecVertex[35].t = D3DXVECTOR2(192.0f / 1024.0f, 320.0f / 512.0f);
	}	

	m_vecIdleVertex = m_vecVertex;
}

void cCube::SetTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	pTexture->AddRef();
	m_pTexture = pTexture;
}

void cCube::update(float delta){
	D3DXMATRIXA16 matR, matT, matT2, matFinal;
	if ((GetKeyState('W') & 0x8000) || (GetKeyState('S') & 0x8000)){
		m_bMoved = true;
		switch (m_eType)
		{
		case cCube::PT_leg_left:
			D3DXMatrixTranslation(&matT, 0, -2.0f, 0);
			D3DXMatrixRotationX(&matR, D3DXToRadian(m_fShakingAngleUnit));
			D3DXMatrixTranslation(&matT2, 0, 2.0f, 0);
			m_fShakingAngle += m_fShakingAngleUnit * delta;
			if (m_fShakingAngle > 0.5f || m_fShakingAngle < -0.5f){
				m_fShakingAngleUnit *= -1;
			}
			matFinal = matT * matR *matT2;
			for (UINT i = 0; i < m_vecVertex.size(); i++){
				D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &matFinal);
			}			
			break;
		case cCube::PT_leg_right:
			D3DXMatrixTranslation(&matT, 0, -2.0f, 0);
			D3DXMatrixRotationX(&matR, D3DXToRadian(-m_fShakingAngleUnit));
			D3DXMatrixTranslation(&matT2, 0, 2.0f, 0);
			m_fShakingAngle += -m_fShakingAngleUnit * delta;
			if (m_fShakingAngle > 0.5f || m_fShakingAngle < -0.5f){
				m_fShakingAngleUnit *= -1;
			}
			matFinal = matT * matR *matT2;
			for (UINT i = 0; i < m_vecVertex.size(); i++){
				D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &matFinal);
			}
			break;
		case cCube::PT_arm_left:
			D3DXMatrixTranslation(&matT, 0, -2.0f, 0);
			D3DXMatrixRotationX(&matR, D3DXToRadian(m_fShakingAngleUnit));
			D3DXMatrixTranslation(&matT2, 0, 2.0f, 0);
			m_fShakingAngle += m_fShakingAngleUnit * delta;
			if (m_fShakingAngle > 0.5f || m_fShakingAngle < -0.5f){
				m_fShakingAngleUnit *= -1;
			}
			matFinal = matT * matR *matT2;
			for (UINT i = 0; i < m_vecVertex.size(); i++){
				D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &matFinal);
			}
			break;
		case cCube::PT_arm_right:
			D3DXMatrixTranslation(&matT, 0, -2.0f, 0);
			D3DXMatrixRotationX(&matR, D3DXToRadian(-m_fShakingAngleUnit));
			D3DXMatrixTranslation(&matT2, 0, 2.0f, 0);
			m_fShakingAngle += -m_fShakingAngleUnit * delta;
			if (m_fShakingAngle > 0.5f || m_fShakingAngle < -0.5f){
				m_fShakingAngleUnit *= -1;
			}
			matFinal = matT * matR *matT2;
			for (UINT i = 0; i < m_vecVertex.size(); i++){
				D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &matFinal);
			}
			break;
		default:
			break;
		}
	}
	else{
		if (m_bMoved){
			m_vecVertex = m_vecIdleVertex;
			m_fShakingAngle = 0;
		}
	}
}

void cCube::render(){
	D3DXMATRIXA16 matWorld, matR, matT;
	//D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationY(&matR, m_fAngle);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	matWorld = matR * matT;
	if (m_worldMatrix)
		matWorld = matWorld * (*m_worldMatrix);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex.size() / 3,
		&m_vecVertex[0],
		sizeof(ST_PT_VERTEX));
}
