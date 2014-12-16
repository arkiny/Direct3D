#include <iostream>
#include "cFactorial.h"


cFactorial::cFactorial(int n)
{
	m_nvalue = n;
}


cFactorial::~cFactorial()
{
}

void cFactorial::factorial(){
	std::cout << factorialhelper(m_nvalue, 0) << std::endl;
}

int cFactorial::factorialhelper(int n, int accum){
	if (n == 0) return accum;
	else {
		int ac = accum + n;
		return factorialhelper(n - 1, ac);
	}
}