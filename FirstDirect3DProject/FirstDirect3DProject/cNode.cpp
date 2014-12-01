#include <iostream>
#include "cNode.h"

cNode::cNode(int value){
	m_nValue = value;
}

cNode::~cNode(){
}

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


int main(){
	cLinkedList input;
	for (int i = 0; i < 10; i++){
		input.add(i);
	}
	input.printAll();
	
}