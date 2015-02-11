#pragma once

struct ST_PARTICLE{
	D3DXVECTOR3		_direction;
	D3DXVECTOR3		_vInitialPos;

	float			_speed;

	float			_lifeSpan;
	float			_currentTime;
};

class cParticles
{
protected:
	std::vector<ST_PC_VERTEX>	m_vecVertex;
	std::vector<ST_PARTICLE>	m_vecMoveInfo;

	D3DXVECTOR3					m_vPosition;
	D3DXVECTOR3					m_vFirst;

public:
	cParticles();
	~cParticles();

	// Utility Function
	DWORD FtoDw(float f)
	{
		return *((DWORD*)&f);
	}

	virtual void SetPosition(D3DXVECTOR3& pos){ m_vPosition = pos; m_vFirst = m_vPosition; }
	virtual void Setup();
	virtual void Update(float fDelta);
	virtual void Render();
};

