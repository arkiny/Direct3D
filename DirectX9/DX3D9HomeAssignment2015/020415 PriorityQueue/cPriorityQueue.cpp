#include "stdafx.h"
#include "cPriorityQueue.h"
#include "cTile.h"


cPriorityQueue::cPriorityQueue()
{
	//m_vecContainer.resize(2 * m_nCurLevel - 1);
	//m_vecContainer.resize(1);
}

cPriorityQueue::~cPriorityQueue()
{
	//for (auto p : m_vecContainer){}
}


cPriorityQueue::cPriorityQueue(int size)
{
	m_vecContainer.resize(size);
}


void	cPriorityQueue::Resize(int size){
	//if (size > m_vecContainer.size()){
	//	m_vecContainer.resize(size);
	//}
}
void	cPriorityQueue::Push(cTile* pTile){
	//m_vecContainer[m_nNextIndex] = pTile;

	//m_nNextIndex++;
	//if (m_nCurLevel * 2 + 1 <= m_nNextIndex){
	//	m_nCurLevel++;
	//	m_vecContainer.resize(m_nCurLevel * 2 + 1);
	//}
	m_vecContainer.push_back(pTile);
	CheckParentAndSwap(m_vecContainer.size() - 1);
}

cTile*	cPriorityQueue::Pop(){
	//if (m_nNextIndex == 0){
	//	return NULL;
	//}
	//m_nNextIndex--;
	if (m_vecContainer.empty()){
		return NULL;
	}
	cTile* ret = m_vecContainer.front();
	m_vecContainer[0] = m_vecContainer.back();
	m_vecContainer.pop_back();
	CheckChildAndSwap(0);

	//m_vecContainer[0] = m_vecContainer[m_nNextIndex];
	//m_vecContainer[m_nNextIndex] = NULL;
	//CheckChildAndSwap(0);
	//m_vecContainer.pop_back();

	return ret;
}

void	cPriorityQueue::RefreshUp(cTile* pTile){
	int index = GetIndexOf(pTile);
	if (index == -1) return;

	CheckParentAndSwap(index);
}

int		cPriorityQueue::GetIndexOf(cTile* p){
	for (size_t i = 0; i < m_vecContainer.size(); i++){
		if (p == m_vecContainer[i]){
			return i;
		}
	}
	return -1;
}

void	cPriorityQueue::Swap(int index1, int index2){
	cTile* temp = m_vecContainer[index1];
	m_vecContainer[index1] = m_vecContainer[index2];
	m_vecContainer[index2] = temp;
}

void	cPriorityQueue::CheckParentAndSwap(int index){
	if (index == 0){
		return;
	}
	int parentIndex = (index - 1) / 2;

	float cur = m_vecContainer[index]->GetFGH().m_fF;
	float parent = m_vecContainer[parentIndex]->GetFGH().m_fF;

	// Playing Recursive
	if (cur < parent){
		Swap(index, parentIndex);
		CheckParentAndSwap(parentIndex);
	}
	else{
		return;
	}
}

void	cPriorityQueue::CheckChildAndSwap(int index){
	if (index >= m_vecContainer.size()){
		return;
	}

	int rcIndex = index * 2 + 1;
	int lcIndex = index * 2 + 2;

	if (rcIndex >= m_vecContainer.size() || lcIndex >= m_vecContainer.size()) return;

	float cur = m_vecContainer[index]->GetFGH().m_fF;
	float rc = -1.0f;
	float lc = -1.0f;

	if (m_vecContainer[rcIndex]){
		rc = m_vecContainer[rcIndex]->GetFGH().m_fF;
	}
	if (m_vecContainer[lcIndex]){
		lc = m_vecContainer[lcIndex]->GetFGH().m_fF;
	}

	if (lc < rc){
		if (cur >= lc){
			Swap(index, lcIndex);
			CheckChildAndSwap(lcIndex);
		}
		else{
			return;
		}
	}
	else{
		if (cur >= rc){
			Swap(index, rcIndex);
			CheckChildAndSwap(rcIndex);
		}
		else{
			return;
		}
	}
}

void	cPriorityQueue::ToString(){
	for (int i = 0; i < m_vecContainer.size(); i++){
		std::cout << m_vecContainer[i]->GetFGH().m_fF << " ";
	}
	std::cout << std::endl;
}