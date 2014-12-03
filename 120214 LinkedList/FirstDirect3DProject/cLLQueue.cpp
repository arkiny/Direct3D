#include "cLLQueue.h"

#include <iostream>
#include "cNode.h"

cLLQueue::cLLQueue()
{
	m_pNodeFront = nullptr;
	m_pNodeRear = m_pNodeFront;
}


cLLQueue::~cLLQueue()
{

}


void cLLQueue::enqueue(int n){
	cNode* npNode = new cNode(n);

	if (m_pNodeFront == nullptr && m_pNodeRear == nullptr){
		m_pNodeFront = npNode;
		m_pNodeRear = m_pNodeFront;
		size++;
	}
	else {
		m_pNodeRear->m_pNext = npNode;
		m_pNodeRear = m_pNodeRear->m_pNext;
		size++;
	}
}

void cLLQueue::enqueue(cNode* in){
	if (m_pNodeFront == nullptr && m_pNodeRear == nullptr){
		m_pNodeFront = in;
		m_pNodeRear = m_pNodeFront;
		size++;
	}
	else {
		m_pNodeRear->m_pNext = in;
		m_pNodeRear = m_pNodeRear->m_pNext;
		size++;
	}
}

cNode* cLLQueue::dequeue(){
	if (size == 0){
		return nullptr; // empty
	}
	else if (m_pNodeFront == m_pNodeRear){
		cNode* ret = m_pNodeFront;
		m_pNodeFront = nullptr;
		m_pNodeRear = m_pNodeFront;
		size--;
		return ret;
	}
	else {
		cNode* ret = m_pNodeFront;
		//int ret = m_pNodeFront->m_nValue;
		m_pNodeFront = m_pNodeFront->m_pNext;
		//delete temp;
		size--;
		return ret;
	}
}

void cLLQueue::print(){
	cNode* cur = m_pNodeFront;
	while (cur){
		std::cout << cur->m_nValue << std::endl; 
		cur = cur->m_pNext;
	}
}