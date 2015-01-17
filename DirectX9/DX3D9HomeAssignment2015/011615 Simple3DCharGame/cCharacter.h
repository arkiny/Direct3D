#pragma once

class cFrame;

class cCharacter
{
private:
	std::vector<cFrame*>			m_vecFrameRoots;
	std::vector<stSceneInfo>		m_vecSceneInfo;

	D3DXVECTOR3						m_vPosition;
	D3DXVECTOR3						m_vFront;
	float							m_fAngle = 0.0f;

	D3DXMATRIXA16					m_matMat;
	cFrame*							m_pCurrentFrameRoot;
	float							m_fAccum = 0.0f;

public:
	enum							ECState{ECS_IDLE, ECS_ISWALK};
	
	cCharacter();
	~cCharacter();
	void Setup();
	void Update(float delta);
	void Render();
	D3DXVECTOR3* GetPosition() { return &m_vPosition; }
};

