#pragma once

class cObjectParser;
class cObject;

class cObjectFromParser
{
public:
	cObjectFromParser();
	~cObjectFromParser();

	void setup(const char* fileName = NULL);
	void update(float);
	void render();
	void setMatrix(D3DXMATRIX& mat);

private:
	cObjectParser* m_pResource;
	std::vector<cObject*> m_vecObjects;
};

