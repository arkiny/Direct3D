#include "StdAfx.h"
#include "cMtlTex.h"


cMtlTex::cMtlTex(void)
	 : pTex(NULL)
	 , m_nAttrId(0)
{
	ZeroMemory(&stMtl, sizeof(D3DMATERIAL9));
}


cMtlTex::~cMtlTex(void)
{
	int  j = 0;
}
