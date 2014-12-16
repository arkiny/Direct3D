#pragma once

class cBSTree;
class cParser
{
public:
	cParser();
	~cParser();
	void loadFromFile(const char* fileName);
	void run();
private:
	cBSTree* m_TreeData;
};

