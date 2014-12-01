#pragma once

class cNode{
public:
	cNode(int value);
	~cNode();
public:
	int m_nValue;
	cNode* m_pNext;
};

