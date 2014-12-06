#pragma once

struct sNode{
	int value;
	sNode* pLeft;
	sNode* pRight;
};

class cBSTree
{
public:
	cBSTree();
	~cBSTree();

	//void removeRoot();
	bool insert(int n);

	sNode* deleteByValue(int n);

	bool contains(int n);
	
	void print();
	void deleteMin();
	
	void clear(sNode* node);
private:
	bool insertRec(int n, sNode* cur);
	sNode* getNodebyValue(int n, sNode* cur);

	// get address of the min
	sNode* min(sNode* cur);
	
	// delete the min
	sNode* deleteMin(sNode* cur);
	sNode* deleteByValue(int n, sNode* cur);

	void printRecursiveHelper(sNode* cur);
	sNode* m_pRoot;
	int m_nSize = 0;	
};

