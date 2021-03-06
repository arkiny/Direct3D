#pragma once
class cMyCube
{
public:
	cMyCube(D3DXVECTOR3 origin, float edgeLength);
	~cMyCube();
	void init();
	void update(float delta);
	void render();

private:
	D3DXVECTOR3					m_vec3Origin;
	std::vector<ST_PC_VERTEX>	m_vecVertex;
	float						m_fEdgeLength;
};

