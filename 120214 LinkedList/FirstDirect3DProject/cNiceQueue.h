#pragma once

class cNode;
class cLLQueue;

class cNiceQueue
{
public:
	cNiceQueue();
	~cNiceQueue();

	void enqueue(int i);
	cNode* dequeue();
	void print();
	void printPool();

private:
	cLLQueue* m_pMainQueue;
	cLLQueue* m_pMemoryPoolQueue;
};

