#pragma once
class cMyCube
{
public:
	cMyCube(D3DXVECTOR3 origin, float edgeLength);
	~cMyCube();
	void init();
	void update(float delta);
	void render();
	D3DXVECTOR3& getPosition(){ return m_vec3Origin; }
	//D3DXVECTOR3& getPos();
private:
	D3DXVECTOR3					m_vec3Origin;
	D3DXVECTOR3					m_vecForward;
	float						m_fAngleDegree;
	float						m_fSpeed;

	std::vector<ST_PC_VERTEX>	m_vecVertex;
	float						m_fEdgeLength;	
};

