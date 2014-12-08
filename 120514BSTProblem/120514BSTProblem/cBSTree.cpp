#include <iostream>
#include "cBSTree.h"

using namespace std;

cBSTree::cBSTree()
{
	m_pRoot = nullptr;
}


cBSTree::~cBSTree()
{
	clear(m_pRoot);
	m_nSize = 0;
}

void cBSTree::clear(sNode* node){
	if (node){
		if (node->pLeft) clear(node->pLeft);
		if (node->pRight) clear(node->pRight);
		delete node;
		m_nSize--;
	}
}

bool cBSTree::insert(int n){
	if (m_pRoot == nullptr){
		m_pRoot = new sNode;
		m_pRoot->value = n;
		m_pRoot->pLeft = nullptr;
		m_pRoot->pRight = nullptr;
	}
	else {
		insertRec(n, m_pRoot);
	}
	m_nSize++;
	return true;
}

bool cBSTree::insertRec(int n, sNode* cur){
	if (n < cur->value){
		if (cur->pLeft == nullptr){
			cur->pLeft = new sNode;
			cur->pLeft->value = n;
			cur->pLeft->pLeft = nullptr;
			cur->pLeft->pRight = nullptr;
			return true;
		}
		else{ 
			insertRec(n, cur->pLeft);
		}
		
	}
	else if (n > cur->value) {
		if (cur->pRight == nullptr){
			cur->pRight = new sNode;
			cur->pRight->value = n;
			cur->pRight->pLeft = nullptr;
			cur->pRight->pRight = nullptr;
			return true;
		}
		else{
			insertRec(n, cur->pRight);
		}
	}
	else {
		return false;
	}
	return false;
}

sNode* cBSTree::Min(sNode* cur){
	if (cur == nullptr) return nullptr;
	if (cur->pLeft == nullptr) return cur;
	else Min(cur->pLeft);
}

sNode* cBSTree::deleteMin(sNode* cur){
	//if (cur->pLeft == nullptr) {
	//	if (cur->pRight != nullptr){
	//		parent->pLeft = cur->pRight;
	//		return cur;
	//	}
	//	else{
	//		//delete cur;
	//		//parent->pLeft = nullptr;
	//		parent->pLeft = nullptr;
	//		return cur;
	//	}
	//}
	//else {
	//	deleteMin(cur->pLeft, cur);
	//}

	if (cur->pLeft == nullptr) {
		sNode* ret = cur->pRight;
		delete cur;
		cur = nullptr;
		m_nSize--;
		return ret;
	}
	cur->pLeft = deleteMin(cur->pLeft);
	return cur;
}

void cBSTree::deleteMin(){
	// process time ¡ı∞°...
	sNode* minNode = Min(m_pRoot);
	deleteMin(m_pRoot);
	delete minNode;
	m_nSize--;
}

sNode* cBSTree::deleteByValue(int n, sNode* cur){	
	if (cur == nullptr) return cur;
	else if (n < cur->value) {
		cur->pLeft = deleteByValue(n, cur->pLeft);
		return cur;
	}
	else if (n > cur->value) { 
		cur->pRight = deleteByValue(n, cur->pRight);
		return cur;
	}
	else {
		if (cur->pLeft == nullptr){
			return cur->pRight;
		}
		if (cur->pRight == nullptr){
			return cur->pLeft;
		}
		else{
			sNode t = *cur;
			*cur = *Min(t.pRight);
			cur->pRight = deleteMin(t.pRight);
			cur->pLeft = t.pLeft;
			return cur;
		}
	}
}

sNode* cBSTree::deleteByValue(int n){
	
	if (m_pRoot == nullptr) { 
		//cout << "Nothing to delete" << endl;
		return nullptr; 
	}
	/*else if (m_pRoot->value == n){
		sNode t = *cur;
		*cur = *min(t.pRight);
		cur->pRight = deleteMin(t.pRight, &t);
		cur->pLeft = t.pLeft;
		return cur;
	}*/
	else{
		//sNode* forDelete = getNodebyValue(n, m_pRoot);
		//delete forDelete;
		m_pRoot = deleteByValue(n, m_pRoot);		
		m_nSize--;
	}
}

bool cBSTree::contains(int n){
	return getNodebyValue(n, m_pRoot) != nullptr;
}

sNode* cBSTree::getNodebyValue(int n, sNode* cur){
	if (cur == nullptr) return nullptr;
	if (n < cur->value) return getNodebyValue(n, cur->pLeft);
	else if (n > cur->value) return getNodebyValue(n, cur->pRight);
	else return cur;
}

void cBSTree::printRecursiveHelper(sNode* cur){
	if (cur == nullptr) return;
	printRecursiveHelper(cur->pLeft);
	cout << cur->value << " ";
	printRecursiveHelper(cur->pRight);
}

void cBSTree::print(){
	if (m_pRoot == nullptr) { 
		cout << "nothing to print" << endl; 
		return; 
	}
	printRecursiveHelper(m_pRoot);
	cout << endl;
}
