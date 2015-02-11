#include "StdAfx.h"
#include "cParticles.h"
#include "cParticlesFire.h"
#include "cParticlesSystem.h"
#include "cParticlesExplosion.h"

cParticlesSystem::cParticlesSystem(void)
{
}


cParticlesSystem::~cParticlesSystem(void)
{
}

void cParticlesSystem::Setup()
{
	g_pTextureManager->GetTexture("Particle.tga");

	// ����Ʈ�� Ȯ�� ��� �� �� �ְ� ����
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true); 

	// ����Ʈ �����ϸ� Factor�� ����
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDw(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDw(50.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDw(100.0f));

	// ����Ʈ�� �ؽ��ĸ� ���� �� �ְ� ����
	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);

	// �ؽ��� ���� �ɼ� ����
	g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );  
	g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );  
	g_pD3DDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );  

	// ���ĺ��� ��� ����.
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	cParticles* p = new cParticles;
	p->Setup();
	//p->SetPosition(D3DXVECTOR3(3, 0, 0));
	m_vecParticles.push_back(p);

	cParticlesFire* pf = new cParticlesFire;
	pf->Setup();
	pf->SetPosition(D3DXVECTOR3(1, 0, 0));
	m_vecParticles.push_back(pf);

	cParticlesExplosion* pe = new cParticlesExplosion;
	pe->Setup();
	pe->SetPosition(D3DXVECTOR3(-6, 0, 0));
	m_vecParticles.push_back(pe);
}

void cParticlesSystem::Update(float fDelta)
{
	for (auto p : m_vecParticles){
		p->Update(fDelta);
	}
}

void cParticlesSystem::Render()
{
	for (auto p : m_vecParticles){
		p->Render();
	}
}
