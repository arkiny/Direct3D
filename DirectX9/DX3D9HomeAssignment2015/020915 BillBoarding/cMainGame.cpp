#include "stdafx.h"
#include <sstream>
#include "cMainGame.h"
#include "../Common/cAxis.h"
#include "../Common/cGrid.h"
#include "cCamera.h"
#include "cPlayer.h"
#include "cPyramid.h"
#include "cCharacter.h"
#include "cCard.h"
#include "cHeightMap.h"
#include "cAPoint.h"
#include "cGraph.h"
#include "cDjikstraSP.h"
#include "cSkinnedMeshObject.h"
#include "cActionSeq.h"
#include "cActionMove.h"
#include "cActionRepeat.h"
#include "cActionIdle.h"
#include "cEdge.h"
#include "cPlain.h"
#include "cSphere.h"
#include "cMousePeeking.h"
#include "cBox.h"
#include "cPlayer.h"
#include "cTileMap.h"
#include "cTile.h"
#include "cAstarSP.h"
#include "cTileMapLoader.h"



cMainGame::cMainGame() :
m_cAxis(NULL),
m_cGrid(NULL),
m_cCamera(NULL),
m_pPyramid(NULL),
m_pFont(NULL),
m_nScore(0)
//m_pSphere(NULL)
{
	srand(GetTickCount());
	GetCursorPos(&m_mousePos);
	InitializeCriticalSection(&gCriticalSection);
}

cMainGame::~cMainGame()
{

	//std::terminate();
	m_bKillThread = true;
	
	//TerminateThread(SetupSkinnedMesh, 0);
	
	WaitForSingleObject(SetupSkinnedMesh, INFINITE);
	CloseHandle(SetupSkinnedMesh);
	DeleteCriticalSection(&gCriticalSection);
	
	SAFE_DELETE(m_pPyramid);
	SAFE_DELETE(m_cAxis);
	SAFE_DELETE(m_cGrid);
	SAFE_DELETE(m_cCamera);
	SAFE_RELEASE(m_pFont);
	//SAFE_RELEASE(m_pSphere);
	//for (auto p : m_vecSpheres){
	//	SAFE_RELEASE(p);
	//}

	for (size_t i = 0; i < m_vecSkinnedMeshObjects.size(); i++){
		if (m_vecSkinnedMeshObjects[i]->isLoaded()){
			SAFE_RELEASE(m_vecSkinnedMeshObjects[i]);
		}
	}

	g_pTextureManager->Destroy();
	cDeviceManager* pDevice = cDeviceManager::GetInstance();
	pDevice->Destroy();
}

void cMainGame::SetupSkinnedMesh(LPVOID pParam){
	cMainGame* pMain = (cMainGame*)pParam;

	for (int i = 0; i < 50; i++){
		EnterCriticalSection(&gCriticalSection);
		if (pMain->KillThread()){
			ExitThread(0);
		}
		cSkinnedMeshObject* p = new cSkinnedMeshObject;
		p->Setup();
		p->SetAnimationIndex(4);
		p->SetisLoaded(true);
		p->SetPosition(D3DXVECTOR3(rand() % 30, 0, rand() % 30));
		LeaveCriticalSection(&gCriticalSection);
		pMain->GetSkinnedMeshObjects().push_back(p);
	}
}

void cMainGame::Init(){
	m_cAxis = new cAxis(100.0f);
	m_cAxis->init();

	m_cGrid = new cGrid(100.0f, 100);
	m_cGrid->init();

	m_cCamera = new cCamera;
	m_cCamera->Setup();

	m_pPyramid = new cPyramid;
	m_pPyramid->setup();

	

	//m_vecSpheres;
	//cSphere* p;
	//for (int i = 0; i < 2000; i++){
	//	p = new cSphere;
	//	p->Setup();
	//	p->SetPosition(rand() % 500 / 10.0f - 25.0f, rand() % 100 / 1.0f, rand() % 500 / 10.0f - 25.0f);
	//	m_vecSpheres.push_back(p);
	//}


	D3DXCreateFont(g_pD3DDevice,		//D3D Device
		40,								//Font height
		0,								//Font width
		FW_NORMAL,						//Font Weight
		1,								//MipLevels
		false,							//Italic
		DEFAULT_CHARSET,				//CharSet
		OUT_DEFAULT_PRECIS,				//OutputPrecision
		ANTIALIASED_QUALITY,			//Quality
		DEFAULT_PITCH | FF_DONTCARE,	//PitchAndFamily
		"Arial",						//pFacename,
		&m_pFont);						//ppFont

	SetRect(&m_recFontRect, 0, 0, 400, 200);

	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	D3DXVECTOR3 vDir = D3DXVECTOR3(1.5, -1, 1);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	stLight.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	stLight.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);

	DWORD dwThID;
	CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SetupSkinnedMesh, this, NULL/*CREATE_SUSPENDED*/, &dwThID));
}


