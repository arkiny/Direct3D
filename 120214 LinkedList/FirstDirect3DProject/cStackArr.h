#pragma once
#define STACK_SIZE 5

class cStackArr
{
private:
	int m_aData[STACK_SIZE];
	int m_nTop;

public:
	cStackArr(void);
	~cStackArr(void);

	void Push(int n);
	void Pop();
	void Print();
};
