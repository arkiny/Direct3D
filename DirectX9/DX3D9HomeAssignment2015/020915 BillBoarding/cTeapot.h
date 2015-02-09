#pragma once

class cMtlTex;
class cVertexPoints;

class cTeapot
{
public : 
	enum eINTERPOLATIONTYPE{ eLinear, eBezier };
private:
	LPD3DXMESH		m_pMesh;
	cMtlTex*		m_pMtlTex;
	float			fAccum = 0.0f;
	float			fPrevTime = 0.0f;

	D3DXVECTOR3		m_vecStart;
	D3DXVECTOR3		m_vecPos;
	D3DXVECTOR3		m_vecPos2;
	D3DXVECTOR3		m_vecPos3;
	D3DXVECTOR3     m_vecPos4;
	D3DXVECTOR3		m_vecTarget;
	D3DXVECTOR3		m_vecTarget2;
	D3DXVECTOR3		m_vecFront;
	D3DXVECTOR3		m_vecFront2;
	float			m_fDist;
	cVertexPoints*	m_pTargets;
	int				m_nTargetIndex = 1;
	float			m_fAngle = 0.0f;
	eINTERPOLATIONTYPE	m_eType = eLinear;
public:
	cTeapot();
	~cTeapot();
	void setPos(D3DXVECTOR3& vec);

	void setup(cVertexPoints* points, eINTERPOLATIONTYPE type);
	void update(float delta);
	void render();

	void linear(D3DXVECTOR3& prev, D3DXVECTOR3& next);

};

