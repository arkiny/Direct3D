#pragma once
class cNode;

class cStackLL
{
public:
	cStackLL();
	~cStackLL();

	void push(int in);
	int pop();
	void print();

private:
	cNode* m_pNodetop;
};

