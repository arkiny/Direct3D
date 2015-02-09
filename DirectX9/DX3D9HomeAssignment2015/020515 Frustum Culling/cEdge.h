#pragma once
class cEdge
{

private:
	std::vector<ST_PC_VERTEX> m_vecVertex;
public:
	cEdge();
	~cEdge();

	void Setup(D3DXVECTOR3 from, D3DXVECTOR3 to);
	void Render();
};

