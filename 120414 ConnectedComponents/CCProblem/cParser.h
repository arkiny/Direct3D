#pragma once
#include <vector>
#include <queue>
#include <map>

struct Person{
	int nID;
	std::vector<int> vKnownPerson;
	bool visited = false;
};

class cParser
{
public:
	cParser();
	~cParser();

	void loadFromFile(const char* fileName);
	void print();
	void printHuman();

private:
	int m_nLineNums;
	std::vector<char*>* m_vLines;
	bool *visited;
};

