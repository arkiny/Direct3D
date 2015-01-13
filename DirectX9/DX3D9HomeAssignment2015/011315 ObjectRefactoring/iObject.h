#pragma once

__interface iObject{
	void		AddRef();
	void		Release();
	int			GetRefCount();
	std::string GetDesc();
	void		SetDesc(std::string& s);
};

