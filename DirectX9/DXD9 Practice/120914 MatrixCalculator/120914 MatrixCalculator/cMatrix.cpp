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
	
	if (m.getSize() != m_nSize){
		return cMatrix();
	}

	float sum;
	for (int i = 0; i < m_nSize; i++){
		for (int j = 0; j < m_nSize; j++){
			sum = 0;
			for (int k = 0; k < m_nSize; k++){
				sum = sum + getElement(i, k) * m.getElement(k, j);
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
		// a b 
		// c d
		// ad - bc
		return 
			(m.getElement(0, 0) * m.getElement(1, 1))
			- (m.getElement(1, 0) * m.getElement(0, 1));
	}
	else {
		// 11 12 13  ..
		// 21 22 23  ..
		// 31 32 33  ..
		// .. .. ..  ..
		// 열의 사이즈 (정방형이므로 3x3은 3)만큼
		// 11, 12, 13의 minor 매트릭스를 통한 코팩터를 구해서 더한다. (여기서 숫자는 행열)
		// 11 * cofactor(22, 23)  + 12 * cofactor(21, 23) + 13 * cofactor(21, 22) 
		//              (32, 33)	             (31, 33)                (31, 32)
		// 열이 늘어나더라도 결국 이 법칙을 벗어나지 않으므로 위 식을 기반으로 행렬식을 구하면 된다.
		float ret = 0.0f;
		for (int i = 0; i < m.getSize(); i++){
			ret = ret + m.getElement(0, i) * cofactor(0,i,m);
		}
		return ret;
	}
}

// 여인수는 재귀적으로 구한다.
float cMatrix::cofactor(int i, int j){
	return cofactor(i, j, *this);
}

float cMatrix::cofactor(int i, int j, cMatrix& m){
	// ret = pow(-1, i+j) * 행렬식(매트릭스의 ij의 마이너 행렬)
	float ret = pow(-1.0f, i+j) * detRecursive(minor(i, j, m));
	return ret;
}

cMatrix cMatrix::adj(){
	cMatrix ret(m_nSize);
	for (int i = 0; i < ret.getSize(); i++){
		for (int j = 0; j < ret.getSize(); j++){
			// 딸림 행렬
			// 여인수의 행렬의 전치 행렬
			// 모든 원소에 대해서 여인수를 구하고, 그것을 전치시켜준다.
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
}

cMatrix cMatrix::Identity(cMatrix& m){
	cMatrix ret(m.getSize());
	for (int i = 0; i < m.getSize(); i++){
		ret.setElement(i, i, 1.0f);
	}
	return ret;
}

void cMatrix::print(){
	for (int i = 0; i < m_nSize; i++){
		for (int j = 0; j < m_nSize; j++){
			cout << getElement(i, j) << " ";
		}
		cout << endl;
	}
}