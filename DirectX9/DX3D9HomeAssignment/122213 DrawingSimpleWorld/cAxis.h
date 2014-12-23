#pragma once
class cAxis
{
public:
	cAxis();
	cAxis(float flength);
	~cAxis();

	void init();
	void render();

private:
	std::vector<ST_PC_VERTEX>	m_vecVertexLineXAxis;	
	std::vector<ST_PC_VERTEX>	m_vecVertexLineYAxis;	
	std::vector<ST_PC_VERTEX>	m_vecVertexLineZAxis;

	std::vector<ST_PC_VERTEX>	m_vecVertexLineXPyramid;
	std::vector<ST_PC_VERTEX>	m_vecVertexLineYPyramid;
	std::vector<ST_PC_VERTEX>	m_vecVertexLineZPyramid;
	float						m_fEdgeLength;
};

