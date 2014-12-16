#include <iostream>
#include "cCircularQueue.h"


cCircularQueue::cCircularQueue()
{
}


cCircularQueue::~cCircularQueue()
{
}


void cCircularQueue::enqueue(int n){
	if ((m_nRear + 1) % QUEUE_SIZE == m_nFront){ // full
		return;
	}
	else {
		m_aData[m_nRear] = n;
		m_nRear = (m_nRear + 1) % QUEUE_SIZE;
	}
}

int cCircularQueue::dequeue(){
	if (m_nFront == m_nRear){
		return -1;
	}
	else {
		int ret = m_aData[m_nFront];
		m_nFront = (m_nFront + 1) % QUEUE_SIZE;
		return ret;
	}
}

void cCircularQueue::print(){
	for (int i = m_nFront; i%QUEUE_SIZE != m_nRear; i++){
		std::cout << m_aData[i] << std::endl;
	}
}