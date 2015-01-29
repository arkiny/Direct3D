#include "stdafx.h"
#include "cMtlTex.h"


cMtlTex::cMtlTex()
	: pTex(NULL)
{
	ZeroMemory(&stMtl, sizeof(D3DMATERIAL9));
}

cMtlTex::cMtlTex(std::string Name)
	: pTex(NULL)
{
	ZeroMemory(&stMtl, sizeof(D3DMATERIAL9));
	sMtlName = Name;
}


cMtlTex::~cMtlTex(void)
{
	int  j = 0;
}
