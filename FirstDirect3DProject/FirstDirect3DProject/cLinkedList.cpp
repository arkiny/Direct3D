#include <iostream>

#include "cLinkedList.h"
#include "cNode.h"

cLinkedList::cLinkedList(){
	head = nullptr;
}

cLinkedList::~cLinkedList(){
	cNode* cur = head;
	cNode* precur;
	while (cur->m_pNext == nullptr){
		precur = cur;
		cur = cur->m_pNext;
		delete precur;
	}
}

void cLinkedList::add(int value){
	cNode *newNode = new cNode(value);
	newNode->m_pNext = nullptr;
	if (size == 0){
		head = newNode;
		tail = newNode;
		size++;
	}
	else {
		tail->m_pNext = newNode;
		tail = tail->m_pNext;
		size++;
	}
}

void cLinkedList::printAll(){
	cNode *cur = head;
	std::cout << cur->m_nValue << std::endl;
	while (cur->m_pNext != nullptr){
		cur = cur->m_pNext;
		std::cout << cur->m_nValue << std::endl;
	}
}

void cLinkedList::removebyValue(int value){
	if (size == 0){
		std::cerr << "errer: Nothing to remove." << std::endl;
		return;
	}
	
	cNode *cur = head;
	cNode *ppredNode;

	// iterating
	while (cur != nullptr){
		if (cur->m_nValue == value){
			break;
		}
		ppredNode = cur;
		cur = cur->m_pNext;
	}

	if (cur == nullptr){ // exception
		std::cerr << "errer: No such element : " << value << std::endl; 
		return;
	}
	else if (cur == head){
		head = cur->m_pNext;
		delete cur;
	}
	else if (cur == tail){
		ppredNode->m_pNext = nullptr;
		delete cur;
	}
	else{
		ppredNode->m_pNext = ppredNode->m_pNext->m_pNext;
		delete cur;
	}
	size--;
}

void cLinkedList::removebyIndex(int index){
	if (size == 0){
		std::cerr << "errer: Nothing to remove." << std::endl;
		return;
	}
	else if (index < 0){
		std::cerr << "errer: invalid index (negative). input :" << index << std::endl;
		return;
	}
	else if (index >= size){
		std::cerr << "errer: invalid index. input :" << index << std::endl;
		return;
	}

	cNode *cur = head;
	cNode *ppredNode;
	for (int i = 0; i < index; i++){
		ppredNode = cur;
		cur = cur->m_pNext;
	}

	if (cur == head){
		head = cur->m_pNext;
		delete cur;
	}
	else if (cur == tail){
		ppredNode->m_pNext = nullptr;
		delete cur;
	}
	else{
		ppredNode->m_pNext = ppredNode->m_pNext->m_pNext;
		delete cur;
	}
	size--;
}

int main(){
	cLinkedList input;
	std::cout << "<<< Add >>>" << std::endl;
	for (int i = 0; i < 10; i++){
		input.add(i);
	}

	input.printAll();
	std::cout << "<<< Remove by value >>>" << std::endl;
	input.removebyValue(0);	// remove node which has value 0
	input.removebyValue(3);	// remove node which has value 3
	input.removebyValue(9);	// remove node which has value 9
	input.printAll();
	
	std::cout << "<<< Remove by value Exception >>>" << std::endl;
	input.removebyValue(0); // err no such element
		
	std::cout << "<<< Remove by index >>>" << std::endl;
	input.removebyIndex(1);	// remove node which locates index 1, node which has value 2 would be removed
	input.printAll();

	std::cout << "<<< Remove by value Exception >>>" << std::endl;
	input.removebyIndex(-1); // negative exception
	input.removebyIndex(100); // wrong point exception
	
	system("pause");
}

