#include "StdAfx.h"
#include "cSkinnedMesh.h"
#include "cAllocateHierarchy.h"
#include "cMtlTex.h"
#include "cAnimationSet.h"

cSkinnedMesh::cSkinnedMesh(void)
	: m_pRootFrame(NULL)
	, m_fAnimationBlendTime(0.3f)
	, m_fPassedBlendTime(0.0f)
	, m_isAnimationBlending(false)
	, m_nCurrentAnimation(0)
{
}


cSkinnedMesh::~cSkinnedMesh(void)
{
	if (m_pRootFrame)
	{
		cAllocateHierarchy Alloc;
		D3DXFrameDestroy(m_pRootFrame, &Alloc);
	}
}

void cSkinnedMesh::Setup(std::string sFolder, std::string sFile)
{
	cAllocateHierarchy Alloc;
	Alloc.SetFolder(sFolder);
	D3DXLoadMeshHierarchyFromX(
		(sFolder + sFile).c_str(),
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&Alloc,
		NULL,
		&m_pRootFrame,
		&m_pAnimControl);
	UINT uiNumAnim = m_pAnimControl->GetNumAnimationSets();
	for (UINT i = 0; i < uiNumAnim; ++i)
	{
		cAnimationSet* pAnimSet = new cAnimationSet;
		LPD3DXANIMATIONSET pAS = NULL;
		m_pAnimControl->GetAnimationSet(i, &pAS);
		pAnimSet->SetAnimationSet(pAS);
		SAFE_RELEASE(pAS);
		pAnimSet->SetIndex(m_vecAnimationSet.size());
		m_vecAnimationSet.push_back(pAnimSet);
	}

	SetupBoneMatrixPtrs(m_pRootFrame);
}

void cSkinnedMesh::Update(float delta)
{
	m_vecAnimationSet[m_nCurrentAnimation]->Update(delta);

	if (m_isAnimationBlending)
	{
		m_fPassedBlendTime += delta;
		if (m_fPassedBlendTime >= m_fAnimationBlendTime)
		{
			m_isAnimationBlending = false;
			m_pAnimControl->SetTrackWeight(0, 1.0f);
			m_pAnimControl->SetTrackWeight(1, 0.0f);
			m_pAnimControl->SetTrackEnable(1, false);
		}
		else
		{
			float fWeight = m_fPassedBlendTime / m_fAnimationBlendTime;
			m_pAnimControl->SetTrackWeight(0, fWeight);
			m_pAnimControl->SetTrackWeight(1, 1.0f - fWeight);
		}
	}
	m_pAnimControl->AdvanceTime(delta, NULL);

	//if (rootMat){
	//	m_pRootFrame->TransformationMatrix = *rootMat;
	//}

	UpdateWorldMatrix(m_pRootFrame, NULL);
	UpdateSkinnedMesh(m_pRootFrame);
}

void cSkinnedMesh::Render(D3DXMATRIXA16* pParentWorldTM)
{
	D3DXMATRIXA16 mati;
	D3DXMatrixIdentity(&mati);
	Render(m_pRootFrame, pParentWorldTM);
}


void cSkinnedMesh::UpdateWorldMatrix(D3DXFRAME* pFrame, D3DXMATRIXA16* pmatParent)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	pBone->matWorldTM = pBone->TransformationMatrix;

	if (pmatParent)
	{
		pBone->matWorldTM = pBone->matWorldTM * (*pmatParent);
	}

	if (pBone->pFrameSibling)
	{
		UpdateWorldMatrix(pBone->pFrameSibling, pmatParent);
	}
	if (pBone->pFrameFirstChild)
	{
		UpdateWorldMatrix(pBone->pFrameFirstChild, &pBone->matWorldTM);
	}
}

void cSkinnedMesh::Render(D3DXFRAME* pFrame, D3DXMATRIXA16* pParentWorldTM)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	/*D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);*/

	pBone->matWorldTM = (pFrame->TransformationMatrix) * (*pParentWorldTM);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &pBone->matWorldTM);

	if (pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		for (size_t i = 0; i < pBoneMesh->dwNumSubset; ++i)
		{
			g_pD3DDevice->SetTexture(0, pBoneMesh->vecMtlTex[i]->pTex);
			g_pD3DDevice->SetMaterial(&pBoneMesh->vecMtlTex[i]->stMtl);
			pBoneMesh->MeshData.pMesh->DrawSubset(i);
		}
	}
	if (pBone->pFrameSibling)
	{
		Render(pBone->pFrameSibling, pParentWorldTM);
	}

	if (pBone->pFrameFirstChild)
	{
		Render(pBone->pFrameFirstChild, &pBone->matWorldTM);
	}
}

