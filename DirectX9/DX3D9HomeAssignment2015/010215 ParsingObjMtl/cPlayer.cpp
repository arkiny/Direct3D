#include "stdafx.h"
#include "cPlayer.h"

#include "cPart.h"
#include "cMainGame.h"

cPlayer::cPlayer()
	: m_eCurrAnim(E_ANIM_IDLE)
	, m_vPosition(0, 4.5f, 0)
	, m_vForward(0, 0, 1)
	, m_fAngle(0.0f)
	, m_fSpeed(100.0f)
	, m_pRoot(NULL)
	, m_pGame(NULL)
{
}


cPlayer::~cPlayer()
{
	if (m_pRoot)
		m_pRoot->Destroy();
}

void cPlayer::Setup(cMainGame* game){
	m_pGame = game;
	LPDIRECT3DTEXTURE9 pTexture = NULL;
	D3DXCreateTextureFromFile(
		g_pD3DDevice,
		L"../Resource/Iron_Man_Skin_2.png",
		&pTexture);

	D3DXMATRIXA16 matPrevT, matPostT;

	// 몸통
	cPart* pPart = new cPart;
	pPart->Setup(2, 3, 1, cPart::Cube_Part::PT_body);
	pPart->SetTexture(pTexture);
	//pCube->SetPosition(D3DXVECTOR3(0, 0, 0));
	m_pRoot = pPart;
	
	// 머리

	pPart = new cPart;
	pPart->Setup(2, 2, 2, cPart::Cube_Part::PT_head);
	pPart->SetTexture(pTexture);
	D3DXMatrixTranslation(&matPrevT, 0, 2.5f, 0);
	D3DXMatrixIdentity(&matPostT);
	pPart->SetTransform(matPrevT, matPostT);
	m_pRoot->AddChild(pPart);
	
	// 팔

	pPart = new cPart;
	pPart->Setup(1, 3, 1, cPart::Cube_Part::PT_arm_left);
	pPart->SetTexture(pTexture);
	pPart->SetAngleSpeed(4.0f);
	//pPart->SetPosition(D3DXVECTOR3(-1.5, 0, 0));
	D3DXMatrixTranslation(&matPrevT, 0, -1.0, 0);
	D3DXMatrixTranslation(&matPostT, -1.5, 1.0, 0);
	pPart->SetTransform(matPrevT, matPostT);
	m_pRoot->AddChild(pPart);

	pPart = new cPart;
	pPart->Setup(1, 2, 1, cPart::Cube_Part::PT_arm_right);
	pPart->SetTexture(pTexture);
	pPart->SetAngleSpeed(-4.0f);
	D3DXMatrixTranslation(&matPrevT, 0, -0.75, 0);
	D3DXMatrixTranslation(&matPostT, 1.5, 1.25, 0);
	pPart->SetTransform(matPrevT, matPostT);
	m_pRoot->AddChild(pPart);

	cPart* pPart2 = new cPart;
	pPart2->Setup(1, 1, 1, cPart::Cube_Part::PT_fist);
	pPart2->SetTexture(pTexture);
	pPart2->SetAngleSpeed(0.0f);
	D3DXMatrixTranslation(&matPrevT, 0, 0, 0);
	D3DXMatrixTranslation(&matPostT, 0, -1.5f, 0);
	pPart2->SetTransform(matPrevT, matPostT);
	pPart->AddChild(pPart2);
	m_pFist = pPart2;

	// 다리
	
	pPart = new cPart;
	pPart->Setup(1, 3, 1, cPart::Cube_Part::PT_leg_left);
	pPart->SetTexture(pTexture);
	pPart->SetAngleSpeed(-4.0f);
	//pPart->SetPosition(D3DXVECTOR3(-0.5, -3, 0));
	D3DXMatrixTranslation(&matPrevT, 0, -1.5f, 0);
	D3DXMatrixTranslation(&matPostT, -0.5, -1.5f, 0);
	pPart->SetTransform(matPrevT, matPostT);
	m_pRoot->AddChild(pPart);

	pPart = new cPart;
	pPart->Setup(1, 3, 1, cPart::Cube_Part::PT_leg_right);
	pPart->SetTexture(pTexture);
	pPart->SetAngleSpeed(4.0f);
	D3DXMatrixTranslation(&matPrevT, 0, -1.5f, 0);
	D3DXMatrixTranslation(&matPostT, 0.5, -1.5f, 0);
	pPart->SetTransform(matPrevT, matPostT);
	m_pRoot->AddChild(pPart);

	SAFE_RELEASE(pTexture);
}

