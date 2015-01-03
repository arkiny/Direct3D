#pragma once
class cPyramid
{
public:
	cPyramid();
	~cPyramid();

	void setup();
	void render();

private:
	D3DMATERIAL9				m_stMaterialLineX;
	D3DMATERIAL9				m_stMaterialLineY;
	D3DMATERIAL9				m_stMaterialLineZ;

	std::vector<ST_PN_VERTEX>	m_vecVertexLineXPyramid;
	std::vector<ST_PN_VERTEX>	m_vecVertexLineYPyramid;
	std::vector<ST_PN_VERTEX>	m_vecVertexLineZPyramid;
	float						m_fEdgeLength;
};