void cSkinnedMesh::SetAnimationIndex(DWORD dwIndex)
{
	if (dwIndex >= m_vecAnimationSet.size())
		return;

	cAnimationSet* pCurr = m_vecAnimationSet[m_nCurrentAnimation];
	cAnimationSet* pNext = m_vecAnimationSet[dwIndex];
	if (pNext->GetIsLoop())
	{
		SetAnimationIndexBlend(dwIndex);
	}
	else
	{
		pNext->SetDelegate(this);
		pNext->SetPrevAnimation(pCurr);
		pNext->Start();
		SetAnimationIndexBlend(dwIndex);
	}
	m_nCurrentAnimation = dwIndex;
}

void cSkinnedMesh::SetAnimationIndexBlend(DWORD dwIndex)
{
	LPD3DXANIMATIONSET pPrev = NULL;
	LPD3DXANIMATIONSET pNext = NULL;

	m_pAnimControl->GetAnimationSet(dwIndex, &pNext);
	if (!pNext)
	{
		return;
	}
	m_pAnimControl->GetTrackAnimationSet(0, &pPrev);

	D3DXTRACK_DESC desc;
	m_pAnimControl->GetTrackDesc(0, &desc);
	m_pAnimControl->SetTrackDesc(1, &desc);

	m_pAnimControl->SetTrackWeight(0, 0.0f);
	m_pAnimControl->SetTrackWeight(1, 1.0f);

	m_pAnimControl->SetTrackAnimationSet(0, pNext);
	m_pAnimControl->SetTrackAnimationSet(1, pPrev);

	SAFE_RELEASE(pPrev);
	SAFE_RELEASE(pNext);

	m_fPassedBlendTime = 0.0f;
	m_isAnimationBlending = true;
}

void cSkinnedMesh::UpdateRootMatrix(D3DXMATRIXA16* rootMatrix){
	m_pRootFrame->TransformationMatrix = m_pRootFrame->TransformationMatrix * *rootMatrix;
}

void cSkinnedMesh::SetAnimationLoop(DWORD dwIndex, bool isLoop)
{
	if (dwIndex < m_vecAnimationSet.size())
	{
		m_vecAnimationSet[dwIndex]->SetIsLoop(isLoop);
	}
}

void cSkinnedMesh::SetupBoneMatrixPtrs(D3DXFRAME* pFrame)
{
	// 각 프레임의 메시 컨테이너에 있는 pSkinInfo를 이용하여 영향받는 모든 
	// 프레임의 매트릭스를 ppBoneMatrixPtrs에 연결한다.

	if (pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;
		if (pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			// pSkinInfo->GetNumBones() 으로 영향받는 본의 개수를 찾음.
			// pSkinInfo->GetNumBones() 으로 영향받는 본의 개수를 찾음.
			// pSkinInfo->GetBoneName(i) 로 i번 프레임의 이름을 찾음
			// D3DXFrameFind(루트 프레임, 프레임 이름) 로 프레임을 찾음.
			// 찾아서 월드매트릭스를 걸어줘라.
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				ST_BONE* pBone = (ST_BONE*)D3DXFrameFind(m_pRootFrame, pSkinInfo->GetBoneName(i));
				pBoneMesh->ppBoneMatrixPtrs[i] = &pBone->matWorldTM;
			}
		}
	}

	ST_BONE* pBone = (ST_BONE*)pFrame;
	//재귀적으로 모든 프레임에 대해서 실행.
	if (pBone->pFrameSibling)
	{
		SetupBoneMatrixPtrs(pBone->pFrameSibling);
	}

	if (pBone->pFrameFirstChild)
	{
		SetupBoneMatrixPtrs(pBone->pFrameFirstChild);
	}
}

