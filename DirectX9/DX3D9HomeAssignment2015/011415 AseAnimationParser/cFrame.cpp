#include "StdAfx.h"
#include "cFrame.h"
#include "cMtlTex.h"


cFrame::cFrame(void)
	: m_pMesh(NULL)
	, m_pMtlTex(NULL)
{
	D3DXMatrixIdentity(&m_matLocalTM);
	D3DXMatrixIdentity(&m_matWorldTM);
}


cFrame::~cFrame(void)
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMtlTex);
}

void cFrame::AddChild(cFrame* pChild)
{
	pChild->CalcLocalTM(&m_matWorldTM);
	m_vecChildren.push_back(pChild);
}

void cFrame::CalcLocalTM(D3DXMATRIXA16* pParent)
{
	D3DXMATRIXA16 matInvParent;
	D3DXMatrixInverse(&matInvParent, 0, pParent);
	m_matLocalTM = m_matWorldTM * matInvParent;
}

void cFrame::BuidlMesh(std::vector<ST_PNT_VERTEX>& vecVertex)
{
	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixInverse(&matInvWorld, 0, &m_matWorldTM);
	for (size_t i = 0; i < vecVertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&vecVertex[i].p, &vecVertex[i].p, &matInvWorld);
		D3DXVec3TransformNormal(&vecVertex[i].n, &vecVertex[i].n, &matInvWorld);
	}

	HRESULT hr = D3DXCreateMeshFVF(vecVertex.size() / 3,
		vecVertex.size(),
		D3DXMESH_MANAGED,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&m_pMesh);

	ST_PNT_VERTEX* pV = NULL;
	m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_pMesh->UnlockVertexBuffer();

	WORD* pI = NULL;
	m_pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	for (size_t i = 0; i < vecVertex.size(); ++i)
	{
		pI[i] = i;
	}
	m_pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	m_pMesh->LockAttributeBuffer(0, &pA);
	for (size_t i = 0; i < vecVertex.size() / 3; ++i)
	{
		pA[i] = 0;
	}
	m_pMesh->UnlockAttributeBuffer();

	std::vector<DWORD> vecAdjBuffer(vecVertex.size());
	m_pMesh->GenerateAdjacency(0.0f, &vecAdjBuffer[0]);

	m_pMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&vecAdjBuffer[0], 0, 0, 0);
}

void cFrame::SetMtlTex(cMtlTex* pMtlTex)
{
	if (!m_pMtlTex)
	{
		pMtlTex->AddRef();
		m_pMtlTex = pMtlTex;
	}
}

void cFrame::Update(D3DXMATRIXA16* pmatParent, float delta)
{
	//m_matWorldTM = m_matWorldTM * GetTranslationMatrixFromAnimation(delta);

	m_matWorldTM = m_matLocalTM;
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	
	GetRotationMatrixFromAnimation(delta, mat);
	GetTranslationMatrixFromAnimation(delta, mat);

	m_matWorldTM = mat;

	if (pmatParent)
		m_matWorldTM *= (*pmatParent);
	for each(auto pChild in m_vecChildren)
	{
		pChild->Update(&m_matWorldTM, delta);
	}
}

void cFrame::Render()
{
	if (m_pMtlTex)
	{
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
		g_pD3DDevice->SetTexture(0, m_pMtlTex->pTex);
		g_pD3DDevice->SetMaterial(&m_pMtlTex->stMtl);
		m_pMesh->DrawSubset(0);
	}

	for each(auto pChild in m_vecChildren)
	{
		pChild->Render();
	}
}

void cFrame::Destroy()
{
	for each(auto pChild in m_vecChildren)
	{
		pChild->Destroy();
	}
	delete this;
}



void cFrame::GetTranslationMatrixFromAnimation(float delta, D3DXMATRIXA16& mat){
	D3DXMATRIXA16 trans;
	if (m_stNodeAni.vTrs.size() > 2){
		int nextIndex = (m_nTrsIndex + 1) % m_stNodeAni.vTrs.size();
		int Index = m_nTrsIndex % m_stNodeAni.vTrs.size();
		float duration = (m_stNodeAni.vTrs[nextIndex].nf - m_stNodeAni.vTrs[Index].nf) / 640.0f;
		m_fTransAccum = m_fTransAccum + delta;
		float fUnit = m_fTransAccum / duration;
		

		D3DXVECTOR3 from(m_stNodeAni.vTrs[Index].x, m_stNodeAni.vTrs[Index].y, m_stNodeAni.vTrs[Index].z);
		D3DXVECTOR3 to(m_stNodeAni.vTrs[nextIndex].x, m_stNodeAni.vTrs[nextIndex].y, m_stNodeAni.vTrs[nextIndex].z);
		D3DXVECTOR3 moved;
		D3DXVec3Lerp(&moved, &from, &to, fUnit);
	

		if (m_fTransAccum > duration){
			m_fTransAccum = 0.0f;
			m_nTrsIndex++;
			if (m_nTrsIndex % m_stNodeAni.vTrs.size() == 0){
				m_nTrsIndex = 0;
			}
		}

		
		D3DXMatrixTranslation(&trans, moved.x, moved.y, moved.z);
		//m_matWorldTM *= trans;

		mat._41 = trans._41;
		mat._42 = trans._42;
		mat._43 = trans._43;
		mat._44 = trans._44;
		/*mat._11 = trans._11;
		mat._12 = trans._12;
		mat._13 = trans._13;
		mat._21 = trans._21;
		mat._22 = trans._22;
		mat._23 = trans._23;
		mat._31 = trans._31;
		mat._32 = trans._32;
		mat._33 = trans._33;*/
	}
	else if (m_stNodeAni.vTrs.size() == 1){
		D3DXMatrixTranslation(&trans, m_stNodeAni.vTrs[0].x, m_stNodeAni.vTrs[0].y, m_stNodeAni.vTrs[0].z);
		//m_fTransAccum += delta;
		//m_matWorldTM *= trans;
		mat._41 = trans._41;
		mat._42 = trans._42;
		mat._43 = trans._43;
		mat._44 = trans._44;
	}
	else if (m_stNodeAni.vTrs.size() == 0){
		//m_fTransAccum += delta;
		/*trans._11 = m_matLocalTM._11;
		trans._12 = m_matLocalTM._12;
		trans._13 = m_matLocalTM._13;
		trans._21 = m_matLocalTM._21;
		trans._22 = m_matLocalTM._22;
		trans._23 = m_matLocalTM._23;
		trans._31 = m_matLocalTM._31;
		trans._32 = m_matLocalTM._32;
		trans._33 = m_matLocalTM._33;*/

		mat._41 = m_matLocalTM._41;
		mat._42 = m_matLocalTM._42;
		mat._43 = m_matLocalTM._43;
		mat._44 = m_matLocalTM._44;
	}	
}

