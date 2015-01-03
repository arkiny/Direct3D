#include "stdafx.h"
#include "cPyramid.h"


cPyramid::cPyramid()
{
}


cPyramid::~cPyramid()
{
}

void cPyramid::setup(){
	// pyramid
	std::vector<ST_PN_VERTEX> original_payrimid;
	ST_PN_VERTEX v;

	v.p = D3DXVECTOR3(0, 0, 0);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(1, -4, -1);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(-1, -4, -1);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(0, 0, 0);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(1, -4, 1);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(1, -4, -1);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(0, 0, 0);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(-1, -4, 1);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(1, -4, 1);
	original_payrimid.push_back(v);


	v.p = D3DXVECTOR3(0, 0, 0);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(-1, -4, -1);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(-1, -4, 1);
	original_payrimid.push_back(v);


	v.p = D3DXVECTOR3(-1, -4, -1);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(1, -4, -1);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(-1, -4, 1);
	original_payrimid.push_back(v);


	v.p = D3DXVECTOR3(1, -4, -1);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(1, -4, 1);
	original_payrimid.push_back(v);

	v.p = D3DXVECTOR3(-1, -4, 1);
	original_payrimid.push_back(v);

	D3DXMATRIXA16 matRotate;
	D3DXMATRIXA16 matScaling;
	D3DXMATRIXA16 matFinal;
	D3DXVECTOR4 new_vec4;
	D3DXMatrixScaling(&matScaling, 0.2f, 0.2f, 0.2f);
	for (UINT i = 0; i < original_payrimid.size(); i++){
		//
		D3DXVec3Transform(&new_vec4, &original_payrimid[i].p, &matScaling);
		original_payrimid[i].p = D3DXVECTOR3(new_vec4.x, new_vec4.y, new_vec4.z);
	}
	m_vecVertexLineYPyramid = original_payrimid;

	D3DXMatrixRotationZ(&matRotate, D3DXToRadian(90.0f));

	matFinal = matRotate;
	for (UINT i = 0; i < original_payrimid.size(); i++){
		//
		D3DXVec3Transform(&new_vec4, &original_payrimid[i].p, &matFinal);
		original_payrimid[i].p = D3DXVECTOR3(new_vec4.x, new_vec4.y, new_vec4.z);
	}
	m_vecVertexLineXPyramid = original_payrimid;

	D3DXMatrixIdentity(&matRotate);
	D3DXMatrixRotationY(&matRotate, D3DXToRadian(90.0f));
	for (UINT i = 0; i < original_payrimid.size(); i++){
		//
		D3DXVec3Transform(&new_vec4, &original_payrimid[i].p, &matRotate);
		original_payrimid[i].p = D3DXVECTOR3(new_vec4.x, new_vec4.y, new_vec4.z);
	}
	m_vecVertexLineZPyramid = original_payrimid;
	//m_vecVertexLineZPyramid;*/
}

void cPyramid::render(){

}