void cSkinnedMesh::UpdateSkinnedMesh(D3DXFRAME* pFrame)
{
	if (pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;
		if (pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				// pCurrentBoneMatrices 를 계산하시오
				// pCurrentBoneMatrices = pBoneOffsetMatrices * ppBoneMatrixPtrs 

				pBoneMesh->pCurrentBoneMatrices[i] =
					pBoneMesh->pBoneOffsetMatrices[i] * *(pBoneMesh->ppBoneMatrixPtrs[i]);
			}

			BYTE* src = NULL;
			BYTE* dest = NULL;

			pBoneMesh->pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&src);
			pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (void**)&dest);

			//MeshData.pMesh을 업데이트 시켜준다.
			pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
				pBoneMesh->pCurrentBoneMatrices, NULL, src, dest);

			pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
			pBoneMesh->pOrigMesh->UnlockVertexBuffer();
		}
	}

	ST_BONE* pBone = (ST_BONE*)pFrame;
	//재귀적으로 모든 프레임에 대해서 실행.
	if (pBone->pFrameSibling)
	{
		UpdateSkinnedMesh(pBone->pFrameSibling);
	}

	if (pBone->pFrameFirstChild)
	{
		UpdateSkinnedMesh(pBone->pFrameFirstChild);
	}
}

void cSkinnedMesh::OnFinishAnimation(cAnimationSet* pSender)
{
	SetAnimationIndex(pSender->GetPrevAnimation()->GetIndex());
}


