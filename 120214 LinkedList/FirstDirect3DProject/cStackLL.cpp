#include <iostream>
#include "cNode.h"
#include "cStackLL.h"

cStackLL::cStackLL()
{
	m_pNodetop = nullptr;
}

cStackLL::~cStackLL()
{
	//cNode* cur = m_pNodetop;
	while (m_pNodetop != nullptr){
		this->pop();
	}
}

void cStackLL::push(int n){
	cNode* npNode = new cNode(n);
	if (m_pNodetop == nullptr){
		m_pNodetop = npNode;
		m_pNodetop->m_pNext = nullptr;
	}
	else{
		npNode->m_pNext = m_pNodetop;
		m_pNodetop = npNode;
	}
}

int cStackLL::pop(){
	int ret;
	if (m_pNodetop == nullptr){
		return -1;
	}
	else {
		ret = m_pNodetop->m_nValue;
		cNode* cur = m_pNodetop;
		m_pNodetop = m_pNodetop->m_pNext;
		delete cur;
	}
	return ret;
}

void cStackLL::print(){
	cNode* cur = m_pNodetop;
	while (cur){
		std::cout << cur->m_nValue << std::endl;
		cur = cur->m_pNext;
	}
}