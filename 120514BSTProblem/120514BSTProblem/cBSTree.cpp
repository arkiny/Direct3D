#include <iostream>
#include "cBSTree.h"

using namespace std;

cBSTree::cBSTree()
{
	m_pRoot = nullptr;
}


cBSTree::~cBSTree()
{
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
	return false;
}

bool cBSTree::remove(int n){
	return true;
}

bool cBSTree::find(int n){
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
	printRecursiveHelper(m_pRoot);
	cout << endl;
}
