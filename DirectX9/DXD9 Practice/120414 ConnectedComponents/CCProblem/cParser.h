#pragma once
#include <vector>
//#include <queue>
//#include <map>

//struct Person{
//	int nID;
//	std::vector<int> vKnownPerson;
//	bool visited = false;
//};

// vector�� ���� �＼���� �����ؼ� �ε����� �̿��ؼ� �＼���� �Ѵ�.
// ������ �ø��� ������� ���� �ڱ��� �������� 2�辿 �� �߰��ؼ� allocate�Ѵ�.
// ���� �ǵ����̸� �����Ҵ��� �̸� �صε��� �Ѵ�.

class cParser
{
public:
	// init parser
	cParser();
	~cParser();

	void loadFromFile(const char* fileName);
	void print();
	void printHuman();

private:
	// Size of Data
	int m_nLineNums;
	// Store Raw Data per Line from File
	std::vector<char*>* m_vLines;
	// Visited Informations
	bool *visited;
};
