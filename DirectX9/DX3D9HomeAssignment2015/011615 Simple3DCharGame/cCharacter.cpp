#include "stdafx.h"
#include "cCharacter.h"
#include "cFrame.h"
#include "cAseLoader.h"

cCharacter::cCharacter() :
m_pCurrentFrameRoot(NULL),
m_vFront(0,0,-1.0f)
{
}


cCharacter::~cCharacter()
{
	for (auto p : m_vecFrameRoots){
		if (p){
			p->Destroy();
		}
	}
}

void cCharacter::Setup(){	
	cAseLoader AseLoader1;
	std::string sFolder1 = std::string("../Resource/");
	sFolder1 += std::string("ase/woman/");
	stSceneInfo scene = {};

	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	cFrame* pS = AseLoader1.Load(sFolder1, std::string("woman_01_all_stand.ASE"), scene);
	pS->CalcLocalTM(&mat);
	m_vecFrameRoots.push_back(pS);
	m_vecSceneInfo.push_back(scene);
	
	cAseLoader AseLoader2;
	cFrame* pW = AseLoader2.Load(sFolder1, std::string("woman_01_all.ASE"), scene);
	pW->CalcLocalTM(&mat);
	m_vecFrameRoots.push_back(pW);
	m_vecSceneInfo.push_back(scene);
	m_pCurrentFrameRoot = pW;
}

void cCharacter::Update(float delta){
	m_fAccum += delta;
	int index = 0;
	
	//D3DXVECTOR3 curPos = m_pTransform->GetPosition();
	float fangle = m_pTransform->GetYAxisAngle();

	if (GetKeyState('W') & 0x8000){
		index = 1;
		//curPos += m_vFront*delta*5.0f;
		m_pTransform->SetPosition(
			m_pTransform->GetPosition() + m_vFront*delta*5.0f);
	}
	if (GetKeyState('S') & 0x8000){
		index = 1;
		//curPos -= m_vFront*delta*5.0f;
		m_pTransform->SetPosition(
			m_pTransform->GetPosition() - m_vFront*delta*5.0f);
	}
	if (GetKeyState('A') & 0x8000){
		index = 1;
		m_pTransform->SetYAxisAngle(m_pTransform->GetYAxisAngle() - 4.0f * delta);
		D3DXMATRIXA16 matR;
		D3DXMatrixRotationY(&matR, m_pTransform->GetYAxisAngle());
		m_vFront = D3DXVECTOR3(0, 0, -1.f);
		D3DXVec3TransformNormal(&m_vFront, &m_vFront, &matR);
	}
	if (GetKeyState('D') & 0x8000){
		index = 1;
		m_pTransform->SetYAxisAngle(m_pTransform->GetYAxisAngle() + 4.0f * delta);
		D3DXMATRIXA16 matR;
		D3DXMatrixRotationY(&matR, m_pTransform->GetYAxisAngle());
		m_vFront = D3DXVECTOR3(0, 0, -1.f);
		D3DXVec3TransformNormal(&m_vFront, &m_vFront, &matR);
	}

	int temp = m_vecSceneInfo[index].uiFrameSpeed * m_vecSceneInfo[index].uiFrameTick;
	float t = m_fAccum * temp;
	
	if (m_fAccum > m_vecSceneInfo[index].uiFrameLast * m_vecSceneInfo[index].uiFrameTick){
		m_fAccum = 0;
	}

	int first = 640;
	int last = m_vecSceneInfo[index].uiFrameLast * m_vecSceneInfo[index].uiFrameTick;
	//int passed = static_cast<int>(m_fAccum)* m_vecSceneInfo[1].uiFrameSpeed * m_vecSceneInfo[1].uiFrameSpeed;
	
	int nkey = (static_cast<int>(t) % (last - first)) + first;
	//(GetTickCount() % (3200 - 640)) + 640;
	
	m_pCurrentFrameRoot = m_vecFrameRoots[index];
	
	D3DXMATRIXA16 matWorld;
	matWorld = *GetTransformMatrix();

	if (m_pCurrentFrameRoot)
		m_pCurrentFrameRoot->Update(&matWorld, nkey);
}

void cCharacter::Render(){
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	m_pCurrentFrameRoot->Render();
}

D3DXVECTOR3* cCharacter::GetPosition() { 
	return m_pTransform->getPosPointer();
}