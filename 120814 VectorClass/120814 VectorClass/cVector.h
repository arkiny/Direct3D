#pragma once

struct sVector{
	float x;
	float y;
	float z;
};

class cVector
{
public:
	cVector();
	cVector(float x, float y, float z);
	~cVector();

	cVector operator+(cVector v);
	cVector operator-(cVector v);


	bool equal(cVector in);
	
	cVector add(cVector in);
	cVector sub(cVector in);
	cVector mul(float scalar);

	cVector normalized();
	float length();

	float dot(cVector in);
	cVector cross(cVector in);

	sVector getVectorCoord(){
		return *m_sVectorData;
	}

	void print();

private:
	sVector* m_sVectorData;
};

