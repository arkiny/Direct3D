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
		size--;
	}

	head = nullptr;
}

void cLinkedList::destroy(){
	cLinkedList::~cLinkedList();
}

void cLinkedList::reverse(){
	cNode* prev = nullptr;
	cNode* next;
	while (head){
		next = head->m_pNext;
		head->m_pNext = prev;
		prev = head;
		if (next == nullptr) break;
		head = next;
	}	
}

void cLinkedList::recursiveReverse(){
	tail = head;
	reverseHelper(head, nullptr);
}

void cLinkedList::reverseHelper(cNode* cursor, cNode* prev){
	// base case if next node is tail
	if (cursor->m_pNext == nullptr){
		cursor->m_pNext = prev;
		head = cursor;
		return;
	}
	// fail case if cursor is null(head)
	else if (cursor == nullptr){
		return;
	}
	// else change order
	else{
		cNode* next;
		next = cursor->m_pNext;
		cursor->m_pNext = prev;
		reverseHelper(next, cursor);
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


// helper for removeAllbyValue
void cLinkedList::recursiveRemove(int value, cNode* cursor){
	if (!cursor){
		return;
	}
	
	cNode* cur = cursor;
	cur = cur->m_pNext;
	
	if (cur && cur->m_nValue == value){
		if (cur == head){
			head = cur->m_pNext;
			delete cur;
			cur = cursor->m_pNext;
			size--;
		}
		else if (cur == tail){
			tail = cursor;
			cursor->m_pNext = nullptr;
			delete cur;
			cur = cursor->m_pNext;
			size--;
		}
		else{
			cursor->m_pNext = cursor->m_pNext->m_pNext;
			delete cur;
			cur = cursor->m_pNext;
			size--;
		}
	}

	recursiveRemove(value, cur);
}

// 재귀함수를 이용해 링크내 같은 value 모두 지우기
void cLinkedList::removeAllbyValue(int value){
	if (size == 0){
		std::cerr << "errer: Nothing to remove." << std::endl;
		return;
	}
	tail = head;
	recursiveRemove(value, head);
}

// 가장 앞의 value 하나 지우기
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
		tail = ppredNode;
		ppredNode->m_pNext = nullptr;
		delete cur;
	}
	else{
		ppredNode->m_pNext = ppredNode->m_pNext->m_pNext;
		delete cur;
	}
	size--;
}

// 0 based index 노드 지우기
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

cNode* cLinkedList::partition(cNode* first, cNode* last, cNode** nHead, cNode** nTail){
	cNode* pivot = last;
	cNode* prev = nullptr, *cur = first, *tail = pivot;
	
	// sorting this partition
	while (cur != pivot){
		// if cursor value is less than pivot(the last)
		// cursor just move right
		if (cur->m_nValue < pivot->m_nValue){
			if ((*nHead) == nullptr){
				(*nHead) = cur;
			}

			prev = cur;
			cur = cur->m_pNext;
		}
		else{
			//swap
			if (prev)
				prev->m_pNext = cur->m_pNext;

			cNode* temp = cur->m_pNext;
			cur->m_pNext = nullptr;
			tail->m_pNext = cur;
			tail = cur;
			cur = temp;
		}
	}
	
	if ((*nHead) == nullptr){
		(*nHead) = pivot;
	}
	(*nTail) = tail;

	return pivot;
}

cNode* cLinkedList::quicksortRecurively(cNode* head, cNode* tail){
	if (!head || head == tail){
		return head;
	}
	cNode* newHead = nullptr, *newEnd = nullptr;

	//left side
	cNode* pivot = partition(head, tail, &newHead, &newEnd);

	if (newHead != pivot){
		cNode *temp = newHead;
		while (temp->m_pNext != pivot){
			temp = temp->m_pNext;
		}
		temp->m_pNext = nullptr;

		newHead = quicksortRecurively(newHead, temp);
		cNode *cur = newHead;
		// to get new tail
		while (cur->m_pNext!=nullptr){
			cur = cur->m_pNext;
		}
		cur->m_pNext = pivot;
	}

	// rightside
	pivot->m_pNext = quicksortRecurively(pivot->m_pNext, newEnd);
	return newHead;
}

cNode* cLinkedList::quickSort(){
	head = quicksortRecurively(head, tail);
	cNode *cur = head;
	// tail update
	while (cur->m_pNext != nullptr){
		cur = cur->m_pNext;
	}
	tail = cur;
	return head;
}

