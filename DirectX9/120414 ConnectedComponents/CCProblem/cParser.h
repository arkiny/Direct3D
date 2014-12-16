#pragma once
#include <vector>
//#include <queue>
//#include <map>

//struct Person{
//	int nID;
//	std::vector<int> vKnownPerson;
//	bool visited = false;
//};

// vector는 랜덤 억세스가 가능해서 인덱스를 이용해서 억세스를 한다.
// 공간을 늘릴때 꽉찰경우 현재 자기의 사이즈의 2배씩 더 추가해서 allocate한다.
// 따라서 되도록이면 동적할당을 미리 해두도록 한다.

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

