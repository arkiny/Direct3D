#include "stdafx.h"
#include "cZealot.h"
#include "cAllocateHierarchy.h"
#include "cMtlTex.h"

cZealot::cZealot() :
m_pFrame(NULL),
m_vPosition(0, 0, 0),
m_pMesh(NULL),
m_pMtlTex(NULL)
{
}


cZealot::~cZealot()
{
	cAllocateHierarchy Alloc;
	D3DXFrameDestroy((D3DXFRAME*)m_pFrame, &Alloc);
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMtlTex);
}

void cZealot::Setup(){
	cAllocateHierarchy Alloc;
	HRESULT hr;
	LPD3DXFRAME p = m_pFrame;
	/*ID3DXAnimationController ctrl;*/
	hr = D3DXLoadMeshHierarchyFromX("../Resource/Zealot/zealot.X",
		D3DXMESH_MANAGED, g_pD3DDevice, &Alloc, NULL, &p, NULL);
	_ASSERT(hr == S_OK);
	m_pFrame = (D3DXFRAME_DR*)p;
	/*D3DXMATRIXA16 mat;
	CalculateWorldTM(&mat, m_pFrame);*/
	D3DXCreateSphere(g_pD3DDevice, 0.025f, 10, 10, &m_pMesh, 0);
	m_pMtlTex = new cMtlTex;
	m_pMtlTex->stMtl.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.2f, 1.0f);
	m_pMtlTex->stMtl.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.2f, 1.0f);
	m_pMtlTex->stMtl.Specular = D3DXCOLOR(0.8f, 0.8f, 0.2f, 1.0f);
}

void cZealot::Update(float delta){

}

void cZealot::Render(){
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	g_pD3DDevice->SetMaterial(&m_pMtlTex->stMtl);
	g_pD3DDevice->SetTexture(0, NULL);
	if (m_pFrame){
		RenderingAllFrame(&mat, m_pFrame);
	}
}

void cZealot::RenderingAllFrame(D3DXMATRIXA16* pParentWorldTM, D3DXFRAME_DR* pFrame){
	if (pFrame){
		D3DXMATRIXA16 matWorld;
		D3DXMatrixIdentity(&matWorld);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

		pFrame->matWorld = (pFrame->TransformationMatrix) * (*pParentWorldTM);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &pFrame->matWorld);
		m_pMesh->DrawSubset(0);
	
		if (pFrame->pFrameFirstChild){
			RenderingAllFrame(&pFrame->matWorld, (D3DXFRAME_DR*)pFrame->pFrameFirstChild);
		}
		
		if (pFrame->pFrameSibling){
			RenderingAllFrame(pParentWorldTM, (D3DXFRAME_DR*)pFrame->pFrameSibling);
		}
		
	}
}

//void cZealot::CalculateWorldTM(D3DXMATRIXA16* pParentWorldTM, D3DXFRAME_DR* pFrameDR){
//	if (pFrameDR){
//		pFrameDR->matWorld = (pFrameDR->TransformationMatrix) * (*pParentWorldTM);
//
//		if (pFrameDR->pFrameFirstChild){
//			CalculateWorldTM(&pFrameDR->matWorld, (D3DXFRAME_DR*)pFrameDR->pFrameFirstChild);
//		}
//
//		if (pFrameDR->pFrameSibling){
//			CalculateWorldTM(pParentWorldTM, (D3DXFRAME_DR*)pFrameDR->pFrameSibling);
//		}
//	}
//}