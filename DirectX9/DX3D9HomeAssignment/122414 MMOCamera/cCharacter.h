#pragma once
class cCharacter
{
public:
	cCharacter();
	cCharacter(D3DXVECTOR3 origin);
	~cCharacter();

	void init();
	void update(float delta);
	void render();
	D3DXVECTOR3& getPosition() { return m_vecPos; }
	D3DXVECTOR3& getForward(){ return m_vecForward; }

private:
	LPDIRECT3DTEXTURE9			m_pTexture;
	D3DXVECTOR3					m_vecPos;
	D3DXVECTOR3					m_vecForward;
	float						m_fAngleDegree;
	float						m_fSpeed;
	std::vector<ST_PT_VERTEX>	m_vecVertex;
};

