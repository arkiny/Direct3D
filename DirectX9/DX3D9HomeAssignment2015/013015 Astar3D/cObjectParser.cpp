#include "stdafx.h"
#include "cObjectParser.h"

#include <fstream>
#include <sstream>
#include <queue>

using namespace std;

cObjectParser::cObjectParser(const char* fileName)
{
	m_sFileName = fileName;
}


cObjectParser::~cObjectParser()
{
}

void cObjectParser::LoadAndParse(){
	fstream read(m_sFileName);
	// do this until file end
	string header;
	// header type for obj file
	//

	while (!read.eof()){
		read >> header;
		
	}
}
