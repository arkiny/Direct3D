#pragma once

class cNode{
public:
	cNode(int value);
	~cNode();

	void reverse(cNode** ppNext);
public:
	int m_nValue;
	cNode* m_pNext;
};

