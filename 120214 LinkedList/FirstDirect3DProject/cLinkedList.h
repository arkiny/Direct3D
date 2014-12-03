#pragma once
class cNode;

class cLinkedList{
public:
	cLinkedList();
	~cLinkedList();

	void add(int value);

	void removebyValue(int value);
	void removebyIndex(int index);
	void removeAllbyValue(int value);
	
	void destroy();
	void reverse();
	void recursiveReverse();

	void printAll();
	cNode* getTail() { return tail; }
	cNode* getHead() { return head; }

	cNode* quickSort();


private:
	cNode* head;
	cNode* tail;
	int size = 0;

	void reverseHelper(cNode* cursor, cNode* prev);
	void recursiveRemove(int value, cNode* cursor);

	cNode* partition(cNode* head, cNode* tail, cNode** nHead, cNode** nTail);
	cNode* quicksortRecurively(cNode* head, cNode* tail);
};