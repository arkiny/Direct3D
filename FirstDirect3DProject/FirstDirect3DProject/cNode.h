#pragma once

class cNode{
public:
	cNode(int value);
	~cNode();
public:
	int m_nValue;
	cNode* m_pNext;
};

class cLinkedList{
public:
	cLinkedList();
	~cLinkedList();

	void add(int value);
	void remove(int value); 
	void printAll();

private:
	cNode* head;
	cNode* tail;
	int size = 0;
};