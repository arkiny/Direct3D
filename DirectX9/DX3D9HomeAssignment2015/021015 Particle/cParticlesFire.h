#pragma once
#include "cParticles.h"

class cParticlesFire : public cParticles
{
protected:
	

public:
	cParticlesFire();
	virtual ~cParticlesFire();

	virtual void Setup();
	virtual void Update(float fDelta);
};

