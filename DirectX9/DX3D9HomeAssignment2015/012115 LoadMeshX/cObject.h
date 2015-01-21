#pragma once
class cObject 
{
protected:
	int m_nRefCount;
	std::string m_sDesc;

public:
	cObject();
	cObject(std::string sDesc);
	virtual ~cObject();

	void AddRef(){
		_ASSERT(m_nRefCount > 0);
		m_nRefCount++;
	}

	void		Release();

	int			GetRefCount(){ return m_nRefCount; }
	std::string GetDesc() { return m_sDesc; }
	void		SetDesc(std::string& s){ m_sDesc = s; }
};

