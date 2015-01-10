#include "stdafx.h"
#include "cASEObject.h"
#include "cMtlTex.h"

cASEObject::cASEObject():
m_pMesh(NULL),
m_pNodeMesh(NULL)
{
	D3DXMatrixIdentity(&m_matWorldTM);
	D3DXMatrixIdentity(&m_matLocalMat);
}


cASEObject::~cASEObject()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pNodeMesh);
}

void cASEObject::setup(stASENode& nodeinfo, D3DXMATRIXA16* pmatParentWorld/* = NULL*/){
	m_stNodeInfo = nodeinfo;		
	m_matWorldTM = nodeinfo.LocalMat;
	m_matOriginalWorld = nodeinfo.LocalMat;

	if (pmatParentWorld){
		D3DXMATRIXA16 mtPrnI;
		D3DXMatrixInverse(&mtPrnI, NULL, pmatParentWorld);
		m_matLocalMat = m_matWorldTM * mtPrnI;
	}
	else {
		D3DXMatrixIdentity(&m_matLocalMat);
	}	
	
	D3DXMATRIXA16 matInverse;
	D3DXMatrixInverse(&matInverse, NULL, &m_matWorldTM);

	for (size_t i = 0; i < m_stNodeInfo.vecVertex.size(); i++){
		D3DXVec3TransformCoord(
			&m_stNodeInfo.vecVertex[i].p,
			&m_stNodeInfo.vecVertex[i].p,
			&matInverse);
		D3DXVec3TransformNormal(
			&m_stNodeInfo.vecVertex[i].n,
			&m_stNodeInfo.vecVertex[i].n,
			&matInverse
			);
	}

	D3DXCreateSphere(g_pD3DDevice, 0.025f, 20, 20, &m_pNodeMesh, NULL);

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
	//	if (pmatParentWorld){
	//		D3DXMatrixInverse(&parentInv, NULL, pmatParentWorld);
	//		m_matLocalMat = m_matWorldTM * *pmatParentWorld;
	//	}
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
	//D3DXMATRIXA16 parentInv;
	
	if (pmatParentWorld){
		m_matWorldTM = m_matLocalMat * *pmatParentWorld;
	}

	for (auto p : m_vecChilds){
		p->update(delta, &m_matWorldTM);
	}
}

void cASEObject::render(std::vector<cMtlTex*>& vecMtl){
	D3DXMATRIX matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	if (GetKeyState(VK_SPACE) & 0x8000){
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	}

	if (GetKeyState(VK_TAB) & 0x8000){
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matOriginalWorld);
	}
	
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	if (m_pMesh){
		g_pD3DDevice->SetTexture(0, vecMtl[m_stNodeInfo.nRef]->pTex);
		g_pD3DDevice->SetMaterial(&vecMtl[m_stNodeInfo.nRef]->stMtl);
		m_pMesh->DrawSubset(m_stNodeInfo.nRef);
		m_pNodeMesh->DrawSubset(0);
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