#include "cBSTree.h"


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
}

bool cBSTree::insertRec(int n, sNode* cur){
	if (n < cur->value){
		if (cur->pLeft = nullptr){
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
	else {
		if (cur->pLeft = nullptr){
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
	
}

bool cBSTree::find(int n){
	if (m_pRoot == nullptr) return false;
	if (m_pRoot->value == n) return true;
	if (n < m_pRoot->value){
		
	}
	else {

	}
}

void cBSTree::print(){

}