void cMainGame::Update(float delta){
	m_fAccumTime += delta;
	m_cCamera->Update(delta);
	for (size_t i = 0; i < m_vecSkinnedMeshObjects.size(); i++){
		if (m_vecSkinnedMeshObjects[i]->isLoaded()){
			m_vecSkinnedMeshObjects[i]->Update(delta);
		}
	}
	//for (auto p : m_vecSkinnedMeshObjects){
	//	if (p->isLoaded()){
	//		p->Update(delta);
	//	}
	//}
	
}

void cMainGame::Render(){
	D3DXMATRIXA16 matRot, matWorld;

	g_pD3DDevice->Clear(
		NULL, NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		//D3DCOLOR_XRGB(47, 121, 112),
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f, 0);
	g_pD3DDevice->BeginScene();
	
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_pPyramid->render();
	m_cAxis->render();
	m_cGrid->render();

	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	for (size_t i = 0; i < m_vecSkinnedMeshObjects.size(); i++){
		if (m_vecSkinnedMeshObjects[i]->isLoaded()){
			m_vecSkinnedMeshObjects[i]->Render();
		}
	}
	
	std::stringstream s;
	s.precision(2);

	if (m_vecSkinnedMeshObjects.size() == 50){
		s << m_vecSkinnedMeshObjects.size() << "/50, DONE" << std::endl;
	}
	else{
		s << m_vecSkinnedMeshObjects.size() << "/50, Loading.." << std::endl;
	}
	

	m_pFont->DrawText(NULL,				 //pSprite
		s.str().c_str(),	 //pString
		-1,					//Count
		&m_recFontRect,		//pRect
		DT_LEFT | DT_NOCLIP,//Format,
		0xFFFFFFFF);		//Color
	
	//if ()
	
	//typedef struct _D3DVIEWPORT9 {
	//	DWORD       X;
	//	DWORD       Y;            /* Viewport Top left */
	//	DWORD       Width;
	//	DWORD       Height;       /* Viewport Dimensions */
	//	float       MinZ;         /* Min/max of clip Volume */
	//	float       MaxZ;
	//} D3DVIEWPORT9;

	/*D3DVIEWPORT9 vp;
	g_pD3DDevice->GetViewport(&vp);

	std::vector<D3DXVECTOR3> vecfrusmtom(8);
	
	vecfrusmtom[0] = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	vecfrusmtom[1] = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	vecfrusmtom[2] = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	vecfrusmtom[3] = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	vecfrusmtom[4] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vecfrusmtom[5] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
	vecfrusmtom[6] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vecfrusmtom[7] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);*/

	//
	//std::vector<D3DXVECTOR3> vecWorldVertex(8);
	//for (size_t i = 0; i < 8; ++i){
	//	D3DXVec3Unproject(
	//		&vecWorldVertex[i],
	//		&m_vecProjVertex[i],
	//		NULL,
	//		&matProj,
	//		&matWorld)
	//}

	//std::vector<D3DXVECTOR3> frustom;
	//
	//frustom.push_back();
	//frustom.push_back();
	//frustom.push_back();
	//frustom.push_back();
	//frustom.push_back();
	//frustom.push_back();
	//


	///
	//if (GetAsyncKeyState(VK_SPACE)){
	//	D3DXMATRIXA16 invProj;
	//	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &invProj);
	//	D3DXMatrixInverse(&invProj, NULL, &invProj);


	//	D3DXMATRIXA16 invView;
	//	g_pD3DDevice->GetTransform(D3DTS_VIEW, &invView);
	//	D3DXMatrixInverse(&invView, NULL, &invView);

	//	D3DXMATRIXA16 world;
	//	world = invProj * invView;

	//	for (size_t i = 0; i < vecfrusmtom.size(); i++){
	//		D3DXVec3TransformCoord(&vecfrusmtom[i], &vecfrusmtom[i], &world);
	//	}

	//	std::vector<D3DXPLANE> vecPlanes(6);

	//	D3DXPlaneFromPoints(&vecPlanes[0], &vecfrusmtom[0], &vecfrusmtom[1], &vecfrusmtom[2]); // near
	//	D3DXPlaneFromPoints(&vecPlanes[1], &vecfrusmtom[6], &vecfrusmtom[7], &vecfrusmtom[5]); // far
	//	D3DXPlaneFromPoints(&vecPlanes[2], &vecfrusmtom[2], &vecfrusmtom[6], &vecfrusmtom[4]); // left
	//	D3DXPlaneFromPoints(&vecPlanes[3], &vecfrusmtom[7], &vecfrusmtom[3], &vecfrusmtom[5]); // right
	//	D3DXPlaneFromPoints(&vecPlanes[4], &vecfrusmtom[2], &vecfrusmtom[3], &vecfrusmtom[6]); // top
	//	D3DXPlaneFromPoints(&vecPlanes[5], &vecfrusmtom[1], &vecfrusmtom[0], &vecfrusmtom[4]); // bottom

	//	for (auto p : m_vecSpheres){
	//		D3DXVECTOR3 pos = p->GetTransform()->GetPosition();
	//		float a = p->GetRadius();

	//		if (D3DXPlaneDotCoord(&vecPlanes[0], &pos) + a > 0
	//			&& D3DXPlaneDotCoord(&vecPlanes[1], &pos) + a > 0
	//			&& D3DXPlaneDotCoord(&vecPlanes[2], &pos) + a > 0
	//			&& D3DXPlaneDotCoord(&vecPlanes[3], &pos) + a > 0
	//			&& D3DXPlaneDotCoord(&vecPlanes[4], &pos) + a > 0
	//			&& D3DXPlaneDotCoord(&vecPlanes[5], &pos) + a > 0){

	//			SAFE_RENDER(p);
	//		}
	//	}
	//}
	//else {
	//	for (auto p : m_vecSpheres){
	//			SAFE_RENDER(p);
	// 	}
	//	
	//}

	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
	if (m_cCamera)
		m_cCamera->WndProc(hWnd, message, wParam, lParam);

	switch (message)
	{
	case WM_LBUTTONDOWN:{
		break;
	}

	case WM_RBUTTONUP:
		break;

						
	case WM_LBUTTONUP:
	{
		m_bClicked = false;
		break;
	}

	case WM_KEYDOWN:
	{
	}

	case WM_MOUSEMOVE:
	{
		m_stMouseLocation.x = LOWORD(lParam);
		m_stMouseLocation.y = HIWORD(lParam);
	}
	break;
	}
}

