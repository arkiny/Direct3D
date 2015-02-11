#pragma once
#include "cParticles.h"

class cParticlesExplosion :
	public cParticles
{
protected:
	float m_fAccumDelay;
	const float m_fDealay = 0.5f;
	float m_fAccel;
public:
	cParticlesExplosion();
	virtual ~cParticlesExplosion();

	virtual void Setup();
	virtual void Update(float fDelta);
};

