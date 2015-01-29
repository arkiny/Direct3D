#include "stdafx.h"
#include "cHeightMap.h"
#include "cMtlTex.h"
#include "cRawLoader.h"
#include "cTextureManager.h"


cHeightMap::cHeightMap()
{
	m_pTransform->SetPosition(D3DXVECTOR3(0, 0, 0));
}


cHeightMap::~cHeightMap()
{
	SAFE_RELEASE(m_pMtlTex);
	SAFE_RELEASE(m_pMesh);
}

void cHeightMap::Setup(){
	cRawLoader rawLoader;
	std::string sFolder("../Resource/HeightMapData/");
	std::string sFile("HeightMap.raw");
	rawLoader.LoadRawData(sFolder, sFile, m_vecHeight);

	m_vecVertex.resize(257 * 257);
	for (int i = 0; i < 257; i++){
		for (int j = 0; j < 257; j++){
			m_vecVertex[(i * 257) + j].p = D3DXVECTOR3((float)j, (float)(m_vecHeight[((256-i) * 257) + j]/10.0f - 50.0f), (float)i);
			m_vecVertex[(i * 257) + j].t = D3DXVECTOR2(j / 257.0f, (257.0f-i) / 257.0f);
			m_vecVertex[(i * 257) + j].n = D3DXVECTOR3(0,1,0);
			/*m_vecVertex[(i * 257) + j].p = D3DXVECTOR3((float)j, (float)(m_vecHeight[((i * 257) + j)] / 10.0f - 50.0f), (float)i);
			m_vecVertex[(i * 257) + j].t = D3DXVECTOR2(j / 257.0f, i / 257.0f);*/
		}
	}
	
	for (int z = 1; z < 256; z++){
		for (int x = 1; x < 256; x++){
			D3DXVECTOR3 normal;

			D3DXVECTOR3 xaxisplus = m_vecVertex[(z * 257) + (x + 1)].p;
			D3DXVECTOR3 xaxisMinus = m_vecVertex[(z * 257) + (x - 1)].p;
			D3DXVECTOR3 xaxis = xaxisplus - xaxisMinus;

			D3DXVECTOR3 zaxisplus = m_vecVertex[((z + 1) * 257) + x].p;
			D3DXVECTOR3 zaxisMinus = m_vecVertex[((z - 1) * 257) + x].p;
			D3DXVECTOR3 zaxis = zaxisplus - zaxisMinus ;

			D3DXVec3Cross(&normal, &zaxis, &xaxis);
			D3DXVec3Normalize(&normal, &normal);
			m_vecVertex[(z * 257) + x].n = normal;
		}
	}

	//for (int z = 0; z < 256; z++){
	//	for (int x = 0; x < 256; x++){
	//		D3DXVECTOR3 normal;
	//		D3DXVECTOR3 xaxis = m_vecVertex[(z * 257) + x].p - m_vecVertex[(z * 257) + (x + 1)].p;
	//		D3DXVECTOR3 zaxis = m_vecVertex[(z * 257) + x].p - m_vecVertex[((z + 1) * 257) + x].p;
	//		D3DXVec3Cross(&normal, &xaxis, &zaxis);
	//		D3DXVec3Normalize(&normal, &normal);
	//		m_vecVertex[(z * 257) + x].n = normal;
	//	}
	//}
	
	//m_vecIndex.push_back(x % 257 + z * 257);
	//m_vecIndex.push_back(z * 257);

	//m_vecIndex.push_back(x % 257);
	//m_vecIndex.push_back(x % 257 + z * 257);
	//m_vecIndex.push_back(x % 257 + z * 257);

	// for 256
	// index size;
	m_vecIndex.resize(256 * 256 * 6);
	int index = 0;
	for (int z = 0; z < 256; z++){
		for (int x = 0; x < 256; x++){
			m_vecIndex[index++] = ((x + 0) + ((z + 0) * 257));
			m_vecIndex[index++] = ((x + 0) + ((z + 1) * 257));
			m_vecIndex[index++] = ((x + 1) + ((z + 1) * 257));
					   
			m_vecIndex[index++] = ((x + 0) + ((z + 0) * 257));
			m_vecIndex[index++] = ((x + 1) + ((z + 1) * 257));
			m_vecIndex[index++] = ((x + 1) + ((z + 0) * 257));
		}
	}
	// 0, 257, 258
	// 0, 1, 258	

	m_pMtlTex = new cMtlTex;
	m_pMtlTex->stMtl.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_pMtlTex->stMtl.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_pMtlTex->stMtl.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_pMtlTex->pTex = g_pTextureManager->GetTexture("../Resource/HeightMapData/terrain.jpg");

	DWORD vertexnum = m_vecVertex.size();
	DWORD faceNum = m_vecIndex.size() / 3;
	HRESULT hr = D3DXCreateMeshFVF(
		faceNum,
		vertexnum,
		D3DXMESH_32BIT || D3DXMESH_MANAGED,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&m_pMesh);

	_ASSERT(hr == S_OK);
	/*
	ST_PT_VERTEX* buffv;

	memcpy(buffv, &m_vecVertex[0], m_vecVertex.size() * sizeof(ST_PT_VERTEX));*/

	ST_PNT_VERTEX* v = 0;
	m_pMesh->LockVertexBuffer(0, (void**)&v);
	//for (int i = 0; i < vecVertices.size(); i++){
	//	v[i] = vecVertices[i];
	//}
	memcpy(v, &m_vecVertex[0], m_vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_pMesh->UnlockVertexBuffer();

	DWORD* di = 0;
	m_pMesh->LockIndexBuffer(0, (void**)&di);
	//std::vector<int> check;
	memcpy(di, &m_vecIndex[0], m_vecIndex.size() * sizeof(DWORD));

	m_pMesh->UnlockIndexBuffer();

	DWORD* attributeBuffer = 0;
	m_pMesh->LockAttributeBuffer(0, &attributeBuffer);

	int j = 0;
	memset(&attributeBuffer[0], 0,m_pMesh->GetNumFaces()*sizeof(DWORD));
	m_pMesh->UnlockAttributeBuffer();

	/*for (UINT i = 0; i < m_pMesh->GetNumFaces(); i++){
	attributeBuffer[i] = 0;
	}*/
	std::vector<DWORD> adjacencyBuffer(m_vecIndex.size());
	int size = m_pMesh->GetNumFaces() * 3;
	m_pMesh->GenerateAdjacency(0.0f, &adjacencyBuffer[0]);

	hr = m_pMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&adjacencyBuffer[0],
		0, 0, 0);
}

