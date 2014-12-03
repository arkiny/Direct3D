#include <iostream>
#include "cStackArr.h"

cStackArr::cStackArr(void)
: m_nTop(-1)
{
}

cStackArr::~cStackArr(void)
{
}

void cStackArr::Push(int n)
{
	if (m_nTop >= STACK_SIZE - 1)
		return;
	++m_nTop;
	m_aData[m_nTop] = n;
}

void cStackArr::Pop()
{
	if (m_nTop < 0)
		return;
	--m_nTop;
}

void cStackArr::Print(){
	for (int i = m_nTop; i >= 0; i--){
		std::cout << m_aData[i] << std::endl;
	}
}