//cSkinnedMesh::cSkinnedMesh(void)
//	: m_pRootFrame(NULL),
//	m_bAttack(false),
//	m_fAnimationBlendTime(0.3f),
//	m_fPassedBlendTime(0.0f),
//	m_bisAnimationBlending(false)
//{
//}
//
//
//cSkinnedMesh::~cSkinnedMesh(void)
//{
//	if (m_pRootFrame)
//	{
//		cAllocateHierarchy Alloc;
//		D3DXFrameDestroy(m_pRootFrame, &Alloc);
//	}
//	SAFE_RELEASE(m_pAnimControl);
//}
//
//void cSkinnedMesh::Setup(std::string sFolder, std::string sFile)
//{
//	cAllocateHierarchy Alloc;
//	Alloc.SetFolder(sFolder);
//	D3DXLoadMeshHierarchyFromX(
//		(sFolder + sFile).c_str(),
//		D3DXMESH_MANAGED,
//		g_pD3DDevice,
//		&Alloc,
//		NULL,
//		&m_pRootFrame,
//		&m_pAnimControl);
//
//	//	
//	SetupBoneMatrixPtrs(m_pRootFrame);
//	SetAnimationIndex(IDLE);
//	//
//}
//
//void cSkinnedMesh::Render()
//{
//	Render(m_pRootFrame);
//}
//
//void cSkinnedMesh::Update(float delta){
//	
//
//	if (m_bisAnimationBlending){
//		m_fPassedBlendTime += delta;
//		if (m_fPassedBlendTime >= m_fAnimationBlendTime){
//			m_bisAnimationBlending = false;
//			m_pAnimControl->SetTrackWeight(0, 1.0f);
//			m_pAnimControl->SetTrackWeight(1, 0.0f);
//			m_pAnimControl->SetTrackEnable(1, false);
//		}
//		else {
//
//		}
//	}
//
//	m_fActionTime += delta;
//	m_pAnimControl->AdvanceTime(delta, NULL);
//	UpdateSkinnedMesh(m_pRootFrame);
//	ChangeAnimation(delta);
//
//
//	LPD3DXANIMATIONSET pAnimationSet = NULL;
//	if (m_eCurrentStatus == ATTACK1 || m_eCurrentStatus == ATTACK2 || m_eCurrentStatus == ATTACK3 ||
//		m_eNextStatus == ATTACK1 || m_eNextStatus == ATTACK2 || m_eNextStatus == ATTACK3){
//		m_bAttack = false;
//		m_fAccumTime += delta;
//
//		if (m_eCurrentStatus == ATTACK1 || m_eCurrentStatus == ATTACK2 || m_eCurrentStatus == ATTACK3){
//			m_pAnimControl->GetAnimationSet(m_eCurrentStatus, &pAnimationSet);
//		}
//		else {
//			m_pAnimControl->GetAnimationSet(m_eNextStatus, &pAnimationSet);
//		}
//
//		float curTime = (float)m_pAnimControl->GetTime();
//		float curPer = (float)pAnimationSet->GetPeriod();
//
//		if (m_fAccumTime > curPer*.3f){
//			m_bAttack = true;
//		}
//		if (m_fAccumTime > curPer*.5f){
//			m_bAttack = false;
//		}
//
//		if (m_fAccumTime > curPer){
//		//	m_pAnimControl->ResetTime();
//			m_fAccumTime = 0.0f;
//		}
//	}
//	else{
//		m_fAccumTime = 0.0f;
//	}
//	SAFE_RELEASE(pAnimationSet);
//
//
//	if (!m_bIsTransferAnimation){
//		m_eNextStatus = IDLE;
//		if (GetKeyState('W') & 0x8000){
//			m_eNextStatus = WALKING;
//		}
//		if (GetKeyState('1') & 0x8000){
//			m_eNextStatus = ATTACK1;
//			m_bInAction = true;
//		}
//		if (GetKeyState('2') & 0x8000){
//			m_eNextStatus = ATTACK2;
//			m_bInAction = true;
//		}
//		if (GetKeyState('3') & 0x8000){
//			m_eNextStatus = ATTACK3;
//			m_bInAction = true;
//		}
//	}
//}
//
//void cSkinnedMesh::SetAnimationBlend(DWORD dwIndex){
//	LPD3DXANIMATIONSET pPrev = NULL;
//	LPD3DXANIMATIONSET pNext = NULL;
//	
//	m_pAnimControl->GetTrackAnimationSet(0, &pPrev);
//	m_pAnimControl->GetAnimationSet(dwIndex, &pNext);
//	
//	if (!pNext)
//	{
//		return;
//	}
//
//	m_pAnimControl->GetTrackAnimationSet(0, &pPrev);
//	D3DXTRACK_DESC desc;
//	m_pAnimControl->GetTrackDesc(0, &desc);
//	m_pAnimControl->SetTrackDesc(1, &desc);
//	m_pAnimControl->SetTrackWeight(1, 1.0f);
//	m_pAnimControl->SetTrackWeight(0, 0.0f);
//	m_pAnimControl->SetTrackAnimationSet(0, pNext);
//	m_pAnimControl->SetTrackAnimationSet(1, pPrev);
//
//	
//	m_fPassedBlendTime = 0.0f;
//	m_bisAnimationBlending = true;
//
//	SAFE_RELEASE(pNext);
//	SAFE_RELEASE(pPrev);
//}
//
//void cSkinnedMesh::SetupWorldMatrix(D3DXFRAME* pFrame, D3DXMATRIXA16* pmatParent)
//{
//	ST_BONE* pBone = (ST_BONE*)pFrame;
//	//pBone->matWorldTM =  *(*pmatParent);
//
//	if (pmatParent)
//	{
//		pBone->matWorldTM = pBone->TransformationMatrix * (*pmatParent);
//	}
//	else {
//		pBone->matWorldTM = pBone->TransformationMatrix;
//	}
//
//	if (pBone->pFrameSibling)
//	{
//		SetupWorldMatrix(pBone->pFrameSibling, pmatParent);
//	}
//	if (pBone->pFrameFirstChild)
//	{
//		SetupWorldMatrix(pBone->pFrameFirstChild, &pBone->matWorldTM);
//	}
//}
//
//void cSkinnedMesh::Render(D3DXFRAME* pFrame)
//{
//	ST_BONE* pBone = (ST_BONE*)pFrame;
//	
//	/*D3DXMATRIXA16 worldmat = pBone->TransformationMatrix;
//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &worldmat);*/
//	g_pD3DDevice->SetTransform(D3DTS_WORLD, &pBone->matWorldTM);
//	if (pBone->pMeshContainer)
//	{
//		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
//		for (size_t i = 0; i < pBoneMesh->dwNumSubset; ++i)
//		{		
//			g_pD3DDevice->SetTexture(0, pBoneMesh->vecMtlTex[i]->pTex);
//			g_pD3DDevice->SetMaterial(&pBoneMesh->vecMtlTex[i]->stMtl);
//			pBoneMesh->MeshData.pMesh->DrawSubset(i);
//		}
//	}
//	if (pBone->pFrameSibling)
//	{
//		Render(pBone->pFrameSibling);
//	}
//
//	if (pBone->pFrameFirstChild)
//	{
//		Render(pBone->pFrameFirstChild);
//	}
//}
//
//void cSkinnedMesh::ChangeAnimation(float fTime){
//	if (m_eNextStatus != m_eCurrentStatus ){
//		m_fChangeTime += fTime*5.0f;
//		m_pAnimControl->SetTrackEnable(0, true);
//		m_pAnimControl->SetTrackEnable(1, true);
//		LPD3DXANIMATIONSET pAnimationSetPrev = NULL;
//		LPD3DXANIMATIONSET pAnimationSetNext = NULL;
//		
//		if (!m_bIsTransferAnimation){
//			if (m_dwCurrentTrack == 0){
//				m_pAnimControl->GetAnimationSet(m_eCurrentStatus, &pAnimationSetPrev);
//				m_pAnimControl->SetTrackAnimationSet(0, pAnimationSetPrev);
//				m_pAnimControl->GetAnimationSet(m_eNextStatus, &pAnimationSetNext);
//				m_pAnimControl->SetTrackAnimationSet(1, pAnimationSetNext);
//
//				float a = (float)pAnimationSetPrev->GetPeriod() / (float)pAnimationSetNext->GetPeriod();
//				float b = (float)pAnimationSetNext->GetPeriod() / (float)pAnimationSetPrev->GetPeriod();
//
//				m_pAnimControl->SetTrackSpeed(0, a);
//				m_pAnimControl->SetTrackSpeed(1, b);
//				D3DXTRACK_DESC desA;
//				D3DXTRACK_DESC desB;
//				m_pAnimControl->GetTrackDesc(0, &desA);
//				m_pAnimControl->GetTrackDesc(1, &desB);
//				//desA.Position = 0.0;
//				desB.Position = 0.0;
//				m_pAnimControl->SetTrackDesc(0, &desA);
//				m_pAnimControl->SetTrackDesc(1, &desB);
//			}
//			else {
//				m_pAnimControl->GetAnimationSet(m_eCurrentStatus, &pAnimationSetPrev);
//				m_pAnimControl->SetTrackAnimationSet(1, pAnimationSetPrev);
//				m_pAnimControl->GetAnimationSet(m_eNextStatus, &pAnimationSetNext);
//				m_pAnimControl->SetTrackAnimationSet(0, pAnimationSetNext);
//
//				float a = (float)pAnimationSetPrev->GetPeriod() / (float)pAnimationSetNext->GetPeriod();
//				float b = (float)pAnimationSetNext->GetPeriod() / (float)pAnimationSetPrev->GetPeriod();
//
//				m_pAnimControl->SetTrackSpeed(0, b);
//				m_pAnimControl->SetTrackSpeed(1, a);
//
//				D3DXTRACK_DESC desA;
//				D3DXTRACK_DESC desB;
//				m_pAnimControl->GetTrackDesc(0, &desA);
//				m_pAnimControl->GetTrackDesc(1, &desB);
//				desA.Position = 0.0;
//				//desB.Position = 0.0;
//				m_pAnimControl->SetTrackDesc(0, &desA);
//				m_pAnimControl->SetTrackDesc(1, &desB);
//			}
//			m_pAnimControl->SetTrackPriority(0, D3DXPRIORITY_HIGH);
//			m_pAnimControl->SetTrackPriority(1, D3DXPRIORITY_HIGH);
//			
//			
//			m_pAnimControl->ResetTime();
//			m_bIsTransferAnimation = true;
//		}
//		
//		if (m_fChangeTime <= 1.0f){
//			if (m_dwCurrentTrack == 0){
//				m_pAnimControl->SetTrackWeight(
//					0,
//					1.0f - m_fChangeTime);
//
//				m_pAnimControl->SetTrackWeight(
//					1,
//					m_fChangeTime);
//			}
//			else {
//				m_pAnimControl->SetTrackWeight(
//					1,
//					1.0f - m_fChangeTime);
//
//				m_pAnimControl->SetTrackWeight(
//					0,
//					m_fChangeTime);
//			}
//		}
//		else {
//			m_eCurrentStatus = m_eNextStatus;
//			if (m_dwCurrentTrack == 0){
//				m_pAnimControl->SetTrackEnable(0, false);
//				m_pAnimControl->SetTrackSpeed(1, 1.0f);
//				m_dwCurrentTrack = 1;
//			}
//			else{
//				m_pAnimControl->SetTrackEnable(1, false);
//				m_pAnimControl->SetTrackSpeed(0, 1.0f);
//				m_dwCurrentTrack = 0;
//			}
//			m_bIsTransferAnimation = false;
//			m_fChangeTime = 0.0f;
//		} 
//
//		SAFE_RELEASE(pAnimationSetNext);
//		SAFE_RELEASE(pAnimationSetPrev);
//	}
//}
//
//void cSkinnedMesh::SetAnimationIndex(DWORD dwIndex){
//	LPD3DXANIMATIONSET pAnimationSet = NULL;
//	m_pAnimControl->GetAnimationSet(dwIndex, &pAnimationSet);
//
//	if (dwIndex != m_eCurrentStatus){
//		m_pAnimControl->SetTrackAnimationSet(0, pAnimationSet);
//		m_eCurrentStatus = (E_STATUS)dwIndex;
//	}
//	
//	SAFE_RELEASE(pAnimationSet);
//}
//
//void cSkinnedMesh::SetupBoneMatrixPtrs(D3DXFRAME* pFrame)
//{
//	// 각 프레임의 메시 컨테이너에 있는 pSkinInfo를 이용하여 영향받는 모든 
//	// 프레임의 매트릭스를 ppBoneMatrixPtrs에 연결한다.
//	if (pFrame){
//		ST_BONE* pBone = (ST_BONE*)pFrame;
//		if (pBone->pMeshContainer){
//			ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
//			// pSkinInfo->GetNumBones() 으로 영향받는 본의 개수를 찾음.
//			DWORD numBones = pBoneMesh->pSkinInfo->GetNumBones();
//			for (DWORD i = 0; i < numBones; i++){
//				// pSkinInfo->GetBoneName(i) 로 i번 프레임의 이름을 찾음
//				// D3DXFrameFind(루트 프레임, 프레임 이름) 로 프레임을 찾음.
//				ST_BONE* pinf = (ST_BONE*)D3DXFrameFind(m_pRootFrame, pBoneMesh->pSkinInfo->GetBoneName(i));
//				//ST_BONE_MESH* pinfMesh = (ST_BONE_MESH*)pinf->pMeshContainer;
//				// 찾아서 월드매트릭스를 걸어줘라.
//				pBoneMesh->ppBoneMatrixPtrs[i] = &pinf->matWorldTM;
//			}
//		}
//
//		//재귀적으로 모든 프레임에 대해서 실행.
//		if (pBone->pFrameSibling)
//		{
//			SetupBoneMatrixPtrs(pBone->pFrameSibling);
//		}
//		if (pBone->pFrameFirstChild)
//		{
//			SetupBoneMatrixPtrs(pBone->pFrameFirstChild);
//		}
//	}
//}
//
//void cSkinnedMesh::UpdateSkinnedMesh(D3DXFRAME* pFrame)
//{
//	// pCurrentBoneMatrices 를 계산하시오
//	// pCurrentBoneMatrices = pBoneOffsetMatrices * ppBoneMatrixPtrs 
//	ST_BONE* pBone = (ST_BONE*)pFrame;
//
//	D3DXMATRIXA16 mat;
//	D3DXMatrixIdentity(&mat);
//	SetupWorldMatrix(m_pRootFrame, &mat);
//
//	if (pBone->pMeshContainer){
//		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
//		if (pBoneMesh->pSkinInfo){
//			DWORD numBones = pBoneMesh->pSkinInfo->GetNumBones();
//			for (DWORD i = 0; i < numBones; i++){
//				pBoneMesh->pCurrentBoneMatrices[i] = pBoneMesh->pBoneOffsetMatrices[i] * (*pBoneMesh->ppBoneMatrixPtrs[i]);
//			}
//
//			BYTE* src = NULL;
//			BYTE* dest = NULL;
//
//			pBoneMesh->pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&src);
//			pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (void**)&dest);
//
//			//MeshData.pMesh을 업데이트 시켜준다.
//			pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
//				pBoneMesh->pCurrentBoneMatrices, NULL, src, dest);
//
//			pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
//			pBoneMesh->pOrigMesh->UnlockVertexBuffer();
//		}
//	}
//	//재귀적으로 모든 프레임에 대해서 실행
//
//	if (pBone->pFrameSibling)
//	{
//		UpdateSkinnedMesh(pBone->pFrameSibling);
//	}
//	if (pBone->pFrameFirstChild)
//	{
//		UpdateSkinnedMesh(pBone->pFrameFirstChild);
//	}
//
//}
