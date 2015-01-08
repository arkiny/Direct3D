#pragma once
__declspec(align(16)) class cPart
{
public:
	enum Cube_Part{ PT_body, PT_head, PT_leg_left, PT_leg_right, PT_arm_left, PT_arm_right, PT_fist };
	enum eAnimationPT{E_STATE_IDLE, E_STATE_WALK, E_STATE_ATTACK};
private:
	std::vector<ST_PT_VERTEX>	m_vecVertex;
	LPDIRECT3DTEXTURE9			m_pTexture;
	D3DXMATRIXA16				m_matPrevT;
	D3DXMATRIXA16				m_matRot;
	D3DXMATRIXA16				m_matPostT;
	D3DXMATRIXA16				m_matWorldTM;
	float						m_fAngle;
	float						m_fXAngle;
	float						m_fAngleSpeed;
	std::vector<cPart*>			m_vecChildren;
	Cube_Part					m_epart;
	eAnimationPT				m_eState;

	IDirect3DVertexBuffer9*		m_pVertexBuffer;

public:
	cPart(void);
	~cPart(void);

	void* operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}

		void operator delete(void* p)
	{
		_mm_free(p);
	}

	void Setup(float fWidth, float fHeight, float fDepth, Cube_Part type);
	void Update(float delta, D3DXMATRIXA16* pmatParentWorld = NULL);
	void Render();
	void SetTexture(LPDIRECT3DTEXTURE9 pTexture);
	void SetTransform(D3DXMATRIXA16& matPrevT, D3DXMATRIXA16& matPostT);
	void AddChild(cPart* pChild);
	void Destroy();
	void SetAngleSpeed(float fSpeed)
	{
		m_fAngleSpeed = fSpeed;
	}
	void SetForcedAngle(float fAngle);
	void SetForcedXangle(float fAngle);
	void SetState(eAnimationPT in);
	D3DXVECTOR3 getTransformedCoord();
};

