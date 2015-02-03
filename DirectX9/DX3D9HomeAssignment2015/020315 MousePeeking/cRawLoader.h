#pragma once
class cRawLoader
{
public:
	cRawLoader();
	~cRawLoader();
	void LoadRawData(IN std::string& sFolder, IN std::string& sFileName, OUT std::vector<DWORD>& vecUINT);
};

