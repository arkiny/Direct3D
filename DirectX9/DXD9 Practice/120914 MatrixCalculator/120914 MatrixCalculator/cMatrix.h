#pragma once

#include <vector>
#define EPSILON 0.0001f

class cMatrix
{
public:
	cMatrix();
	cMatrix(int size);
	//cMatrix(int size, float* data);
	~cMatrix();

	// actual homework
	bool equalto(cMatrix& m);
	bool operator==(cMatrix& m);;

	cMatrix operator+(cMatrix& m);
	cMatrix operator-(cMatrix& m);
	cMatrix operator*(float scalar);
	cMatrix operator*(cMatrix& m);

	cMatrix inverse();
	float det();

	//float minor(int x, int y);
	float cofactor(int i, int j);

	cMatrix adj();
	void transpose();
	

	static cMatrix Identity(cMatrix& m);

	// Print
	void print();

	// getter, zero-based matrix system
	float getElement(int x, int y){ return m_matrix[x * m_nSize + y]; }
	float getElement(int i){ return m_matrix[i]; }
	
	void setElement(int x, int y, float value){ m_matrix[x * m_nSize + y] = value; }
	int getSize() { return m_nSize; }
	
	void setData(int x, float value){ m_matrix[x] = value; }
	float cofactor(int i, int j, cMatrix& m);
private:
	int m_nSize;
	std::vector<float> m_matrix;	


	std::vector<float>* getDataSet(){ return &m_matrix; }

	cMatrix minor(int x, int y, cMatrix& m);

	float minorcalc(int x, int y, cMatrix& m);
	float detRecursive(cMatrix& m);
	
};

