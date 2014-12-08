#pragma once

struct sMyVector
{
	float m_fX;
	float m_fY;
	float m_fX;
};

class cVector
{
public:
	cVector();
	~cVector();

	bool equal(sMyVector& in);
	sMyVector& add(sMyVector&);
	sMyVector& sub(sMyVector&);
	sMyVector& mul(sMyVector&);
	sMyVector& normalized(sMyVector&);
	float length();
	float dot(sMyVector&);
	float cross(sMyVector&);

private:
	sMyVector* m_Vector;
};

