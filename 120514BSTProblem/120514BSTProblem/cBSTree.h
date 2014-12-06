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
	bool remove(int n);

	bool find(int n);
	
	void print();

private:
	bool insertRec(int n, sNode* cur);
	sNode* getNodebyValue(int n, sNode* cur);
	void printRecursiveHelper(sNode* cur);
	sNode* m_pRoot;
	int m_nSize;	
};