void cMainGame::OnActionFinish(cAction* pSender){
	cActionSeq* pActionSeq = new cActionSeq;
	cActionIdle* pActionMove = new cActionIdle;
	pActionMove->SetActionTime(1.0f);
	pActionMove->SetOwner(pSender->GetOwner());
	pActionSeq->AddAction(pActionMove);
	cSkinnedMeshObject* bothering = (cSkinnedMeshObject*)pSender->GetOwner();
	bothering->SetAnimationIndex(4);
	SAFE_RELEASE(pActionMove);	
	pActionSeq->SetDelegate(this);

	/*cActionRepeat* pActionRepeat = new cActionRepeat;
	pActionRepeat->SetAction(pActionSeq);*/
	//	pActionRepeat->SetDelegate(this);

	//pSender->GetOwner()->SetAngle(pSender->GetOwner()->GetAngle());
	pSender->GetOwner()->SetAction(pActionSeq);
	
	pActionSeq->Start();

	//SAFE_RELEASE(pSender);
	SAFE_RELEASE(pActionSeq);
}

void cMainGame::OnActionMoveTargetUpdated(cAction* pSender, int TargetNode){
	int a = 0;
	//std::vector<int> path;
	//m_nCurrentNode = m_nDestination;
	//m_nDestination = TargetNode;

	//if (TargetNode == m_nCurrentNode){
	//	OnActionFinish(pSender);
	//	return;
	//}

	//cDjikstraSP sp(m_pGraph, m_nCurrentNode, m_nDestination);
	//sp.SetupAndCalculate();
	//sp.GetShortestPathAsVector(path);

	//cSkinnedMeshObject* bothering = (cSkinnedMeshObject*)pSender->GetOwner();
	//bothering->SetAnimationIndex(3);

	//cActionSeq* pActionSeq = new cActionSeq;
	//for (int i = 1; i < path.size(); ++i)
	//{
	//	cActionMove* pActionMove = new cActionMove;
	//	pActionMove->SetFrom(m_pvecPoints[path[i - 1]]->GetTransform()->GetPosition());
	//	pActionMove->SetTo(m_pvecPoints[path[i]]->GetTransform()->GetPosition());
	//	pActionMove->SetActionTime(1.0f);
	//	pActionMove->SetOwner(m_pSkinnedMeshObject);
	//	//pActionMove->SetDelegate(this);
	//	pActionSeq->AddAction(pActionMove);
	//	SAFE_RELEASE(pActionMove);
	//}
	//pActionSeq->SetDelegate(this);
	///*cActionRepeat* pActionRepeat = new cActionRepeat;
	//pActionRepeat->SetAction(pActionSeq);*/
	////	pActionRepeat->SetDelegate(this);

	//m_pSkinnedMeshObject->SetAction(pActionSeq);
	//pActionSeq->Start();

	//SAFE_RELEASE(pActionSeq);
}

