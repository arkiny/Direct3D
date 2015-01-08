#include "StdAfx.h"
#include "iMap.h"

void cObjMap::Load( IN std::string& sFolder, IN std::string& sFileName, IN D3DXMATRIXA16* pmat/* = NULL*/ )
{
	FILE* fp;
	fopen_s(&fp, (sFolder + sFileName).c_str(), "r");

	std::vector<D3DXVECTOR3> vecV;

	while(!feof(fp))
	{
		char szLineBuf[1024] = {0,};
		fgets(szLineBuf, 1024, fp);
		
		if(strlen(szLineBuf) == 0)
			continue;
		if(szLineBuf[0] == 'v')
		{
			if(szLineBuf[1] == ' ')
			{
				float x, y, z;
				sscanf(szLineBuf, "%*s %f %f %f", &x, &y, &z);
				
				D3DXVECTOR3 p = D3DXVECTOR3(x, y, z);

				if(pmat)
				{
					D3DXVec3TransformCoord(&p, &p, pmat);
				}

				vecV.push_back(p);
			}
		}
		else if(szLineBuf[0] == 'f')
		{
			int aIndex[3];
			sscanf(szLineBuf, "%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
				&aIndex[0], &aIndex[1], &aIndex[2]);
			m_vecFaces.push_back(vecV[aIndex[0] - 1]);
			m_vecFaces.push_back(vecV[aIndex[1] - 1]);
			m_vecFaces.push_back(vecV[aIndex[2] - 1]);
		}
	}

	fclose(fp);
}

float cObjMap::GetHeight( OUT bool& isLand, IN D3DXVECTOR3* pvPosition )
{
	D3DXVECTOR3 vPosition = (*pvPosition);
	vPosition.y = 1000.0f;

	float u, v, fDist;
	for(size_t i = 0; i < m_vecFaces.size(); i += 3)
	{
		if(D3DXIntersectTri(&m_vecFaces[i], &m_vecFaces[i+1], &m_vecFaces[i+2],
			&vPosition, &D3DXVECTOR3(0, -1, 0), &u, &v, &fDist))
		{
			isLand = true;
			return 1000.0f - fDist;
		}
	}
	isLand = false;
	return 0.0f;
}