void cHeightMap::Update(float delta){

}

void cHeightMap::Render(){
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	//D3DXMatrixRotationX(&mat, D3DXToRadian(180.0f));
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);

	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	
	if (GetAsyncKeyState(VK_TAB) && 0x8000){
		g_pD3DDevice->SetTexture(0, NULL);
	}
	else {
		g_pD3DDevice->SetTexture(0, m_pMtlTex->pTex);
	}
	g_pD3DDevice->SetMaterial(&m_pMtlTex->stMtl);
	m_pMesh->DrawSubset(0);
}

float cHeightMap::GetHeight(OUT bool& isLand, IN D3DXVECTOR3* pvPosition){
	int xIndex = static_cast<int>(floorf(pvPosition->x));
	int zIndex = static_cast<int>(floorf(pvPosition->z));
	if (xIndex < 0 || zIndex < 0 || xIndex >= 256 || zIndex >= 256){
		isLand = false;
		return 0.0f;
	}
	D3DXVECTOR3 lb = m_vecVertex[(zIndex * 257) + (xIndex)].p;
	D3DXVECTOR3 lt = m_vecVertex[((zIndex + 1) * 257) + (xIndex)].p;
	D3DXVECTOR3 rt = m_vecVertex[((zIndex + 1) * 257) + ((xIndex + 1))].p;
	D3DXVECTOR3 rb = m_vecVertex[((zIndex * 257) + (xIndex + 1))].p;

	if ((pvPosition->x - xIndex) + (pvPosition->z - zIndex) <= 1){
		D3DXVECTOR3 zVector = lt - lb;
		D3DXVECTOR3 xVector = rb - lb;
		float z = (pvPosition->z - zIndex) / zVector.z;
		zVector = zVector * z;
		float x = (pvPosition->x - xIndex) / xVector.x;
		xVector = xVector * x;
		D3DXVECTOR3 nPos = lb + zVector + xVector;
		pvPosition->y = nPos.y;
		return nPos.y;
	}
	else {
		D3DXVECTOR3 xVector = lt - rt;
		D3DXVECTOR3 zVector = rb - rt;

		float z = 1.0f + (pvPosition->z - zIndex) / zVector.z;
		zVector = zVector * z;
		float x = 1.0f + (pvPosition->x - xIndex) / xVector.x;
		xVector = xVector * x;

		D3DXVECTOR3 nPos = rt + zVector + xVector;
		pvPosition->y = nPos.y;
		return 0.0f;
	}
	return 0.0f;
}