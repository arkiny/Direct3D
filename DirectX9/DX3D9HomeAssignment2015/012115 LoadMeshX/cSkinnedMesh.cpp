#include "stdafx.h"
#include "cSkinnedMesh.h"
#include "cAllocateHierarchy.h"


cSkinnedMesh::cSkinnedMesh()
	: m_pRootFrame(NULL)
{
	
}


cSkinnedMesh::~cSkinnedMesh()
{
	if (m_pRootFrame){
		cAllocateHierarchy Alloc;
		D3DXFrameDestroy(m_pRootFrame, &Alloc);
	}
}

void cSkinnedMesh::Setup(std::string sFolder, std::string sFile){
	cAllocateHierarchy Alloc;
	HRESULT hr;

	hr = D3DXLoadMeshHierarchyFromX("../Resource/Zealot/zealot.X",
		D3DXMESH_MANAGED, g_pD3DDevice, &Alloc, NULL, &m_pRootFrame, NULL);
	_ASSERT(hr == S_OK);
}

void cSkinnedMesh::SetupWorldMatrix(D3DXFRAME* pFrame, D3DXMATRIXA16* pmatParnet){
	/*ST_BONE* pBone = pFrame->*/
	
}