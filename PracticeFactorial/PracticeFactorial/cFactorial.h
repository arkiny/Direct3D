#pragma once
class cFactorial
{
public:
	cFactorial(int n);
	~cFactorial();

	void factorial();
	int print();

private:
	int m_nvalue;
	int factorialhelper(int n, int accum);
};

