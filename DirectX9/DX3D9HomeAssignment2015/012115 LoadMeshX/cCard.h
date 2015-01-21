#pragma once

class cGroup;
class cMtlTex;

class cCard : public cGameObject
{
private:
	D3DXVECTOR3							m_vPosition;
	LPD3DXMESH							m_pDrawMesh;
	LPDIRECT3DVERTEXBUFFER9				m_VertexBuffer;
	std::vector<ST_PNT_VERTEX>			m_vecPlane;
	cMtlTex*							m_pMtlTex;

	float								m_fAngle = 0.0f;
	float								m_fAccum = 0.0f;

	SYNTHESIZE(bool, m_bStepped, StepStatus);
	SYNTHESIZE(bool, m_bMatched, MatchedStatus);
	SYNTHESIZE(int, m_nCardType, CardType);

public:
	cCard();
	~cCard();

	void Setup(int nCardType);
	void Update(float delta);
	void Render();


	std::vector<ST_PNT_VERTEX>& GetSurface(){ return m_vecPlane; }
};

