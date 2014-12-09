#pragma once
class cMatrix;
class cParser
{
public:
	cParser();
	~cParser();
	void loadandParse(const char* filename);

private:
	cMatrix* m_Matrix1;
	cMatrix* m_Matrix2;
};

