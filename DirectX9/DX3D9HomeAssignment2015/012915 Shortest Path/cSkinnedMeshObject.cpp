#include "stdafx.h"
#include "cSkinnedMeshObject.h"
#include "cSkinnedMesh.h"

cSkinnedMeshObject::cSkinnedMeshObject()
	:m_pSkinnedMesh(NULL)
{
}


cSkinnedMeshObject::~cSkinnedMeshObject()
{
	SAFE_DELETE(m_pSkinnedMesh);
}

void cSkinnedMeshObject::Setup(){
	m_pSkinnedMesh = new cSkinnedMesh;
	m_pSkinnedMesh->Setup("../Resource/Zealot/", "zealot.X");
	m_pSkinnedMesh->SetAnimationLoop(0, false);
	m_pSkinnedMesh->SetAnimationLoop(1, false);
	m_pSkinnedMesh->SetAnimationLoop(2, false);
	m_pSkinnedMesh->SetAnimationLoop(3, true);
	m_pSkinnedMesh->SetAnimationLoop(4, true);
	m_pSkinnedMesh->SetAnimationIndex(4);	
}

void cSkinnedMeshObject::Update(float delta){
	if (m_pSkinnedMesh){
		m_pSkinnedMesh->Update(delta);
		cGameObject::Update(delta);
		/*D3DXMATRIXA16 worldMat;
		D3DXMatrixRotationY(&worldMat, m_fAngle);
		worldMat._41 = GetTransformMatrix()->_41;
		worldMat._42 = GetTransformMatrix()->_42;
		worldMat._43 = GetTransformMatrix()->_43;*/
		
	}
}

void cSkinnedMeshObject::Render(){
	if (m_pSkinnedMesh){
		m_pSkinnedMesh->Render(GetTransformMatrix());
	}
}
void cSkinnedMeshObject::SetAnimationIndex(DWORD dwIndex){
	if (m_pSkinnedMesh){
		m_pSkinnedMesh->SetAnimationIndex(dwIndex);
	}
}
