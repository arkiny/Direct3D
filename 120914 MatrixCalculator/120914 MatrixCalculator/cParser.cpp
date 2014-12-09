#include "cParser.h"
#include "cMatrix.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

cParser::cParser()
{
	m_Matrix1 = nullptr;
	m_Matrix2 = nullptr;
}


cParser::~cParser()
{
	if (m_Matrix1) delete m_Matrix1;
	if (m_Matrix2) delete m_Matrix2;
}

void cParser::loadandParse(const char* fileName){
	fstream read(fileName);
	int matrixSize;
	float fbuffer;
	read >> matrixSize;
	m_Matrix1 = new cMatrix(matrixSize);
	m_Matrix2 = new cMatrix(matrixSize);
	for (int i = 0; i < matrixSize; i++){
		for (int j = 0; j < matrixSize; j++){
			read >> fbuffer;
			m_Matrix1->setElement(i, j, fbuffer);
		}
	}
	for (int i = 0; i < matrixSize; i++){
		for (int j = 0; j < matrixSize; j++){
			read >> fbuffer;
			m_Matrix2->setElement(i, j, fbuffer);
		}
	}

	string sbuffer1;
	string sbuffer2;
	while (!read.eof()){
		read >> sbuffer1;
		read >> sbuffer2;
		if (sbuffer2 == "=="){
			cout << "<<< M1 equal to M2? >>>" << endl;
			read >> sbuffer1;
			if (*m_Matrix1 == *m_Matrix2){
				cout << "M1 = M2" << endl;
			}
			else{
				cout << "M1 != M2" << endl;
			}
			cout << endl;
		}
		else if (sbuffer2 == "+"){
			cout << "<<< M1 + M2 >>>" << endl;
			read >> sbuffer1;
			(*m_Matrix1 + *m_Matrix2).print();
			cout << endl;
		}
		else if (sbuffer2 == "-"){
			cout << "<<< M1 - M2 >>>" << endl;
			read >> sbuffer1;
			(*m_Matrix1 - *m_Matrix2).print();
			cout << endl;
		}
		else if (sbuffer2 == "*"){
			
			read >> sbuffer1;
			// if scalar
			// if matrix
			if (sbuffer1 == "m2"){
				cout << "<<< M1 * M2 >>>" << endl;
				(*m_Matrix1 * *m_Matrix2).print();
				cout << endl;
			}
			else {
				float value = atof(sbuffer1.c_str());
				cout << "<<< M1 * " << value << " >>>" << endl;
				(*m_Matrix1 * value).print();
				cout << endl;
			}
		}
		else if (sbuffer2 == "Identity"){
			cout << "<<< M1 's Identity >>>" << endl;
			m_Matrix1->Identity(*m_Matrix1).print();
			cout << endl;
		}
		else if (sbuffer2 == "->"){
			read >> sbuffer1;
			if (sbuffer1 == "Inverse"){
				cout << "<<< M1 's Inverse >>>" << endl;
				m_Matrix1->inverse().print();

				cMatrix confirm = *m_Matrix1 * m_Matrix1->inverse();
				if (m_Matrix1->Identity(*m_Matrix1) == confirm){
					cout << "God Damn, Right." << endl;
				}
				else {
					cout << "Magnet!!" << endl;
				}
				cout << endl;
			}
		}
	}
}