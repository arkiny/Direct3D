#include <fstream>
#include <iostream>

#include "cParser.h"
#include "cBSTree.h"

using namespace std;

cParser::cParser()
{
	m_TreeData = new cBSTree;
}


cParser::~cParser()
{
	delete m_TreeData;
}

void cParser::loadFromFile(const char* fileName){
	fstream read(fileName);
	char command;
	char dump;
	int data;

	while (!read.eof()){
		read >> command;		
		switch (command)
		{
		case 'i':
			read >> dump;
			read >> data;
			m_TreeData->insert(data);
			break;
		case 'd':
			read >> dump;
			read >> data;
			m_TreeData->deleteByValue(data);
			break;
		case 'p':
			m_TreeData->print();
			break;
		case 'f':
			read >> dump;
			read >> data;
			if (m_TreeData->contains(data)){
				cout << "Tree contains " << data << endl;
			}
			else {
				cout << "Tree does not contains " << data << endl;
			}
			break;
		default:
			break;
		}
	}

}

void cParser::run(){

}