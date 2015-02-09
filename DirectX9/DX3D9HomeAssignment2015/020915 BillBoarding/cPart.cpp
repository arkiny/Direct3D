#include "stdafx.h"
#include "cPart.h"


cPart::cPart()
	: m_pTexture(NULL)
	, m_fAngle(0.0f)
	, m_fXAngle(D3DXToRadian(240.0f))
	, m_fAngleSpeed(0.0f)
	, m_eState(E_STATE_IDLE)
{
	D3DXMatrixIdentity(&m_matPrevT);
	D3DXMatrixIdentity(&m_matRot);
	D3DXMatrixIdentity(&m_matPostT);
	D3DXMatrixIdentity(&m_matWorldTM);
}


cPart::~cPart()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pVertexBuffer);
}

void cPart::Setup(float fWidth, float fHeight, float fDepth, Cube_Part type){
	ST_PT_VERTEX v;
	D3DXMATRIXA16 matScale, matRotate, matTrans, matFinal;
	m_epart = type;

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
	else if (type == PT_arm_right || type == PT_fist){
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

	g_pD3DDevice->CreateVertexBuffer(
		m_vecVertex.size() * sizeof(ST_PT_VERTEX),
		D3DUSAGE_WRITEONLY,
		ST_PT_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_pVertexBuffer,
		0
		);

	ST_PT_VERTEX* buffv;
	m_pVertexBuffer->Lock(0, 0, (void**)&buffv, 0);

	memcpy(buffv, &m_vecVertex[0], m_vecVertex.size() * sizeof(ST_PT_VERTEX));

	//for (size_t i = 0; i < m_vecVertex.size(); i++){
	//	buffv[i] = m_vecVertex[i];
	//}
	
	m_pVertexBuffer->Unlock();
}

void cPart::Update(float delta, D3DXMATRIXA16* pmatParentWorld){
	
	
	if (m_eState == E_STATE_WALK){
		if (m_epart != PT_fist){
			m_fAngle += m_fAngleSpeed * delta;
			D3DXMatrixRotationX(&m_matRot, m_fAngle);
		}
	}
	else if (m_eState == E_STATE_ATTACK && m_epart == PT_arm_right){
		m_fXAngle -= D3DXToRadian(-360) * delta;
		D3DXMatrixRotationX(&m_matRot, m_fXAngle);
	}
	else {
		D3DXMatrixRotationX(&m_matRot, m_fAngle);
	}

	if (m_fAngle < -D3DX_PI / 4.0f)
	{
		m_fAngle = (-D3DX_PI / 4.0f);
		m_fAngleSpeed *= -1;
	}

	if (m_fAngle > D3DX_PI / 4.0f)
	{
		m_fAngle = (D3DX_PI / 4.0f);
		m_fAngleSpeed *= -1;
	}
	

	m_matWorldTM = m_matPrevT * m_matRot * m_matPostT;
	if (pmatParentWorld)
	{
		m_matWorldTM = m_matWorldTM * (*pmatParentWorld);
	}

	for each (auto p in m_vecChildren)
	{
		p->Update(delta, &m_matWorldTM);
	}
}

void cPart::Render(){
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	
	
	g_pD3DDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(ST_PT_VERTEX));
	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);

	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST,
		0,
		m_vecVertex.size()/3);

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	for each (auto p in m_vecChildren)
	{
		p->Render();
	}
}

void cPart::SetTexture(LPDIRECT3DTEXTURE9 pTexture){
	pTexture->AddRef();
	m_pTexture = pTexture;
}

void cPart::SetTransform(D3DXMATRIXA16& matPrevT, D3DXMATRIXA16& matPostT){
	m_matPrevT = matPrevT;
	m_matPostT = matPostT;
}

void cPart::AddChild(cPart* pChild){
	m_vecChildren.push_back(pChild);
}

void cPart::Destroy(){
	for each (auto p in m_vecChildren)
	{
		p->Destroy();
	}
	delete this;
}

void cPart::SetForcedAngle(float fAngle){
	m_fAngle = fAngle;
	for each (auto p in m_vecChildren)
	{
		p->SetForcedAngle(fAngle);
	}
}

void cPart::SetForcedXangle(float fAngle){
	m_fXAngle = fAngle;
	for each (auto p in m_vecChildren)
	{
		p->SetForcedXangle(fAngle);
	}
}

void cPart::SetState(eAnimationPT in){
	m_eState = in;
	for each (auto p in m_vecChildren)
	{
		p->SetState(in);
	}
}

D3DXVECTOR3 cPart::getTransformedCoord(){
	D3DXVECTOR3 ret;
	D3DXVec3TransformCoord(&ret, &m_vecVertex[32].p, &m_matWorldTM);
	return ret;
}