#pragma once
class cNode;

class cLinkedList{
public:
	cLinkedList();
	~cLinkedList();

	void add(int value);

	void removebyValue(int value);
	void removebyIndex(int index);
	
	void printAll();

private:
	cNode* head;
	cNode* tail;
	int size = 0;
};