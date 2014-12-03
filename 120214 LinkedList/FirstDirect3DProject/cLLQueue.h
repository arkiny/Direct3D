#pragma once
class cNode;

class cLLQueue
{
public:
	cLLQueue();
	~cLLQueue();

	void enqueue(int n);
	void enqueue(cNode* in);
	cNode* dequeue();
	void print();

	int getSize() { return size; }

private:
	cNode* m_pNodeFront;
	cNode* m_pNodeRear;
	int size = 0;
};

