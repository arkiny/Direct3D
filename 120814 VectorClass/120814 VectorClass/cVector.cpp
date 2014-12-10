#include <math.h>
#include <iostream>
#include "cVector.h"

#define EPSILON 0.0001f

cVector::cVector()
{
	m_sVectorData = new sVector;
	m_sVectorData->x = 0;
	m_sVectorData->y = 0;
	m_sVectorData->z = 0;
}

cVector::~cVector()
{
	//delete m_sVectorData;
}

cVector::cVector(float x, float y, float z){
	//if (m_sVectorData) delete m_sVectorData;
	m_sVectorData = new sVector;
	m_sVectorData->x = x;
	m_sVectorData->y = y;
	m_sVectorData->z = z;
}

bool cVector::operator==(cVector &v){
	return true;
}

cVector cVector::operator+(cVector& v){
	sVector a = v.getVectorCoord();
	cVector ret = cVector(a.x + m_sVectorData->x, a.y + m_sVectorData->y, a.z + m_sVectorData->z);
	return ret;
}

cVector cVector::operator-(cVector& v){
	sVector a = v.getVectorCoord();
	cVector ret = cVector((-a.x) + m_sVectorData->x, (-a.y) + m_sVectorData->y, (-a.z) + m_sVectorData->z);
	return ret;
}

bool cVector::equal(cVector& in){	
	float origin = this->length();
	float comp = in.length();
	if ((origin - comp) * (origin - comp) <= EPSILON*EPSILON) return true;
	else return false;
}

cVector cVector::add(cVector& in){
	sVector a = in.getVectorCoord();
	cVector ret = cVector(a.x + m_sVectorData->x, a.y + m_sVectorData->y, a.z + m_sVectorData->z);
	return ret;
}

cVector cVector::sub(cVector& in){
	sVector a = in.getVectorCoord();
	cVector ret = cVector((-a.x) + m_sVectorData->x, (-a.y) + m_sVectorData->y, (-a.z) + m_sVectorData->z);
	return ret;
}

cVector cVector::mul(float scalar){
	return cVector(scalar * m_sVectorData->x,
		scalar* m_sVectorData->y, 
		scalar* m_sVectorData->z);
}

cVector cVector::normalized(){
	float div = length();
	return cVector(m_sVectorData->x / div, 
		m_sVectorData->y / div, 
		m_sVectorData->z / div);
}

float cVector::length(){
	return sqrtf((m_sVectorData->x * m_sVectorData->x) + 
		(m_sVectorData->y * m_sVectorData->y) + 
		(m_sVectorData->y * m_sVectorData->y));
}

float cVector::dot(cVector& in){
	sVector input = in.getVectorCoord();
	return (m_sVectorData->x * input.x) + (m_sVectorData->y * input.y) + (m_sVectorData->z*input.z);
}

cVector cVector::cross(cVector& in){
	sVector input = in.getVectorCoord();
	cVector ret = cVector(((m_sVectorData->y * input.z) - (m_sVectorData->z * input.y)),
		((m_sVectorData->z * input.x) - (m_sVectorData->x * input.z)),
		((m_sVectorData->x * input.y) - (m_sVectorData->y * input.x)));
	return ret;
}

void cVector::print(){
	std::cout << "(" << m_sVectorData->x << ","
		<< m_sVectorData->y << ","
		<< m_sVectorData->z << ")" << std::endl;
}