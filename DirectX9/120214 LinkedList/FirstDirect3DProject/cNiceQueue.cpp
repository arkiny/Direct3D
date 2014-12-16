#include "cNiceQueue.h"
#include "cLLQueue.h"
#include "cNode.h"

cNiceQueue::cNiceQueue()
{
	m_pMainQueue = new cLLQueue;
	m_pMemoryPoolQueue = new cLLQueue; 
}


cNiceQueue::~cNiceQueue()
{
	delete m_pMainQueue;
	delete m_pMemoryPoolQueue;
}

void cNiceQueue::enqueue(int i){
	if (m_pMemoryPoolQueue->getSize() == 0){
		m_pMainQueue->enqueue(i);
	}
	else {
		cNode* in = m_pMemoryPoolQueue->dequeue();
		in->m_nValue = i;
		in->m_pNext = nullptr;
		m_pMainQueue->enqueue(in);
	}
}

cNode* cNiceQueue::dequeue(){
	if (m_pMainQueue->getSize() == 0){
		return nullptr;
	}
	else{
		cNode* ret = m_pMainQueue->dequeue();
		ret->m_pNext = nullptr;
		m_pMemoryPoolQueue->enqueue(ret);
		return ret;
	}
}

void cNiceQueue::print(){
	m_pMainQueue->print();
}

void cNiceQueue::printPool(){
	m_pMemoryPoolQueue->print();
}