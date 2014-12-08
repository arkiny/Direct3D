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

sNode* cBSTree::min(sNode* cur){
	if (cur == nullptr) return nullptr;
	if (cur->pLeft == nullptr) return cur;
	else min(cur->pLeft);
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
		m_nSize--;
		return ret;
	}
	cur->pLeft = deleteMin(cur->pLeft);
	return cur;
}

void cBSTree::deleteMin(){
	// process time ¡ı∞°...
	sNode* minNode = min(m_pRoot);
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

			/*Node t = x;
			x = min(t.right);
			x.right = deleteMin(t.right);
			x.left = t.left;*/

			sNode t = *cur;
			*cur = *min(t.pRight);			
			cur->pRight = deleteMin(t.pRight);
			cur->pLeft = t.pLeft;
			return cur;
		}
	}
	/*if (cur == nullptr) return cur;
	else if (n < cur->value) deleteByValue(n, cur->pLeft);
	else if (n > cur->value) deleteByValue(n, cur->pRight);
	else {
	if (cur->pLeft == nullptr) {
	if (cur->pRight == nullptr){
	sNode* rep = nullptr;
	*cur = rep;
	}
	else {
	*cur = *cur->pRight;
	}
	return cur;
	}
	if (cur->pRight == nullptr) {
	if (cur->pLeft == nullptr){
	*cur = *cur->pLeft;
	}
	else {
	*cur = *cur->pLeft;
	}
	return cur;
	}
	sNode* t = cur;
	cur = min(cur);

	*cur->pLeft = *deleteMin(t->pRight);
	*cur->pRight = *t->pLeft;
	}
	return cur;*/

	//if (cur == nullptr) return nullptr;
	//else if (n < cur->value) deleteByValue(n, cur->pLeft, cur);
	//else if (n < cur->value) deleteByValue(n, cur->pRight, cur);
	//else {
	//	
	//}
	
	/*if (cur == nullptr) return nullptr;	
	if (cur->pLeft->value == n){
		if (cur->pLeft->pLeft == nullptr){
			cur->pLeft = cur->pLeft->pRight;
		} 
		else if (cur->pLeft->pRight == nullptr){
			cur->pLeft = cur->pLeft->pLeft;			
		}
		else {
			sNode* t = cur->pLeft;
			cur->pLeft = min(cur->pLeft);
			cur->pLeft->pLeft = deleteMin(t->pRight, t);
			cur->pLeft->pRight = t->pLeft;
		}
		return cur->pLeft;
	}
	if (cur->pRight->value == n){
		if (cur->pRight->pLeft == nullptr){
			cur->pRight = cur->pRight->pRight;
		}
		else if (cur->pRight->pRight == nullptr){
			cur->pRight = cur->pRight->pLeft;
		}
		else {
			sNode* t = cur->pRight;
			cur->pRight = min(cur->pRight);
			cur->pRight->pLeft = deleteMin(t->pRight, t);
			cur->pRight->pRight = t->pLeft;
		}
		return cur->pRight;
	}

	if (n < cur->value) {
		deleteByValue(n, cur->pLeft); 
	}
	if (n > cur->value) {
		deleteByValue(n, cur->pRight);
	}
	return cur;*/

	/*if (cur == nullptr) return cur;
	else if (n < cur->value) deleteByValue(n, cur->pLeft);
	else if (n > cur->value) deleteByValue(n, cur->pRight);
	else {
	if (cur->pLeft == nullptr) {
	if (cur->pRight == nullptr){
	sNode* rep = nullptr;
	*cur = rep;
	}
	else {
	*cur = *cur->pRight;
	}
	return cur;
	}
	if (cur->pRight == nullptr) {
	if (cur->pLeft == nullptr){
	*cur = *cur->pLeft;
	}
	else {
	*cur = *cur->pLeft;
	}
	return cur;
	}
	sNode* t = cur;
	cur = min(cur);

	*cur->pLeft = *deleteMin(t->pRight);
	*cur->pRight = *t->pLeft;
	}
	return cur;*/
}

sNode* cBSTree::deleteByValue(int n){
	
	if (m_pRoot == nullptr) return nullptr;
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
	printRecursiveHelper(m_pRoot);
	cout << endl;
}
