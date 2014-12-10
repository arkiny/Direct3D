#pragma once

class cMatrix;
class vector4{
public:
	vector4();
	vector4(float ix, float iy, float iz, float iw);
	~vector4();

	vector4 operator*(cMatrix& mat);

	vector4 translate(float ix, float iy, float iz);
	vector4 rotateX(float degree);
	vector4 rotateY(float degree);
	vector4 rotateZ(float degree);
	vector4 scale(float ix, float iy, float iz);

	void print();

private:
	float m_fx = 0.0f;
	float m_fy = 0.0f;
	float m_fz = 0.0f;
	float m_fw = 0.0f;
};