void cPlayer::Update(float delta){
	
	if (GetKeyState(VK_SPACE) & 0x8000 && m_eCurrAnim != E_ANIM_ATTACK){
		m_fAttackAnimationTime += delta;
		m_eCurrAnim = E_ANIM_ATTACK;
		m_pRoot->SetState(cPart::eAnimationPT::E_STATE_ATTACK);
	}
	else if (m_eCurrAnim == E_ANIM_ATTACK){	// 공격중인 상태일때
		m_fAttackAnimationTime += delta;
	
		if (m_fAttackAnimationTime > 0.180f && m_bAttacked == false){
			// Attack triggered (callback) 0.125sec
			m_bAttacked = true;
			m_pGame->CollisionCheck(this);
		}
		else if (m_fAttackAnimationTime > 0.25f){
			m_bAttacked = false;
			m_fAttackAnimationTime = 0;
			m_eCurrAnim = E_ANIM_IDLE;
			m_pRoot->SetState(cPart::eAnimationPT::E_STATE_IDLE);
			m_pRoot->SetForcedXangle(D3DXToRadian(240.0f));
		}
	}
	else { // 공격 상태중이 아닐때
		if (GetKeyState('A') & 0x8000)
		{
			m_fAngle -= 4.0f * delta;
			D3DXMATRIXA16 matR;
			D3DXMatrixRotationY(&matR, m_fAngle);
			m_vForward = D3DXVECTOR3(0, 0, 1);
			D3DXVec3TransformNormal(&m_vForward, &m_vForward, &matR);
		}
		else if (GetKeyState('D') & 0x8000)
		{
			m_fAngle += 4.0f * delta;
			D3DXMATRIXA16 matR;
			D3DXMatrixRotationY(&matR, m_fAngle);
			m_vForward = D3DXVECTOR3(0, 0, 1);
			D3DXVec3TransformNormal(&m_vForward, &m_vForward, &matR);
		}

		if (GetKeyState('W') & 0x8000)
		{
			m_eCurrAnim = E_ANIM_WALK;
			m_pRoot->SetState(cPart::eAnimationPT::E_STATE_WALK);
			m_vPosition += (m_vForward * m_fSpeed * delta);
		}
		else if (GetKeyState('S') & 0x8000)
		{
			m_eCurrAnim = E_ANIM_WALK;
			m_pRoot->SetState(cPart::eAnimationPT::E_STATE_WALK);
			m_vPosition -= (m_vForward * m_fSpeed * delta);
		}
		else
		{
			m_eCurrAnim = E_ANIM_IDLE;
			m_pRoot->SetState(cPart::eAnimationPT::E_STATE_IDLE);
		}

	}

	if (m_eCurrAnim == E_ANIM_IDLE)
	{
		m_pRoot->SetForcedAngle(0.0f);
	}

	D3DXMATRIXA16 matR, matT, matWorld;
	D3DXMatrixRotationY(&matR, m_fAngle);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	matWorld = matR * matT;

	m_pRoot->Update(delta, &matWorld);
}

void cPlayer::Render(){
	m_pRoot->Render();
}

GRIDPOSITION cPlayer::getGridCoord(){
	GRIDPOSITION ret;
	ret.x = static_cast<int>((m_vPosition.x + 50.0f) / 5.0f);
	ret.y = static_cast<int>(m_vPosition.y);
	ret.z = static_cast<int>((m_vPosition.z + 50.0f) / 5.0f);
	return ret;
}

D3DXVECTOR3& cPlayer::getFistPosition() {
	return m_pFist->getTransformedCoord();
}