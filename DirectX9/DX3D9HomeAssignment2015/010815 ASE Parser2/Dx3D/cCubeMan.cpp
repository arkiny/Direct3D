#include "StdAfx.h"
#include "cCubeMan.h"
#include "cCube.h"
#include "iMap.h"

cCubeMan::cCubeMan(void)
	: m_eCurrAnim(E_ANIM_IDLE)
	, m_vPosition(0, 0, 0)
	, m_vForward(0, 0, -1)
	, m_fAngle(0.0f)
	, m_fSpeed(0.5f)
	, m_pRoot(NULL)
{
}


cCubeMan::~cCubeMan(void)
{
	if(m_pRoot)
		m_pRoot->Destroy();
}

void cCubeMan::Setup()
{
	LPDIRECT3DTEXTURE9 pTexture = NULL;
	std::string sResourceFolder(RESOURCE_FOLDER);
	std::string sFile;

	// ¸öÅë
	sFile = sResourceFolder + std::string("Texture/Body.jpg");
	D3DXCreateTextureFromFile(g_pD3DDevice, sFile.c_str(), &pTexture);

	D3DXMATRIXA16 matPrevT, matPostT;

	cCube* pCube = new cCube;
	pCube->Setup(2, 4, 1);
	pCube->SetTexture(pTexture);
	//pCube->SetPosition(D3DXVECTOR3(0, 0, 0));
	m_pRoot = pCube;
	SAFE_RELEASE(pTexture);

	// ¸Ó¸®
	sFile = sResourceFolder + std::string("Texture/Head.jpg");
	D3DXCreateTextureFromFile(g_pD3DDevice, sFile.c_str(), &pTexture);

	pCube = new cCube;
	pCube->Setup(2, 2, 2);
	pCube->SetTexture(pTexture);
	D3DXMatrixTranslation(&matPrevT, 0, 3, 0);
	D3DXMatrixIdentity(&matPostT);
	pCube->SetTransform(matPrevT, matPostT);
	m_pRoot->AddChild(pCube);
	SAFE_RELEASE(pTexture);

	// ÆÈ
	sFile = sResourceFolder + std::string("Texture/Arms.jpg");
	D3DXCreateTextureFromFile(g_pD3DDevice, sFile.c_str(), &pTexture);

	pCube = new cCube;
	pCube->Setup(1, 4, 1);
	pCube->SetTexture(pTexture);
	pCube->SetAngleSpeed(0.05f);
	//pCube->SetPosition(D3DXVECTOR3(-1.5, 0, 0));
	D3DXMatrixTranslation(&matPrevT, 0, -2, 0);
	D3DXMatrixTranslation(&matPostT, -1.5, 2, 0);
	pCube->SetTransform(matPrevT, matPostT);
	m_pRoot->AddChild(pCube);

	pCube = new cCube;
	pCube->Setup(1, 4, 1);
	pCube->SetTexture(pTexture);
	pCube->SetAngleSpeed(-0.05f);
	D3DXMatrixTranslation(&matPrevT, 0, -2, 0);
	D3DXMatrixTranslation(&matPostT, 1.5, 2, 0);
	pCube->SetTransform(matPrevT, matPostT);
	m_pRoot->AddChild(pCube);

	SAFE_RELEASE(pTexture);

	// ´Ù¸®
	sFile = sResourceFolder + std::string("Texture/Legs.jpg");
	D3DXCreateTextureFromFile(g_pD3DDevice, sFile.c_str(), &pTexture);

	pCube = new cCube;
	pCube->Setup(1, 4, 1);
	pCube->SetTexture(pTexture);
	pCube->SetAngleSpeed(-0.05f);
	//pCube->SetPosition(D3DXVECTOR3(-0.5, -3, 0));
	D3DXMatrixTranslation(&matPrevT, 0, -2, 0);
	D3DXMatrixTranslation(&matPostT, -0.5, -2, 0);
	pCube->SetTransform(matPrevT, matPostT);
	m_pRoot->AddChild(pCube);

	pCube = new cCube;
	pCube->Setup(1, 4, 1);
	pCube->SetTexture(pTexture);
	pCube->SetAngleSpeed(0.05f);
	D3DXMatrixTranslation(&matPrevT, 0, -2, 0);
	D3DXMatrixTranslation(&matPostT, 0.5, -2, 0);
	pCube->SetTransform(matPrevT, matPostT);
	m_pRoot->AddChild(pCube);

	SAFE_RELEASE(pTexture);
}

void cCubeMan::Update(iMap* pMap/* = NULL*/)
{
	D3DXVECTOR3 vPosition = m_vPosition;

	bool isIdle = true;
	if(GetKeyState('A') & 0x8000)
	{
		m_fAngle -= 0.1f;
		D3DXMATRIXA16 matR;
		D3DXMatrixRotationY(&matR, m_fAngle);
		m_vForward = D3DXVECTOR3(0, 0, -1);
		D3DXVec3TransformNormal(&m_vForward, &m_vForward, &matR);
	}
	if(GetKeyState('D') & 0x8000)
	{
		m_fAngle += 0.1f;
		D3DXMATRIXA16 matR;
		D3DXMatrixRotationY(&matR, m_fAngle);
		m_vForward = D3DXVECTOR3(0, 0, -1);
		D3DXVec3TransformNormal(&m_vForward, &m_vForward, &matR);
	}
	if(GetKeyState('W') & 0x8000)
	{
		vPosition += (m_vForward * m_fSpeed);
		isIdle = false;
	}
	if(GetKeyState('S') & 0x8000)
	{
		vPosition -= (m_vForward * m_fSpeed);
		isIdle = false;
	}

	if(pMap)
	{
		bool isLand = false;
		float fHeight = pMap->GetHeight(isLand, &vPosition);
		if(isLand)
		{
			m_vPosition = vPosition;
			m_vPosition.y = fHeight;
		}
	}
	else
	{
		m_vPosition = vPosition;
	}
	
	if(isIdle)
	{
		m_pRoot->SetForcedAngle(0.0f);
	}

	D3DXMATRIXA16 matR, matT, matWorld;
	D3DXMatrixRotationY(&matR, m_fAngle);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	matWorld = matR * matT;
	m_pRoot->Update(&matWorld);
}

void cCubeMan::Render()
{
	m_pRoot->Render();
}
