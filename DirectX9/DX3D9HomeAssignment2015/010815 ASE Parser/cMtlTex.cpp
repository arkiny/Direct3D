#include "stdafx.h"
#include "cMtlTex.h"


cMtlTex::cMtlTex(std::string mtlName)
	: pTex(NULL)
{
	sMtlName = mtlName;
	ZeroMemory(&stMtl, sizeof(D3DMATERIAL9));
}


cMtlTex::~cMtlTex(void)
{
	int  j = 0;
}
