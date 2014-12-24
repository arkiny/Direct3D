#pragma once
class cGrid
{
public:
	cGrid();
	
	~cGrid();
	cGrid(float length, int numOfGrid);
	void init();
	void render();

private:
	float m_fLength;
	int m_nGridNum; // should be power of 2
	std::vector<ST_PC_VERTEX>	m_vecVertexLineXGrid; 
	//std::vector<ST_PC_VERTEX>	m_vecVertexLineZGrid;
};

