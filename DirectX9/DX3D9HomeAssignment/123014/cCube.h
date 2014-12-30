#pragma once
__declspec(align(16)) class cCube
{
public:
	enum Cube_Part{PT_body, PT_head, PT_leg_left, PT_leg_right, PT_arm_left, PT_arm_right};

	cCube();
	~cCube();

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

		void operator delete(void* p)
	{
		_mm_free(p);
	}

	void init(float fWidth, float fHeight, float fDepth, Cube_Part type);
	void update(float delta);
	void render();
	void setPosition(D3DXVECTOR3 pos) { m_vPosition = pos; }
	D3DXVECTOR3& getPosition() { return m_vPosition; }
	D3DXVECTOR3& getForward(){ return m_vForward; }
	void setWorldMatrix(D3DXMATRIXA16* input){ m_worldMatrix = input; }
	void idle();

	void SetTexture(LPDIRECT3DTEXTURE9 pTexture);

private:
	std::vector<ST_PT_VERTEX>	m_vecVertex;
	std::vector<ST_PT_VERTEX>	m_vecIdleVertex;

	D3DXVECTOR3					m_vPosition;
	D3DXVECTOR3					m_vForward;

	float						m_fShakingAngle;
	float						m_fShakingAngleUnit = 4.0f;

	float						m_fAngle;
	float						m_fSpeed;
	LPDIRECT3DTEXTURE9			m_pTexture;
	D3DXMATRIXA16*				m_worldMatrix;
	Cube_Part					m_eType;

	bool						m_bMoved = false;
};

