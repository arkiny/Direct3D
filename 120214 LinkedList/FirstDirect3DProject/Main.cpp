#include <iostream>
#include <time.h>
#include <Windows.h>
#include "cLinkedList.h"
#include "cStackArr.h"
#include "cStackLL.h"
#include "cCircularQueue.h"
#include "cLLQueue.h"
#include "cNiceQueue.h"

int main(){
	/*cLinkedList input;
	std::cout << "<<< Add >>>" << std::endl;
	for (int i = 0; i < 10; i++){
	input.add(i);
	}

	input.printAll();

	std::cout << "<<< Reverse >>>" << std::endl;
	input.reverse();
	input.printAll();

	std::cout << "<<< Reverse Recursively >>>" << std::endl;
	input.recursiveReverse();
	input.printAll();

	cLinkedList ll;
	std::cout << "<<< Add for Sorting >>>" << std::endl;
	ll.add(11);
	ll.add(1);
	ll.add(1111);
	ll.add(111);
	ll.printAll();

	std::cout << "<<< After QuickSorted >>>" << std::endl;
	ll.quickSort();
	ll.printAll();*/

	//std::cout << "<<< Remove by value >>>" << std::endl;
	//input.removebyValue(0);	// remove node which has value 0
	//input.removebyValue(3);	// remove node which has value 3
	//input.removebyValue(9);	// remove node which has value 9
	//input.printAll();
	//
	//std::cout << "<<< Remove by value Exception >>>" << std::endl;
	//input.removebyValue(0); // err no such element
	//	
	//std::cout << "<<< Remove by index >>>" << std::endl;
	//input.removebyIndex(1);	// remove node which locates index 1, node which has value 2 would be removed
	//input.printAll();

	//std::cout << "<<< Remove by value Exception >>>" << std::endl;
	//input.removebyIndex(-1); // negative exception
	//input.removebyIndex(100); // wrong point exception

	//std::cout << "<<< Add for recursive remove >>>" << std::endl;
	//input.add(13);
	//input.add(3);
	//input.add(13);
	//input.printAll();

	//std::cout << "<<< Remove with recursive remove >>>" << std::endl;
	//input.removeAllbyValue(13);
	//input.printAll();

	//cLinkedList ll;
	//ll.removebyValue(1);	// exception
	//ll.add(1);				// add 1 to linkedlist
	//ll.removebyValue(2);	// exception: no such element
	//ll.removebyValue(1);	// delete
	//ll.removebyValue(0);	// exception: size 0
	//ll.add(1);				// add 1 to linkedlist
	//ll.add(2);				// add 2 to linkedlist
	//ll.printAll();			// printall

	std::cout << "<<<Stack Array>>>" << std::endl;
	cStackArr sa;
	sa.Push(0);
	sa.Push(1);
	sa.Push(2);
	sa.Push(3);
	sa.Push(4);
	sa.Print();

	std::cout << "<<<Stack LL>>>" << std::endl;
	cStackLL sl;
	sl.push(0);
	sl.push(1);
	sl.push(2);
	sl.push(3);
	sl.push(4);
	sl.print();

	std::cout << "<<<Circular Queue>>>" << std::endl;
	cCircularQueue cq;
	cq.enqueue(0);
	cq.enqueue(1);
	cq.enqueue(2);
	cq.enqueue(3);
	cq.enqueue(4);
	cq.print();

	std::cout << "<<<Circular Queue after dequeue enqueue>>>" << std::endl;
	cq.dequeue();
	cq.enqueue(5);
	cq.enqueue(6); // do nothing

	cq.print();

	std::cout << "<<<Circular Queue after dequeue All(OverDequeue)>>>" << std::endl;
	cq.dequeue();
	cq.dequeue();
	cq.dequeue();
	cq.dequeue();
	cq.dequeue();
	cq.dequeue();
	cq.enqueue(7);
	cq.enqueue(8);
	cq.enqueue(9);
	cq.print();

	std::cout << "<<<Linked List Queue Enqueue>>>" << std::endl;
	cLLQueue lq;
	lq.enqueue(0);
	lq.enqueue(1);
	lq.enqueue(2);
	lq.enqueue(3);
	lq.enqueue(4);
	lq.print();

	std::cout << "<<<Linked List Queue after dequeue>>>" << std::endl;
	lq.dequeue();
	lq.dequeue();
	lq.print();

	std::cout << "<<<NiceQueue Enqueue" << std::endl;
	cNiceQueue nq;
	nq.enqueue(0);
	nq.enqueue(1);
	nq.enqueue(2);
	nq.enqueue(3);
	nq.enqueue(4);
	nq.print();

	std::cout << "<<<NiceQueue Enqueue" << std::endl;
	nq.dequeue();
	nq.dequeue();
	nq.print();
	std::cout << "<<<NiceQueue MemoryPool" << std::endl;
	nq.printPool();

	std::cout << "<<<NiceQueue Enqueue Again using MemoryPool>>>" << std::endl;
	nq.enqueue(5);
	nq.print();
	std::cout << "<<<NiceQueue MemoryPool after using it>>>" << std::endl;
	nq.printPool();


	std::cout << "<<<Performance Test>>>" << std::endl;
	cLLQueue lqP;
	cNiceQueue nqP;
	
	unsigned int starttime = GetTickCount();
	for (int j = 0; j < 5000; j++){
		for (int i = 0; i < 5000; i++){
			lqP.enqueue(i);
		}
		for (int i = 0; i < 5000; i++){
			lqP.dequeue();
		}
	}
	unsigned int endtime = GetTickCount();
	unsigned int diff = endtime - starttime;
	std::cout << "list queue : " << diff << "ms" << std::endl;

	starttime = GetTickCount();
	for (int j = 0; j < 5000; j++){
		for (int i = 0; i < 5000; i++){
			nqP.enqueue(i);
		}
		for (int i = 0; i < 5000; i++){
			nqP.dequeue();
		}
	}
	endtime = GetTickCount();
	diff = endtime - starttime;
	std::cout << "nice queue : " << diff << "ms" << std::endl;

	system("pause");
}