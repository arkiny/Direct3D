#include "stdafx.h"
#include "cASEObject.h"
#include "cMtlTex.h"

cASEObject::cASEObject() :
m_pMesh(NULL),
m_pNodeMesh(NULL),
m_fAngle(0.0f),
m_fXAngle(0.0f),
m_fAngleSpeed(1.0f)
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
	m_stNodeAni = nodeinfo.AnimationInfo;
	
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

	/*D3DXMATRIX mtA, mtT, mtF;
	D3DXMatrixIdentity(&mtA);
	D3DXMatrixIdentity(&mtT);
	size_t iSizeR = m_stNodeAni.vRot.size();
	size_t iSizeT = m_stNodeAni.vTrs.size();
	D3DXQUATERNION* q = NULL;
	D3DXVECTOR3* p = NULL;
	

	if (!m_stNodeAni.vTrs.empty()){
		p = (D3DXVECTOR3*)&m_stNodeAni.vTrs[nFrameT];
	}
	if (!m_stNodeAni.vRot.empty()){
		q = (D3DXQUATERNION*)&m_stNodeAni.vRot[nFrameR];
	}

	if (nFrameT >= iSizeT - 1 || nFrameT <= 0){
		nFrameUnitT *= -1;
	}
	if (nFrameR >= iSizeR - 1 || nFrameR <= 0){
		nFrameUnitR *= -1;
	}
	if (!m_stNodeAni.vTrs.empty()){
		nFrameT += nFrameUnitT;
		if (nFrameT <= 0){
			nFrameT = 0;
		}
		if (nFrameT >= iSizeT - 1){
			nFrameT = iSizeT - 1;
		}
	}
	if (!m_stNodeAni.vRot.empty()){
		nFrameR += nFrameUnitR;
		if (nFrameR <= 0){
			nFrameR = 0;
		}
		if (nFrameR >= iSizeR - 1){
			nFrameR = iSizeR - 1;
		}
	}

	if (q){
		D3DXMatrixRotationQuaternion(&mtA, q);
	}
	if (p){
		D3DXMatrixTranslation(&mtT, p->x, p->y, p->z);
	}

	mtF = mtT * mtA;*/

	//D3DXMATRIX mtR, mtT, mtF;
	//D3DXMatrixIdentity(&mtR);
	//D3DXMatrixIdentity(&mtT);
	//if (!m_stNodeAni.vTrs.empty()){
	//	D3DXVECTOR3 axis(m_stNodeAni.vTrs[0].x, m_stNodeAni.vTrs[0].y, m_stNodeAni.vTrs[0].z);
	//	D3DXMatrixRotationAxis(&mtR, &axis, m_stNodeAni.vTrs[0].w);
	//}
	////D3DXMatrixRotationX(&mtA, D3DXToRadian(1.0f));
	//mtF = mtR * mtT;
	//m_matLocalMat = m_matLocalMat * mtF;
	D3DXMATRIX mtR, mtT;
	D3DXMatrixIdentity(&mtR);
	if (m_stNodeInfo.NodeName == "Bip01RUpperArm" ){
		m_fAngle += m_fAngleSpeed * delta;
		D3DXMatrixRotationX(&mtR, D3DXToRadian(m_fAngle));
		
	}
	else if (m_stNodeInfo.NodeName == "Bip01LUpperArm" ||
		m_stNodeInfo.NodeName == "Bip01RThigh"){
		m_fAngle += m_fAngleSpeed * delta;
		D3DXMatrixRotationX(&mtR, D3DXToRadian(m_fAngle));
	}
	else if (m_stNodeInfo.NodeName == "Bip01LThigh"){
		m_fAngle += m_fAngleSpeed * delta;
		D3DXMatrixRotationY(&mtR, D3DXToRadian(m_fAngle));
	}
	else if (m_stNodeInfo.NodeName == "Bip01RThigh"){
		m_fAngle += m_fAngleSpeed * delta;
		D3DXMatrixRotationY(&mtR, D3DXToRadian(m_fAngle));
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


	m_matLocalMat = m_matLocalMat * mtR;
	
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

	if (GetKeyState(VK_SHIFT) & 0x8000){
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
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