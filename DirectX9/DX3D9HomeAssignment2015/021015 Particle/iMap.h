#pragma once
class iMap
{
public:
	virtual float GetHeight(OUT bool& isLand, IN D3DXVECTOR3* pvPosition) = 0;
};

class cObjMap : public iMap
{
private:
	std::vector<D3DXVECTOR3> m_vecFaces;

public:
	cObjMap(){}
	virtual ~cObjMap(){}

	virtual void Load(IN std::string& sFolder, IN std::string& sFileName, IN D3DXMATRIXA16* pmat = NULL);

	// iMap override
	virtual float GetHeight(OUT bool& isLand, IN D3DXVECTOR3* pvPosition) override;
};