#include "stdafx.h"
#include "cAllocateHierarchy.h"


cAllocateHierarchy::cAllocateHierarchy()
{
}


cAllocateHierarchy::~cAllocateHierarchy()
{
}


HRESULT cAllocateHierarchy::CreateFrame(THIS_ LPCSTR Name,
	LPD3DXFRAME *ppNewFrame){

	ST_BONE* pBone = new ST_BONE;
	D3DXMatrixIdentity(&pBone->matWorld);
	D3DXMatrixIdentity(&pBone->TransformationMatrix);
	pBone->pFrameFirstChild = NULL;
	pBone->pFrameSibling = NULL;
	pBone->pMeshContainer = NULL;
	*ppNewFrame = pBone;

	return S_OK;
}

HRESULT cAllocateHierarchy::CreateMeshContainer(
	THIS_ LPCSTR Name,
	CONST D3DXMESHDATA *pMeshData,
	CONST D3DXMATERIAL *pMaterials,
	CONST D3DXEFFECTINSTANCE *pEffectInstances,
	DWORD NumMaterials,
	CONST DWORD *pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER *ppNewMeshContainer){

	// should deep copy this
	// clone mesh or addref
	// d3dxmeshcontainer can be inheritted
	// effectinstance if not null, deep copying
	// should memcpy
	// skin info -> COM object, or clone
	D3DXMESHCONTAINER* pMeshcontainer = new D3DXMESHCONTAINER;
	
	pMeshcontainer->pAdjacency = NULL;
	pMeshcontainer->pEffects = new D3DXEFFECTINSTANCE;
	pMeshcontainer->pMaterials = new D3DXMATERIAL;

	if (Name){
		pMeshcontainer->Name = new char[strlen(Name)];
		strcpy(pMeshcontainer->Name, Name);
	}

	if (pMeshData){
		pMeshcontainer->MeshData.Type = pMeshData->Type;
		pMeshData->pMesh->CloneMeshFVF(
			pMeshData->pMesh->GetOptions(),
			pMeshData->pMesh->GetFVF(),
			g_pD3DDevice,
			&pMeshcontainer->MeshData.pMesh);
	}
	//pMeshData->pMesh->AddRef();
	if (pEffectInstances){
		// do later
		/*LPSTR               pEffectFilename;
		DWORD               NumDefaults;
		LPD3DXEFFECTDEFAULT pDefaults;*/
		/*pMeshcontainer->pEffects->NumDefaults = pEffectInstances->NumDefaults;
		pMeshcontainer->pEffects->pEffectFilename = "";
		strncpy(pMeshcontainer->pEffects->pEffectFilename, pEffectInstances->pEffectFilename, strlen(pEffectInstances->pEffectFilename));
		pMeshcontainer->pEffects->pDefaults->NumBytes = pEffectInstances->pDefaults->NumBytes;
		pMeshcontainer->pEffects->pDefaults->Type = pEffectInstances->pDefaults->Type;*/
		//LPSTR                 pParamName;
		//D3DXEFFECTDEFAULTTYPE Type;           // type of the data pointed to by pValue
		//DWORD                 NumBytes;       // size in bytes of the data pointed to by pValue
		//LPVOID                pValue;         // data for the default of the effect

	}
	if (pMaterials){
		//memcpy(&pMeshcontainer->pMaterials, pMaterials, sizeof(D3DXMATERIAL)* NumMaterials);
		pMeshcontainer->pMaterials = new D3DXMATERIAL[NumMaterials];
		//	D3DXMATERIAL point = *pMaterials;
		pMeshcontainer->NumMaterials = NumMaterials;
		for (int i = 0; i < NumMaterials; i++){
			memcpy(&pMeshcontainer[i].pMaterials->MatD3D, &pMaterials[i].MatD3D, sizeof(D3DMATERIAL9));
			pMeshcontainer->pMaterials[i].pTextureFilename = new char[strlen(pMaterials[i].pTextureFilename)+1];	
			strcpy(pMeshcontainer->pMaterials[i].pTextureFilename, pMaterials[i].pTextureFilename);	
		}
	}

	if (pAdjacency){
		int numVertex = pMeshData->pMesh->GetNumFaces() * 3;
		pMeshcontainer->pAdjacency = new DWORD[pMeshData->pMesh->GetNumFaces() * 3];
		memcpy(pMeshcontainer->pAdjacency, pAdjacency, sizeof(DWORD)*pMeshData->pMesh->GetNumFaces()*3);
	}
	
	if (pSkinInfo){
		pSkinInfo->Clone(&pMeshcontainer->pSkinInfo);
	}

	*ppNewMeshContainer = pMeshcontainer;

	return S_OK;
}

HRESULT cAllocateHierarchy::DestroyFrame(THIS_ LPD3DXFRAME pFrameToFree){
	delete pFrameToFree;
	return S_OK;
}

HRESULT cAllocateHierarchy::DestroyMeshContainer(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree){
	if (strlen(pMeshContainerToFree->Name) > 0){
		delete[] pMeshContainerToFree->Name;
	}
	if (pMeshContainerToFree->MeshData.pMesh){
		pMeshContainerToFree->MeshData.pMesh->Release();
	}
	if (pMeshContainerToFree->pEffects){
		// we don't use this yet
		/*if (pMeshContainerToFree->pEffects->pDefaults->pParamName){
			if (strlen(pMeshContainerToFree->pEffects->pDefaults->pParamName) > 0)
				delete pMeshContainerToFree->pEffects->pDefaults->pParamName;
		}
		
		if (pMeshContainerToFree->pEffects->pDefaults->pValue){
			delete pMeshContainerToFree->pEffects->pDefaults->pValue;
		}
		if (strlen(pMeshContainerToFree->pEffects->pEffectFilename) > 0){
			delete[] pMeshContainerToFree->pEffects->pEffectFilename;
		}		*/
	}
	if (pMeshContainerToFree->pMaterials){
		delete pMeshContainerToFree->pMaterials;
	}
	if (pMeshContainerToFree->pAdjacency){
		delete[] pMeshContainerToFree->pAdjacency;
	}
	if (pMeshContainerToFree->pSkinInfo){
		pMeshContainerToFree->pSkinInfo->Release();
	}
	return S_OK;
}