#include "stdafx.h"
#include "cMtlTex.h"


cMtlTex::cMtlTex(void)
	: pTex(NULL)
{
	ZeroMemory(&stMtl, sizeof(D3DMATERIAL9));
}


cMtlTex::~cMtlTex(void)
{
	int  j = 0;
}
