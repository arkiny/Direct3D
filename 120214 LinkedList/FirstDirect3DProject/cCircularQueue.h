#pragma once

#define QUEUE_SIZE 6

class cCircularQueue
{
public:
	cCircularQueue();
	~cCircularQueue();

	void enqueue(int n);
	int dequeue();
	void print();

private:
	int m_nFront = 0;
	int m_nRear = 0;
	int m_aData[QUEUE_SIZE];
};

