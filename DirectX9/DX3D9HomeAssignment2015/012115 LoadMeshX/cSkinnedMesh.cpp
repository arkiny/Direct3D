#include "StdAfx.h"
#include "cSkinnedMesh.h"
#include "cAllocateHierarchy.h"
#include "cMtlTex.h"

cSkinnedMesh::cSkinnedMesh(void)
	: m_pRootFrame(NULL)
{
}


cSkinnedMesh::~cSkinnedMesh(void)
{
	if (m_pRootFrame)
	{
		cAllocateHierarchy Alloc;
		D3DXFrameDestroy(m_pRootFrame, &Alloc);
	}
	m_pAnimControl->Release();
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

	//	
	SetupBoneMatrixPtrs(m_pRootFrame);
	//
}

void cSkinnedMesh::Render()
{
	Render(m_pRootFrame);
}

void cSkinnedMesh::Update(float delta){
	m_pAnimControl->AdvanceTime(delta, NULL); 
	UpdateSkinnedMesh(m_pRootFrame);
}

void cSkinnedMesh::SetupWorldMatrix(D3DXFRAME* pFrame, D3DXMATRIXA16* pmatParent)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	//pBone->matWorldTM =  *(*pmatParent);

	if (pmatParent)
	{
		pBone->matWorldTM = pBone->TransformationMatrix * (*pmatParent);
	}
	else {
		pBone->matWorldTM = pBone->TransformationMatrix;
	}

	if (pBone->pFrameSibling)
	{
		SetupWorldMatrix(pBone->pFrameSibling, pmatParent);
	}
	if (pBone->pFrameFirstChild)
	{
		SetupWorldMatrix(pBone->pFrameFirstChild, &pBone->matWorldTM);
	}
}

void cSkinnedMesh::Render(D3DXFRAME* pFrame)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;
	
	/*D3DXMATRIXA16 worldmat = pBone->TransformationMatrix;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &worldmat);*/
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
		Render(pBone->pFrameSibling);
	}

	if (pBone->pFrameFirstChild)
	{
		Render(pBone->pFrameFirstChild);
	}
}

void cSkinnedMesh::SetupBoneMatrixPtrs(D3DXFRAME* pFrame)
{
	// �� �������� �޽� �����̳ʿ� �ִ� pSkinInfo�� �̿��Ͽ� ����޴� ��� 
	// �������� ��Ʈ������ ppBoneMatrixPtrs�� �����Ѵ�.
	ST_BONE* pBone = (ST_BONE*)pFrame;
	if (pBone->pMeshContainer){
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		// pSkinInfo->GetNumBones() ���� ����޴� ���� ������ ã��.
		DWORD numBones = pBoneMesh->pSkinInfo->GetNumBones();
		for (DWORD i = 0; i < numBones; i++){
			// pSkinInfo->GetBoneName(i) �� i�� �������� �̸��� ã��
			// D3DXFrameFind(��Ʈ ������, ������ �̸�) �� �������� ã��.
			ST_BONE* pinf = (ST_BONE*)D3DXFrameFind(m_pRootFrame, pBoneMesh->pSkinInfo->GetBoneName(i));
			//ST_BONE_MESH* pinfMesh = (ST_BONE_MESH*)pinf->pMeshContainer;
			// ã�Ƽ� �����Ʈ������ �ɾ����.
			pBoneMesh->ppBoneMatrixPtrs[i] = &pinf->matWorldTM;
		}
	}
	//��������� ��� �����ӿ� ���ؼ� ����.
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
	// pCurrentBoneMatrices �� ����Ͻÿ�
	// pCurrentBoneMatrices = pBoneOffsetMatrices * ppBoneMatrixPtrs 
	ST_BONE* pBone = (ST_BONE*)pFrame;

	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	SetupWorldMatrix(m_pRootFrame, &mat);

	if (pBone->pMeshContainer){
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		if (pBoneMesh->pSkinInfo){
			DWORD numBones = pBoneMesh->pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < numBones; i++){
				pBoneMesh->pCurrentBoneMatrices[i] = pBoneMesh->pBoneOffsetMatrices[i] * (*pBoneMesh->ppBoneMatrixPtrs[i]);
			}

			BYTE* src = NULL;
			BYTE* dest = NULL;

			pBoneMesh->pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&src);
			pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (void**)&dest);

			//MeshData.pMesh�� ������Ʈ �����ش�.
			pBoneMesh->pSkinInfo->UpdateSkinnedMesh(
				pBoneMesh->pCurrentBoneMatrices, NULL, src, dest);

			pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
			pBoneMesh->pOrigMesh->UnlockVertexBuffer();
		}
	}
	//��������� ��� �����ӿ� ���ؼ� ����

	if (pBone->pFrameSibling)
	{
		UpdateSkinnedMesh(pBone->pFrameSibling);
	}
	if (pBone->pFrameFirstChild)
	{
		UpdateSkinnedMesh(pBone->pFrameFirstChild);
	}

}
