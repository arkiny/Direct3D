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
	*ppNewFrame = new D3DXFRAME_DR;
	return S_OK;
}

HRESULT cAllocateHierarchy::CreateMeshContainer(THIS_
	LPCSTR Name,
	CONST D3DXMESHDATA *pMeshData,
	CONST D3DXMATERIAL *pMaterials,
	CONST D3DXEFFECTINSTANCE *pEffectInstances,
	DWORD NumMaterials,
	CONST DWORD *pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER *ppNewMeshContainer){

	*ppNewMeshContainer = new D3DXMESHCONTAINER;
	
	return S_OK;
}

HRESULT cAllocateHierarchy::DestroyFrame(THIS_ LPD3DXFRAME pFrameToFree){
	delete pFrameToFree;
	return S_OK;
}

HRESULT cAllocateHierarchy::DestroyMeshContainer(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree){
	delete pMeshContainerToFree;
	return S_OK;
}