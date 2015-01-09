#include "stdafx.h"
#include "cASEObject.h"
#include "cMtlTex.h"

cASEObject::cASEObject():
m_pMesh(NULL)
{
	D3DXMatrixIdentity(&m_matWorldTM);
	D3DXMatrixIdentity(&m_matLocalMat);
}


cASEObject::~cASEObject()
{
	SAFE_RELEASE(m_pMesh);
}

void cASEObject::setup(stASENode& nodeinfo){
	m_stNodeInfo = nodeinfo;	

	
	m_matWorldTM = nodeinfo.LocalMat;
	D3DXMATRIXA16 matInverse;
	D3DXMatrixInverse(&m_matLocalMat, NULL, &m_matWorldTM);

	for (int i = 0; i < m_stNodeInfo.vecVertex.size(); i++){
		D3DXVec3TransformCoord(
			&m_stNodeInfo.vecVertex[i].p,
			&m_stNodeInfo.vecVertex[i].p,
			&m_matLocalMat);
		D3DXVec3TransformNormal(
			&m_stNodeInfo.vecVertex[i].n,
			&m_stNodeInfo.vecVertex[i].n,
			&m_matLocalMat
			);
	}

	if (m_stNodeInfo.nRef != INT_MAX){
		m_pMesh = NULL;
		HRESULT hr = D3DXCreateMeshFVF(m_stNodeInfo.vecVertex.size() / 3,
			m_stNodeInfo.vecVertex.size(),
			D3DXMESH_MANAGED,
			ST_PNT_VERTEX::FVF,
			g_pD3DDevice,
			&m_pMesh);

#ifdef _DEBUG
		_ASSERT(hr == S_OK && "Mesh Not Created");
#endif

		ST_PNT_VERTEX* pV = NULL;
		m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
		memcpy(pV, &m_stNodeInfo.vecVertex[0], m_stNodeInfo.vecVertex.size() * sizeof(ST_PNT_VERTEX));
		m_pMesh->UnlockVertexBuffer();

		WORD* pI = NULL;
		m_pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
		for (size_t j = 0; j < m_pMesh->GetNumVertices(); ++j)
		{
			pI[j] = j;
		}
		m_pMesh->UnlockIndexBuffer();

		DWORD* pA = NULL;
		m_pMesh->LockAttributeBuffer(0, &pA);
		for (size_t j = 0; j < m_pMesh->GetNumFaces(); j++){
			pA[j] = m_stNodeInfo.nRef;
		}
		m_pMesh->UnlockAttributeBuffer();

		std::vector<DWORD> vecAdjBuffer(m_stNodeInfo.vecVertex.size());
		m_pMesh->GenerateAdjacency(0.0f, &vecAdjBuffer[0]);

		m_pMesh->OptimizeInplace(
			D3DXMESHOPT_ATTRSORT |
			D3DXMESHOPT_COMPACT |
			D3DXMESHOPT_VERTEXCACHE,
			&vecAdjBuffer[0], 0, 0, 0);
	}
}

void cASEObject::update(float delta, D3DXMATRIXA16* pmatParentWorld/* = NULL*/){
	
	//for (int i = 0; i < m_stNodeInfo.vecVertex.size(); i++){
	//	D3DXVec3TransformCoord(
	//		&m_stNodeInfo.vecVertex[i].p,
	//		&m_stNodeInfo.vecVertex[i].p,
	//		&m_matWorldTM);
	//	D3DXVec3TransformNormal(
	//		&m_stNodeInfo.vecVertex[i].n,
	//		&m_stNodeInfo.vecVertex[i].n,
	//		&m_matWorldTM
	//		);
	//}

	for (auto p : m_vecChilds){
		p->update(delta, &m_matWorldTM);
	}
}

void cASEObject::render(std::vector<cMtlTex*>& vecMtl){
	if (GetKeyState(VK_SPACE) & 0x8000){
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	}
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	if (m_pMesh){
		g_pD3DDevice->SetTexture(0, vecMtl[m_stNodeInfo.nRef]->pTex);
		g_pD3DDevice->SetMaterial(&vecMtl[m_stNodeInfo.nRef]->stMtl);
		m_pMesh->DrawSubset(m_stNodeInfo.nRef);
	}
	for (auto p : m_vecChilds){
		p->render(vecMtl);
	}
}

void cASEObject::AddChild(cASEObject* pObj){
	m_vecChilds.push_back(pObj);
}

void cASEObject::destroy(){
	for (auto p : m_vecChilds){
		p->destroy();
	}
	delete this;
}