void cFrame::GetRotationMatrixFromAnimation(float delta, OUT D3DXMATRIXA16& mat){
	// Point total 4 sec
	// 640 1280 1920 2560 3200
	// frame from, frame to
	// 640 = 1sec, duration = (to - from) / 640
	// in quateronion -> m_fRotAccum shoulud < 1.0f

	_ASSERT(m_stNodeAni.vRot.size() == m_vecAccumRotQuat.size());

	if (m_stNodeAni.vRot.size() > 2){
		int nextIndex = (m_nRotIndex + 1) % m_stNodeAni.vRot.size();
		int Index = m_nRotIndex % m_stNodeAni.vRot.size();
		float duration = (m_stNodeAni.vRot[nextIndex].nf - m_stNodeAni.vRot[Index].nf) / 640.0f;
		
		m_fRotAccum = m_fRotAccum + delta;
		float fUnit = m_fRotAccum / duration;

		D3DXQUATERNION from = m_vecAccumRotQuat[Index];
		D3DXQUATERNION to = m_vecAccumRotQuat[nextIndex];
		D3DXQUATERNION moved;
		//FLOAT w = FLOAT(nFrame - pGeo->vRot[i].nF)/(pGeo->vRot[i+1].nF- pGeo->vRot[i].nF);

		D3DXQuaternionSlerp(&moved, &from, &to, fUnit);

		if (m_fRotAccum > duration){
			m_fRotAccum = 0.0f;
			m_nRotIndex++;
			if (m_nRotIndex % m_stNodeAni.vRot.size() == 0){
				m_nRotIndex = 0;
			}

			/*if (m_sNodeName == "Bip01 Spine"){
				int a = 0;
			}*/
			
		}

		D3DXMATRIXA16 rot;
		D3DXMatrixRotationQuaternion(&rot, &moved);

		mat._11 = rot._11;
		mat._12 = rot._12;
		mat._13 = rot._13;
		mat._21 = rot._21;
		mat._22 = rot._22;
		mat._23 = rot._23;
		mat._31 = rot._31;
		mat._32 = rot._32;
		mat._33 = rot._33;

	}
	else if (m_stNodeAni.vRot.size() == 1){
		D3DXMATRIXA16 rot;
		D3DXMatrixRotationQuaternion(&rot, &m_vecAccumRotQuat[0]);
		mat._11 = rot._11;
		mat._12 = rot._12;
		mat._13 = rot._13;
		mat._21 = rot._21;
		mat._22 = rot._22;
		mat._23 = rot._23;
		mat._31 = rot._31;
		mat._32 = rot._32;
		mat._33 = rot._33;
	}
	else if (m_stNodeAni.vRot.size() == 0){
		mat._11 = m_matLocalTM._11;
		mat._12 = m_matLocalTM._12;
		mat._13 = m_matLocalTM._13;
		mat._21 = m_matLocalTM._21;
		mat._22 = m_matLocalTM._22;
		mat._23 = m_matLocalTM._23;
		mat._31 = m_matLocalTM._31;
		mat._32 = m_matLocalTM._32;
		mat._33 = m_matLocalTM._33;
	}
}

void cFrame::CalcAccumRotTracks(){
	if (!m_stNodeAni.vRot.empty()){
		std::vector<stAseTrack>::iterator itr = m_stNodeAni.vRot.begin();
		float qx = itr->x * sin(itr->w / 2);
		float qy = itr->y * sin(itr->w / 2);
		float qz = itr->z * sin(itr->w / 2);
		float qw = cos(itr->w / 2);
		D3DXQUATERNION q = { qx, qy, qz, qw };
		m_vecAccumRotQuat.push_back(q);
		itr++;
		while (itr != m_stNodeAni.vRot.end()){
			qx = itr->x * sin(itr->w / 2);
			qy = itr->y * sin(itr->w / 2);
			qz = itr->z * sin(itr->w / 2);
			qw = cos(itr->w / 2);
			float x = m_vecAccumRotQuat.back().x;
			float y = m_vecAccumRotQuat.back().y;
			float z = m_vecAccumRotQuat.back().z;
			float w = m_vecAccumRotQuat.back().w;
			D3DXQUATERNION pred = { x, y, z, w};
			D3DXQUATERNION nq = { qx, qy, qz, qw };
			D3DXQUATERNION fq;
			D3DXQuaternionMultiply(&fq, &pred, &nq);
			m_vecAccumRotQuat.push_back(fq);
			itr++;
		}
	}
}

