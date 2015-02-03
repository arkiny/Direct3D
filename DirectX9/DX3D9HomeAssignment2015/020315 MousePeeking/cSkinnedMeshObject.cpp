#include "stdafx.h"
#include "cSkinnedMeshObject.h"
#include "cSkinnedMesh.h"
#include "cSphere.h"

cSkinnedMeshObject::cSkinnedMeshObject()
	:m_pSkinnedMesh(NULL),
	m_pSphere(NULL)
{
}


cSkinnedMeshObject::~cSkinnedMeshObject()
{
	SAFE_DELETE(m_pSkinnedMesh);
	SAFE_RELEASE(m_pSphere);
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
	
	m_pSphere = new cSphere;
	m_pSphere->Setup();
	D3DXVECTOR3 pos = m_pTransform->GetPosition();
	pos.y = pos.y + 0.5f;
	m_pSphere->SetPosition(pos);

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
		D3DXVECTOR3 pos = m_pTransform->GetPosition();
		pos.y = pos.y + 0.5f;
		m_pSphere->SetPosition(pos);
	}
	
}

void cSkinnedMeshObject::Render(){
	if (m_pSkinnedMesh){
		m_pSkinnedMesh->Render(GetTransformMatrix());
		
	}
	if (m_pSphere){
		m_pSphere->Render();
	}
}
void cSkinnedMeshObject::SetAnimationIndex(DWORD dwIndex){
	if (m_pSkinnedMesh){
		m_pSkinnedMesh->SetAnimationIndex(dwIndex);
	}
}

void cSkinnedMeshObject::SetSelcted(bool in){
	if (m_pSphere){
		m_pSphere->SetSelcted(in);
	}
}