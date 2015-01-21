// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// TODO: reference additional headers your program requires here
#include "../Common/CommonHeader.h"

#define SAFE_ADD_REF(p) if(p){p->AddRef();}

#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var){ varName = var; }

#define SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: virtual varType Get##funName(void) const { return varName; }\
public: virtual void Set##funName(const varType& var){ varName=var; }

#define SYNTHESIZE_ADD_REF(varType, varName, funName)    \
protected: varType varName; \
public: virtual varType Get##funName(void) const { return varName; } \
public: virtual void Set##funName(varType var){\
	if (varName != var) {\
	SAFE_ADD_REF(var);\
	SAFE_RELEASE(varName);\
	varName = var;\
		}\
}
// interfaces
#include "iActionDelegate.h"

#include "cObject.h"
#include "cObjectManager.h"
#include "cGameObject.h"
#include "cTextureManager.h"

struct GRIDPOSITION{
	int x = 0;
	int y = 0;
	int z = 0;

	GRIDPOSITION(int _x = 0, int _y = 0, int _z = 0){
		x = _x;
		y = _y;
		z = _z;
	}
};

struct stSceneInfo{
	UINT uiFrameFirst;			// start frame index
	UINT uiFrameLast;			// last frame index
	UINT uiFrameSpeed;			// frame speed
	UINT uiFrameTick;			// frame
};

struct ST_POS_SAMPLE{
	int nKey;
	D3DXVECTOR3 v;
};

struct ST_ROT_SAMPLE{
	int nKey;
	D3DXQUATERNION q;
};

struct stASENode{
	std::vector<ST_PNT_VERTEX> vecVertex;
	std::string NodeName;
	std::string NodeParent;
	int nRef = INT_MAX;
	D3DXMATRIXA16 LocalMat;
};

