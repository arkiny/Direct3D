#include <iostream>
#include <Windows.h>
#include "cMain.h"
#include "cParser.h"


cMain::cMain()
{
}


cMain::~cMain()
{
}


int main(){
	std::cout << "p2-1" << std::endl;
	DWORD dwStart = GetTickCount();
	cParser ps;
	ps.loadFromFile("p2-1.txt"); // should be 9
	ps.printHuman();
	//ps.print();
	DWORD dwEnd = GetTickCount();
	std::cout << (dwEnd - dwStart) / 1000.0f << "sec" << std::endl << std::endl;

	std::cout << "p2-2" << std::endl;
	dwStart = GetTickCount();
	cParser ps2;
	ps2.loadFromFile("p2-2.txt");
	//ps.print();
	dwEnd = GetTickCount();
	std::cout << (dwEnd - dwStart) / 1000.0f << "sec" << std::endl;
}