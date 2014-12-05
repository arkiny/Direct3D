#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>

#include "cParser.h"

using namespace std;

cParser::cParser()
{
	// init line database
	m_vLines = new vector < char* > ;
	m_nLineNums = 0;
}


cParser::~cParser()
{
	// dest all
	delete[] visited;
	char *pt;
	while (!m_vLines->empty()){
		pt = m_vLines->back();
		m_vLines->pop_back();
		delete pt;
	}
}


void cParser::loadFromFile(const char* fileName){
	// 최초 설계
	// 해당 숫자만큼의 bool 배열을 만든다.
	// 1을 읽고 bool 배열을 true로 만든다.
	// known person의 주소가 true인지 확인한다.
	// true가 아니면 
	// known person을 큐에 넣는다.
	// 디큐한다. 
	
	// read file to buffer
	fstream read(fileName);
	//int lines;
	// read data size from buffer
	read >> m_nLineNums;
	// init bool array for visit information
	visited = new bool[m_nLineNums];

	// make buffer chunk, but first line will not use.
	int buffer = 5 + 2 + (20 * 5) + 20;
	char* in = new char[buffer];
	read.getline(in, buffer);
	delete in;
	
	// loop 'til data numbers
	for (int i = 0; i < m_nLineNums; i++){
		//make buffer chunk
		char* in = new char[buffer];
		read.getline(in, buffer);
		// pushback into vector
		m_vLines->push_back(in);
		// recheck, visited will be allocated in zero based.
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
	
	// for check human number
	int nhuman = 0;
	// get first dataline from the vector.
	// condition : first line of data should be always true.
	// DataBase Format (p2-1.txt, p2-2.txt)
	// ID numKnown ID1 ID2 ....
	string dataline(m_vLines->at(0));
	stringstream stream(dataline);
	
	int id;
	int numKnown;

	// queue for not checked list.
	// this queue will store unvisited people who are human.
	queue<int> workinglist;
	stream >> id;
	// recheck, visiting informations are allocated ID-1 index.
	visited[id-1] = true;
	// first human added
	nhuman++;
	stream >> numKnown;
	// enqueue the first human list which the first human knows.
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

	// while queue is not empty
	while (workinglist.size() != 0){
		// Get a front person ID and get his human list.
		int currentpeople = workinglist.front();
		workinglist.pop();

		// If he has not yet be visited,
		if (visited[currentpeople - 1] != true){
			stringstream stream(m_vLines->at(currentpeople - 1));
			stream >> id;
			// change the visiting information that this person is visited.
			visited[id - 1] = true;
			stream >> numKnown;
			// human size up!
			nhuman++;
			// Add unvisited humen which is from ID's list to working queue 
			for (int i = 0; i < numKnown; i++){
				int input;
				stream >> input;
				// if the ID hasn't yet visited,
				if (visited[input - 1] != true){
					workinglist.push(input);
				}
				else{
					//do nothing
				}
			}
		}
	}

	// after the workdone,
	// check visited people who are humen from the visiting information
	// for double checking
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
	//int doublecheck = 0;
	for (int i = 0; i < m_nLineNums; i++){
		if (visited[i] == true) {
			// print list of the Human
			cout << i + 1 << " ";
			//doublecheck++;
		}
	}
	cout << endl;
	//cout << "human num double check : " << doublecheck << endl;
}