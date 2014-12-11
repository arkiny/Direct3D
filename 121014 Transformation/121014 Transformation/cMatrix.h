#pragma once
#include <vector>

class vector4;

class cMatrix
{
public:
	cMatrix();
	~cMatrix();

	void setElement(int x, int y, float value);
	float getElement(int x, int y);

	vector4 operator*(vector4& in);
	cMatrix operator*(cMatrix& in);

	cMatrix translate(float ix, float iy, float iz);
	cMatrix rotateX(float degree);
	cMatrix rotateY(float degree);
	cMatrix rotateZ(float degree);
	cMatrix scale(float ix, float iy, float iz);

private:
	std::vector<float> m_vecData;
};

