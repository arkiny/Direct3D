#pragma once

class cTile;

class cPriorityQueue
{
private:
	std::vector<cTile*>	m_vecContainer;
	int					m_nNextIndex	= 0;
	int					m_nCurLevel		= 0;

public:
	cPriorityQueue();
	~cPriorityQueue();
	cPriorityQueue(int nSize);
	
	void	Push(cTile* pTile);
	cTile*	Pop();
	bool	IsEmpty(){ return m_vecContainer.size() != 0; }

	void	RefreshUp(cTile* pTile);
	int		GetIndexOf(cTile* pTile);
	void	Swap(int index1, int index2);
	void	CheckParentAndSwap(int Index);
	void	Resize(int size);

	void	CheckChildAndSwap(int Index);
	void	ToString();
};

