#pragma once
class cMtlTex;

class cVertexPoints
{
private:
	D3DXVECTOR3		m_arrPoints[6];
	LPD3DXMESH		m_pSphereMesh;
	cMtlTex*		m_pMtlTex;
	
public:
	cVertexPoints();
	~cVertexPoints();
	void setup();
	void render();
	D3DXVECTOR3& getPointAt(int a);
};

