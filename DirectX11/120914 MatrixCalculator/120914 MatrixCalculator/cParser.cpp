#include "cParser.h"


cParser::cParser()
{
}


cParser::~cParser()
{
	if (m_Matrix1) delete m_Matrix1;
	if (m_Matrix2) delete m_Matrix2;
}

void loadandParse(const char* filename){

}