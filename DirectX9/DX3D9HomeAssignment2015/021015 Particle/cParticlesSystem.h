#pragma once

class cParticles;

class cParticlesSystem
{
private:
	std::vector<cParticles*> m_vecParticles;

public:
	cParticlesSystem(void);
	~cParticlesSystem(void);

	// Utility Function
	DWORD FtoDw(float f)
	{
		return *((DWORD*)&f);
	}

	void Setup();
	void Update(float fDelta);
	void Render();
};

