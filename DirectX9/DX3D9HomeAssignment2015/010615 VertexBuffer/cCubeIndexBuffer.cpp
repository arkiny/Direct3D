#include "stdafx.h"
#include "cCubeIndexBuffer.h"


cCubeIndexBuffer::cCubeIndexBuffer()
	: m_pVertexBuffer(NULL),
	m_pIndexBuffer(NULL),
	m_vPosition(0, 2.0f, -10.0f),
	m_fSize(4.0f)
{
}


cCubeIndexBuffer::~cCubeIndexBuffer()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
}

void cCubeIndexBuffer::init(){

	// create vertex buffer
	g_pD3DDevice->CreateVertexBuffer(
		8 * sizeof(ST_PC_VERTEX),
		D3DUSAGE_WRITEONLY,
		ST_PC_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_pVertexBuffer,
		0
		);

	g_pD3DDevice->CreateIndexBuffer(
		36 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIndexBuffer,
		0);


	ST_PC_VERTEX* v;
	m_pVertexBuffer->Lock(0, 0, (void**)&v, 0);

	float left = -0.5f;
	float top = 0.5f;
	float right = 0.5f;
	float bottom = -0.5f;
	float frontdepth = 0.5f;
	float backdepth = -0.5f;

	v[0].p = D3DXVECTOR3(left, top, frontdepth);
	v[1].p = D3DXVECTOR3(right, top, frontdepth);
	v[2].p = D3DXVECTOR3(right, bottom, frontdepth);
	v[3].p = D3DXVECTOR3(left, bottom, frontdepth);
	v[4].p = D3DXVECTOR3(left, top, backdepth);
	v[5].p = D3DXVECTOR3(right, top, backdepth);
	v[6].p = D3DXVECTOR3(right, bottom, backdepth);
	v[7].p = D3DXVECTOR3(left, bottom, backdepth);

	for (int i = 0; i < 8; i++){
		v[i].c = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	}

	D3DXMATRIXA16 matScale;
	for (UINT i = 0; i < 8; i++){
		D3DXMatrixScaling(&matScale, m_fSize, m_fSize, m_fSize);
		D3DXVec3TransformCoord(&v[i].p, &v[i].p, &matScale);
	}

	m_pVertexBuffer->Unlock();

	WORD* indices = 0;
	
	m_pIndexBuffer->Lock(0, 0, (void**)&indices, 0);
	// front side
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;

	// back side
	indices[6] = 4; indices[7] = 6; indices[8] = 5;
	indices[9] = 4; indices[10] = 7; indices[11] = 6;

	// left side
	indices[12] = 4; indices[13] = 5; indices[14] = 1;
	indices[15] = 4; indices[16] = 1; indices[17] = 0;

	// right side
	indices[18] = 3; indices[19] = 2; indices[20] = 6;
	indices[21] = 3; indices[22] = 6; indices[23] = 7;

	// top
	indices[24] = 1; indices[25] = 5; indices[26] = 6;
	indices[27] = 1; indices[28] = 6; indices[29] = 2;

	// bottom
	indices[30] = 4; indices[31] = 0; indices[32] = 3;
	indices[33] = 4; indices[34] = 3; indices[35] = 7;

	m_pIndexBuffer->Unlock();
}

void cCubeIndexBuffer::update(float delta){
	//
}

void cCubeIndexBuffer::render(){
	D3DXMATRIXA16 matWorld, matT;
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matT);
//	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	
	g_pD3DDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(ST_PC_VERTEX));
	g_pD3DDevice->SetIndices(m_pIndexBuffer);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);

	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
		0, 0, 8, 0, 12);

	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
}