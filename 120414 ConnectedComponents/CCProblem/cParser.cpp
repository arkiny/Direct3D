#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "cParser.h"

using namespace std;

cParser::cParser()
{
	m_vLines = new vector < char* > ;
	m_nLineNums = 0;
}


cParser::~cParser()
{
	delete[] visited;
	char *pt;
	while (!m_vLines->empty()){
		pt = m_vLines->back();
		m_vLines->pop_back();
		delete pt;
	}
}


void cParser::loadFromFile(const char* fileName){
	// 해당 숫자만큼의 bool 배열을 만든다.
	// 1을 읽고 bool 배열을 true로 만든다.
	// known person의 주소가 true인지 확인한다.
	// true가 아니면 
	// known person을 큐에 넣는다.
	// 디큐한다.
	// known person의
	
	fstream read(fileName);
	//int lines;
	read >> m_nLineNums;
	visited = new bool[m_nLineNums];

	char* in = new char[10000];
	read.getline(in, 10000);
	for (int i = 0; i < m_nLineNums; i++){
		char* in = new char[10000];
		read.getline(in, 10000);
		m_vLines->push_back(in);
		visited[i] = false;
		//int id;
		//read >> id;
		//int numofknown;
		//read >> numofknown;
		//Person input;
		//input.nID = id;
		//for (int j = 0; j < numofknown; j++){
		//	int known;
		//	read >> known;
		//	input.vKnownPerson.push_back(known);
		//	input.visited = false;			
		//}
		//m_vStoredVector->push_back(input);
	}

	int nhuman = 0;
	string dataline(m_vLines->at(0));
	stringstream stream(dataline);
	

	int id;
	int numKnown;

	queue<int> workinglist;
	stream >> id;
	visited[id-1] = true;
	nhuman++;
	stream >> numKnown;

	for (int i = 0; i < numKnown; i++){
		int input;
		stream >> input;
		if (visited[input] != true){
			workinglist.push(input);
		}
		else{
			//do nothing
		}
	}

	while (workinglist.size() != 0){
		int currentpeople = workinglist.front();
		workinglist.pop();

		if (visited[currentpeople - 1] != true){
			stringstream stream(m_vLines->at(currentpeople - 1));
			stream >> id;
			visited[id - 1] = true;
			stream >> numKnown;
			nhuman++;
			for (int i = 0; i < numKnown; i++){
				int input;
				stream >> input;
				if (visited[input - 1] != true){
					workinglist.push(input);
				}
				else{
					//do nothing
				}
			}
		}
	}

	int doublecheck = 0;
	for (int i = 0; i < m_nLineNums; i++){
		if (visited[i] == true) {
			//cout << i + 1 << " ";
			doublecheck++;
		}
	}

	//cout << endl;
	// using size
	cout << "human num : " << nhuman << endl;
	// using bool array
	cout << "human num double check : " << doublecheck << endl;

	/*FILE* fp;
	errno_t err;
	err = fopen_s(&fp, fileName, "r");
	if (err != 0){
		cerr << "File read Error" << endl;
		return NULL;
	}
	int nSize;
	while (!feof(fp)){
			
	}*/
}

void cParser::print(){
	int size = m_vLines->size();
	for (int i = 0; i < size; i++){
		string a(m_vLines->at(i));
		cout <<  a  << endl;
		cout << visited[i] << endl;
	}
	cout << size << endl;
}

void cParser::printHuman(){
	int doublecheck = 0;
	for (int i = 0; i < m_nLineNums; i++){
		if (visited[i] == true) {
			cout << i + 1 << " ";
			doublecheck++;
		}
	}
	cout << endl;
	cout << "human num double check : " << doublecheck << endl;
}