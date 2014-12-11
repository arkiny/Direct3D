#include <iostream>
#include <math.h>
#include "cMatrix.h"

using namespace std;

cMatrix::cMatrix()
{
	m_nSize = 0;
	m_matrix.resize(m_nSize*m_nSize);
}

cMatrix::cMatrix(int size){
	m_nSize = size;
	m_matrix.resize(m_nSize*m_nSize);
	for (int i = 0; i < m_nSize*m_nSize; i++){
		m_matrix[i] = 0;
	}
}

//cMatrix::cMatrix(int size, float* data){
//	m_nSize = size;
//	m_matrix = data;
//}


cMatrix::~cMatrix()
{
}

// actual homework
bool cMatrix::equalto(cMatrix& m){
	return *this == m;
}

bool cMatrix::operator==(cMatrix& m){
	if (m_nSize != m.getSize()) return false;
	for (int i = 0; i < m_nSize*m_nSize; i++){
		if ((m.getElement(i) - m_matrix[i])*(m.getElement(i) - m_matrix[i]) >(EPSILON*EPSILON))
			return false;
	}
	return true;
}

cMatrix cMatrix::operator+(cMatrix& m){
	cMatrix ret(m_nSize);
	for (int i = 0; i < m_nSize*m_nSize; i++){
		ret.setData(i, m_matrix[i] + m.getElement(i));
	}
	return ret;
}

cMatrix cMatrix::operator-(cMatrix& m){
	cMatrix ret(m_nSize);
	for (int i = 0; i < m_nSize*m_nSize; i++){
		ret.setData(i, m_matrix[i] - m.getElement(i));
	}
	return ret;
}

cMatrix cMatrix::operator*(float scalar){
	cMatrix ret(m_nSize);
	for (int i = 0; i < m_nSize*m_nSize; i++){
		ret.setData(i, scalar * m_matrix[i]);
	}
	return ret;
}

cMatrix cMatrix::operator*(cMatrix& m){
	cMatrix ret(m_nSize);
	// ret = this * m;

	if (m.getSize() != m_nSize){
		return cMatrix();
	}

	float sum;
	for (int i = 0; i < m_nSize; i++){
		for (int j = 0; j < m_nSize; j++){
			// ret[i][j] = sum of (mA[i][k] * mB[k][j])
			sum = 0;
			for (int k = 0; k < m_nSize; k++){
				//
				sum = sum + getElement(i, k) * m.getElement(k, j);
				//
			}
			ret.setElement(i, j, sum);
		}		
	}
	return ret;
}

cMatrix cMatrix::inverse(){
	//@todo
	if (det() == 0) {
		cerr << "Determinant is Zero" << endl;
		return cMatrix();
	}
	cMatrix ret = adj() * (1 / det());
	return ret;
}

float cMatrix::det(){
	return detRecursive(*this);
}

float cMatrix::detRecursive(cMatrix& m){
	if (m.getSize() == 1){
		return m.getElement(0, 0);
	}
	else if (m.getSize() == 2){
		return 
			(m.getElement(0, 0) * m.getElement(1, 1))
			- (m.getElement(1, 0) * m.getElement(0, 1));
	}
	else {
		float ret = 0.0f;
		for (int i = 0; i < m.getSize(); i++){
			// ret + cofactor + recursived det
			//ret = ret + getElement(0, i) * pow(-1.0f, i) * detRecursive(minor(0,i, m));
			ret = ret + m.getElement(0, i) * cofactor(0,i,m);
		}
		return ret;
	}
	/*else{
		float ret = 0.0f;
		for (int i = 0; i < m_nSize; i++){
			ret = ret + (getElement(0, i) * cofactor(0, i));
		}
		return ret;
	}*/
}

float cMatrix::cofactor(int i, int j){
	return cofactor(i, j, *this);
}

float cMatrix::cofactor(int i, int j, cMatrix& m){
	/*return pow(-1.0f, i + j) * minor(i, j, *this);*/
	float ret = pow(-1.0f, i+j) * detRecursive(minor(i, j, m));
	return ret;
}

cMatrix cMatrix::adj(){
	cMatrix ret(m_nSize);
	for (int i = 0; i < ret.getSize(); i++){
		for (int j = 0; j < ret.getSize(); j++){
			float c = cofactor(j, i ,*this);
			ret.setElement(j, i, c);
		}
	}
	ret.transpose();
	return ret;
}

void cMatrix::transpose(){
	for (int i = 0; i < m_nSize; i++){
		for (int j = i; j < m_nSize; j++){
			if (i == j) continue;
			float temp = getElement(i, j);
			setElement(i, j, getElement(j, i));
			setElement(j, i, temp);
		}
	}
}

cMatrix cMatrix::minor(int x, int y, cMatrix& m){
	if (m.getSize() == 1){
		return m;
	}
	if (m.getSize() == 2){
		cMatrix subMat(m.getSize() - 1);
		int ix = 0, iy = 0;

		for (int i = 0; i < m.getSize(); i++){
			if (i == x) continue;
			for (int j = 0; j < m.getSize(); j++){
				if (j == y) continue;
				subMat.setElement(ix, iy, m.getElement(i, j));
				ix++;
			}
			ix = 0;
			iy++;
		}
		return subMat;
	}
	if (m.getSize() >= 3){
		cMatrix subMat(m.getSize() - 1);
		int ix = 0, iy = 0;

		for (int i = 0; i < m.getSize(); i++){
			if (i == x) continue;
			for (int j = 0; j < m.getSize(); j++){
				if (j == y) continue;				
				subMat.setElement(iy, ix, m.getElement(i,j));
				ix++;
			}	
			ix = 0;
			iy++;
		}
		return subMat;
	}
	return cMatrix();
	//if (m.getSize() == 1){
	//	return m.getElement(0, 0);
	//}
	//if (m.getSize() == 2){
	//	// ad - bc
	//	//(0,0 * 1,1) - (1,0 * 0,1)
	//	return (m.getElement(0, 0) * m.getElement(1, 1))
	//		- (m.getElement(1, 0) * m.getElement(0, 1));
	//}
	////if (m.getSize() == 3){

	////}
	//else {
	//	// 만약 매트릭스가 2*2보다 크다면
	//	// sub 매트릭스 설정
	//	//float nMinor;
	//	cMatrix subMat(m.getSize() - 1);
	//	int ix = 0, iy = 0;

	//	for (int i = 0; i < m.getSize(); i++){
	//		if (i == y) continue;
	//		for (int j = 0; j < m.getSize(); j++){
	//			if (j == y) continue;				
	//			subMat.setElement(ix, iy, m.getElement(i,j));
	//			ix++;
	//		}	
	//		ix = 0;
	//		iy++;
	//	}

	//	for (int i = 0; i < subMat.getSize(); i++){
	//		for (int j = 0; j < subMat.getSize(); j++){
	//			
	//		}
	//	}		
	//}
}

cMatrix cMatrix::Identity(cMatrix& m){
	cMatrix ret(m.getSize());
	for (int i = 0; i < m.getSize(); i++){
		ret.setElement(i, i, 1.0f);
	}
	return ret;
}

void cMatrix::print(){
	//cout.precision(2);
	for (int i = 0; i < m_nSize; i++){
		for (int j = 0; j < m_nSize; j++){
			cout << getElement(i, j) << " ";
		}
		cout << endl;
	}
}

// getter
//int cMatrix::getElement(int x, int y){
//
//}
//float* cMatrix::getDataSet(){
//
//}