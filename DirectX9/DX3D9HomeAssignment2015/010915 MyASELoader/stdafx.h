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
#include "cObject.h"
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

struct stAseTrack{
	float x, y, z, w;
	int nf;
};

struct stAseTrackAni{
	std::string sNodeCur;			//Current Node NAme;
	std::vector<stAseTrack> vRot;	//Rotation
	std::vector<stAseTrack> vTrs;	//Transslation
	std::vector<stAseTrack> vScl;	//Scale
};

struct stASENode{
	std::vector<ST_PNT_VERTEX> vecVertex;
	std::string NodeName;
	std::string NodeParent;
	int nRef = INT_MAX;
	D3DXMATRIXA16 LocalMat;
	stAseTrackAni AnimationInfo;
};