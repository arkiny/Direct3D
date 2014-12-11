#include <math.h>
#include "cMatrix.h"
#include "sVector4.h"

#define PI 3.14159265f

cMatrix::cMatrix(){
	// static size matrix
	// and default is identity matrix
	m_vecData.resize(4 * 4);
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			setElement(i, j, i == j);
		}
	}
}

cMatrix::~cMatrix(){
}

void cMatrix::setElement(int x, int y, float value){
	m_vecData[x * 4 + y] = value;
}

float cMatrix::getElement(int x, int y){
	return m_vecData[x * 4 + y];
}

vector4 cMatrix::operator*(vector4& in){
	return vector4(0,0,0,0);
}

cMatrix cMatrix::operator*(cMatrix& in){
	cMatrix ret;
	// ret = this * m;
	float sum;
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			// ret[i][j] = sum of (mA[i][k] * mB[k][j])
			sum = 0;
			for (int k = 0; k < 4; k++){
				//
				sum = sum + getElement(i, k) * in.getElement(k, j);
				//
			}
			ret.setElement(i, j, sum);
		}
	}
	return ret;
}

cMatrix cMatrix::translate(float ix, float iy, float iz){
	cMatrix ret;
	ret.setElement(3, 0, ix);
	ret.setElement(3, 1, iy);
	ret.setElement(3, 2, iz);
	return ret;
}

cMatrix cMatrix::rotateX(float degree){
	cMatrix ret;
	float _fcos = cosf(degree*PI / 180.0f);
	float _fsin = sinf(degree*PI / 180.0f);
	ret.setElement(1, 1, _fcos);
	ret.setElement(1, 2, _fsin);
	ret.setElement(2, 1, -(_fsin));
	ret.setElement(2, 2, _fcos);
	return ret;	
}

cMatrix cMatrix::rotateY(float degree){
	cMatrix ret;
	float _fcos = cosf(degree*PI / 180.0f);
	float _fsin = sinf(degree*PI / 180.0f);
	ret.setElement(0, 0, _fcos);
	ret.setElement(0, 2, -(_fsin));
	ret.setElement(2, 0, _fsin);
	ret.setElement(2, 2, _fcos);
	return ret;
	
}

cMatrix cMatrix::rotateZ(float degree){
	cMatrix ret;
	float _fcos = cosf(degree*PI / 180.0f);
	float _fsin = sinf(degree*PI / 180.0f);
	ret.setElement(0, 0, _fcos);
	ret.setElement(0, 1, _fsin);
	ret.setElement(1, 0, -(_fsin));
	ret.setElement(1, 1, _fcos);
	return ret;
}

cMatrix cMatrix::scale(float ix, float iy, float iz){
	cMatrix ret;
	ret.setElement(0, 0, ix);
	ret.setElement(1, 1, iy);
	ret.setElement(2, 2, iz);
	return ret;
}