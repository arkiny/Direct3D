#include "sVector4.h"
#include <iostream>
#include "cMatrix.h"

using namespace std;

vector4::vector4(){

}
vector4::vector4(float ix, float iy, float iz, float iw){
	m_fx = ix;
	m_fy = iy;
	m_fz = iz;
	m_fw = iw;
}
vector4::~vector4(){

}

vector4 vector4::operator*(cMatrix& mat){
	float x = mat.getElement(0, 0) * m_fx +
		mat.getElement(1, 0) * m_fy +
		mat.getElement(2, 0) * m_fz +
		mat.getElement(3, 0) * m_fw;
	float y = mat.getElement(0, 1) * m_fx +
		mat.getElement(1, 1) * m_fy +
		mat.getElement(2, 1) * m_fz +
		mat.getElement(3, 1) * m_fw;
	float z = mat.getElement(0, 2) * m_fx +
		mat.getElement(1, 2) * m_fy +
		mat.getElement(2, 2) * m_fz +
		mat.getElement(3, 2) * m_fw;
	float w = mat.getElement(0, 3) * m_fx +
		mat.getElement(1, 3) * m_fy +
		mat.getElement(2, 3) * m_fz +
		mat.getElement(3, 3) * m_fw;
	return vector4(x, y, z, w);
}

vector4 vector4::translate(float ix, float iy, float iz){
	vector4 ret;
	cMatrix mat;
	ret = (*this) * mat.translate(ix, iy, iz);
	return ret;
}
vector4 vector4::rotateX(float degree){
	vector4 ret;
	cMatrix mat;
	ret = (*this) * mat.rotateX(degree);
	return ret;
}
vector4 vector4::rotateY(float degree){
	vector4 ret;
	cMatrix mat;
	ret = (*this) * mat.rotateY(degree);
	return ret;
}
vector4 vector4::rotateZ(float degree){
	vector4 ret;
	cMatrix mat;
	ret = (*this) * mat.rotateZ(degree);
	return ret;
}
vector4 vector4::scale(float ix, float iy, float iz){
	vector4 ret;
	cMatrix mat;
	ret = (*this) * mat.scale(ix, iy, iz);
	return ret;
}

void vector4::print(){
	cout << "( " << m_fx << ", " << m_fy << ", " << m_fz << ", " << m_fw << " )" << endl;
}
