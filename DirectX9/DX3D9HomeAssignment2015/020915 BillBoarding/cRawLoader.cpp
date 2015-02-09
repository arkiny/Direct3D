#include "stdafx.h"
#include "cRawLoader.h"


cRawLoader::cRawLoader()
{
}


cRawLoader::~cRawLoader()
{
}

void cRawLoader::LoadRawData(IN std::string& sFolder, IN std::string& sFileName, OUT std::vector<DWORD>& vecUINT){
	FILE* pf = NULL;
	fopen_s(&pf, (sFolder + sFileName).c_str(), "rb");
	_ASSERT(pf != NULL);
	while (!feof(pf)){
		vecUINT.push_back(getc(pf));
	}
}