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
m_nScore(0),
m_pSphere(NULL),
m_pSkinnedMeshObject(NULL)
//m_pGraph(NULL)
//m_pCharacter(NULL),
//m_pHeightMap(NULL),
{
	srand(GetTickCount());
	GetCursorPos(&m_mousePos);
}

cMainGame::~cMainGame()
{

	cBox* p;
	while (!m_vecBox.empty()){
		p = (cBox*)m_vecBox.back();
		m_vecBox.pop_back();
		p->Destroy();
	}
	SAFE_DELETE(m_pPlayer);

	SAFE_DELETE(m_pPyramid);
	SAFE_DELETE(m_cAxis);
	SAFE_DELETE(m_cGrid);
	SAFE_DELETE(m_cCamera);

	//SAFE_DELETE(m_pGraph);
	/*for (auto p : m_vecCards){
		SAFE_RELEASE(p);
	}*/
	//for (auto p : m_vecEdges){
	//	SAFE_DELETE(p);
	//}

	//for (auto p : m_pvecPoints){
	//	SAFE_RELEASE(p);
	//}
	 
	for (auto p : m_vecSkinnedMeshObjects){
		SAFE_RELEASE(p);
	}
	
	//SAFE_RELEASE(m_pSkinnedMeshObject);
	//SAFE_RELEASE(m_pHeightMap);

	//SAFE_RELEASE(m_pCharacter);

	SAFE_RELEASE(m_pFont);
	SAFE_RELEASE(m_pSphere);
	SAFE_DELETE(m_pPlain);

	g_pTextureManager->Destroy();
	cDeviceManager* pDevice = cDeviceManager::GetInstance();
	pDevice->Destroy();
}

void cMainGame::Init(){
	m_cAxis = new cAxis(100.0f);
	m_cAxis->init();

	m_cGrid = new cGrid(100.0f, 100);
	m_cGrid->init();

	m_cCamera = new cCamera;
	m_cCamera->Setup();

	m_pPlayer = new cPlayer;
	m_pPlayer->Setup(this, NULL);
	m_cCamera->SetTarget(&m_pPlayer->GetPosition());

	m_pPyramid = new cPyramid;
	m_pPyramid->setup();

	m_pPlain = new cPlain;
	m_pPlain->Setup();

	m_pSphere = new cSphere;
	m_pSphere->Setup();
	m_pSphere->SetPosition(0, 1, 1);

	m_pTileMap = new cTileMap(16, 16);
	m_nWidth = m_pTileMap->GetBorder().x;
	m_nHeight = m_pTileMap->GetBorder().y;

	cTileMapLoader loader;
	POINT start;
	POINT dest;
	loader.LoadFromFile("data.txt", m_pTileMap, m_pTileMap->GetBorder().x, m_pTileMap->GetBorder().y, start, dest);

	//cAstarSP sp(m_pTileMap, start, dest);
	//sp.CalculatePath();
	////sp.PathToString();

	//std::vector<cTile*> path;
	//std::vector<cTile*> closed;
	//std::vector<cTile*> opened;

	//sp.GetPathPointVector(path, opened, closed);


	/*for (size_t i = 0; i < opened.size(); i++){
		m_pTileMap->SetTileType(opened[i]->GetPosition().x, opened[i]->GetPosition().y, cTile::eTILETYPE::TILE_OPENED);
	}
	for (size_t i = 0; i < closed.size(); i++){
		m_pTileMap->SetTileType(closed[i]->GetPosition().x, closed[i]->GetPosition().y, cTile::eTILETYPE::TILE_CLOSED);
	}
	for (size_t i = 0; i < path.size(); i++){
		m_pTileMap->SetTileType(path[i]->GetPosition().x, path[i]->GetPosition().y, cTile::eTILETYPE::TILE_PATH);
	}*/

	//m_pTileMap->SetTileType(start.x, start.y, cTile::eTILETYPE::TILE_START);
	//m_pTileMap->SetTileType(dest.x, dest.y, cTile::eTILETYPE::TILE_DEST);


	cBox* _box;
	m_vecBox.resize(m_nWidth * m_nHeight);

	for (int i = 0; i < m_nHeight; i++){
		for (int j = 0; j < m_nWidth; j++){
			_box = new cBox;
			_box->init();
			GRIDPOSITION a = { j , 0, /*m_nHeight - */i/* - 1*/ };
			_box->setPositionByGrid(a);
			_box->setHP(3.0f);
			_box->setTile(m_pTileMap->GetTilePointer(j, i));
			m_vecBox[j + i* m_nWidth] = _box;
		}
	}

	//m_pSkinnedMeshObject = new cSkinnedMeshObject;
	//m_pSkinnedMeshObject->Setup();
	//
	//
	//if (m_pCharacter){
	//	m_cCamera->SetTarget(m_pCharacter->GetPosition());
	//}
	
	// 0 (-2, 0, 0)
	// 1 (0, 0, 0)
	// 2 (0,0,4)
	// 3 (1,0,4)
	// 4 (1,0,3)
	// 5 (-2,0,-3)
	// 6 (1, 0, -2)
	// 7 (3, 0, 0)
	//0

	//cAPoint* p = new cAPoint;
	//p->Setup(D3DXCOLOR(0.8f, 0.3f, 0.3f, 1.0f), D3DXVECTOR3(-2.0f, 0, 0));
	//p->SetPointInfo(0); 
	//m_pvecPoints.push_back(p);
	//1
	//p = new cAPoint;
	//p->Setup(D3DXCOLOR(0.8f, 0.3f, 0.3f, 1.0f), D3DXVECTOR3(0, 0, 0));
	//p->SetPointInfo(1);
	//m_pvecPoints.push_back(p);
	//2
	//p = new cAPoint;
	//p->Setup(D3DXCOLOR(0.8f, 0.3f, 0.3f, 1.0f), D3DXVECTOR3(0, 0, 8.0f));
	//p->SetPointInfo(2);
	//m_pvecPoints.push_back(p);
	//
	////3
	//p = new cAPoint;
	//p->Setup(D3DXCOLOR(0.8f, 0.3f, 0.3f, 1.0f), D3DXVECTOR3(4.0f, 0, 3.0f));
	//p->SetPointInfo(3);
	//m_pvecPoints.push_back(p);
	//
	////4
	//p = new cAPoint;
	//p->Setup(D3DXCOLOR(0.8f, 0.3f, 0.3f, 1.0f), D3DXVECTOR3(4.0f, 0, 6.0f));
	//p->SetPointInfo(4);
	//m_pvecPoints.push_back(p);

	////5
	//p = new cAPoint;
	//p->Setup(D3DXCOLOR(0.8f, 0.3f, 0.3f, 1.0f), D3DXVECTOR3(-4.0f, 0, -6.0f));
	//p->SetPointInfo(5);
	//m_pvecPoints.push_back(p);

	//m_pSkinnedMeshObject->GetTransform()
	//	->SetPosition(p->GetTransform()->GetPosition());


	////6
	//p = new cAPoint;
	//p->Setup(D3DXCOLOR(0.8f, 0.3f, 0.3f, 1.0f), D3DXVECTOR3(2.0f, 0, -4.0f));
	//p->SetPointInfo(6);
	//m_pvecPoints.push_back(p);
	//
	////7
	//p = new cAPoint;
	//p->Setup(D3DXCOLOR(0.8f, 0.3f, 0.3f, 1.0f), D3DXVECTOR3(6.0f, 0, 0));
	//p->SetPointInfo(7);
	//m_pvecPoints.push_back(p);

	//cEdge* pE = new cEdge;
	//m_pGraph = new cGraph(m_pvecPoints.size());
	//m_pGraph->setEdge(0, 1, m_pvecPoints);
	//pE = new cEdge;
	//pE->Setup(m_pvecPoints[0]->GetTransform()->GetPosition(), m_pvecPoints[1]->GetTransform()->GetPosition());
	//m_vecEdges.push_back(pE);

	//m_pGraph->setEdge(0, 5, m_pvecPoints);
	//pE = new cEdge;
	//pE->Setup(m_pvecPoints[0]->GetTransform()->GetPosition(), m_pvecPoints[5]->GetTransform()->GetPosition());
	//m_vecEdges.push_back(pE);

	//m_pGraph->setEdge(1, 2, m_pvecPoints);
	//pE = new cEdge;
	//pE->Setup(m_pvecPoints[1]->GetTransform()->GetPosition(), m_pvecPoints[2]->GetTransform()->GetPosition());
	//m_vecEdges.push_back(pE);

	//m_pGraph->setEdge(1, 3, m_pvecPoints);
	//pE = new cEdge;
	//pE->Setup(m_pvecPoints[1]->GetTransform()->GetPosition(), m_pvecPoints[3]->GetTransform()->GetPosition());
	//m_vecEdges.push_back(pE);

	//m_pGraph->setEdge(2, 4, m_pvecPoints);
	//pE = new cEdge;
	//pE->Setup(m_pvecPoints[2]->GetTransform()->GetPosition(), m_pvecPoints[4]->GetTransform()->GetPosition());
	//m_vecEdges.push_back(pE);

	//m_pGraph->setEdge(3, 4, m_pvecPoints);
	//pE = new cEdge;
	//pE->Setup(m_pvecPoints[3]->GetTransform()->GetPosition(), m_pvecPoints[4]->GetTransform()->GetPosition());
	//m_vecEdges.push_back(pE);

	//m_pGraph->setEdge(3, 6, m_pvecPoints);
	//pE = new cEdge;
	//pE->Setup(m_pvecPoints[3]->GetTransform()->GetPosition(), m_pvecPoints[6]->GetTransform()->GetPosition());
	//m_vecEdges.push_back(pE);

	//m_pGraph->setEdge(4, 7, m_pvecPoints);
	//pE = new cEdge;
	//pE->Setup(m_pvecPoints[4]->GetTransform()->GetPosition(), m_pvecPoints[7]->GetTransform()->GetPosition());
	//m_vecEdges.push_back(pE);

	//m_pGraph->setEdge(5, 6, m_pvecPoints);
	//pE = new cEdge;
	//pE->Setup(m_pvecPoints[5]->GetTransform()->GetPosition(), m_pvecPoints[6]->GetTransform()->GetPosition());
	//m_vecEdges.push_back(pE);

	//m_pGraph->setEdge(6, 7, m_pvecPoints);
	//pE = new cEdge;
	//pE->Setup(m_pvecPoints[6]->GetTransform()->GetPosition(), m_pvecPoints[7]->GetTransform()->GetPosition());
	//m_vecEdges.push_back(pE);


	//std::vector<int> path;
	//m_nCurrentNode = 2;
	//m_nDestination = 6;
	//cDjikstraSP sp(m_pGraph, m_nCurrentNode, m_nDestination);
	//sp.SetupAndCalculate();
	//sp.GetShortestPathAsVector(path);


	cSkinnedMeshObject* pSkinnedMesh;
	pSkinnedMesh = new cSkinnedMeshObject;
	pSkinnedMesh->Setup();
	pSkinnedMesh->SetAnimationIndex(4);
	m_vecSkinnedMeshObjects.push_back(pSkinnedMesh);
	
	pSkinnedMesh = new cSkinnedMeshObject;
	pSkinnedMesh->Setup();
	pSkinnedMesh->SetAnimationIndex(4);
	pSkinnedMesh->SetPosition(2.0f, 0.0f, 4.0f);
	m_vecSkinnedMeshObjects.push_back(pSkinnedMesh);

	//cActionSeq* pActionSeq = new cActionSeq;
	//for (int i = 1; i < path.size(); ++i)
	//{
	//	cActionMove* pActionMove = new cActionMove;
	//	pActionMove->SetFrom(m_pvecPoints[path[i-1]]->GetTransform()->GetPosition());
	//	pActionMove->SetTo(m_pvecPoints[path[i]]->GetTransform()->GetPosition());
	//	//pActionMove->SetFrom(m_pvecPoints[path[i - 1]]->GetTransform()->GetPosition() );
	//	//pActionMove->SetTo(m_pvecPoints[path[i]]->GetTransform()->GetPosition() );
	//	pActionMove->SetActionTime(1.0f);
	//	pActionMove->SetOwner(m_pSkinnedMeshObject);
	//	//pActionMove->SetDelegate(this);
	//	pActionSeq->AddAction(pActionMove);
	//	SAFE_RELEASE(pActionMove);
	//}
	//pActionSeq->SetDelegate(this);
	/*cActionRepeat* pActionRepeat = new cActionRepeat;
	pActionRepeat->SetAction(pActionSeq);*/
	//	pActionRepeat->SetDelegate(this);

	//m_pSkinnedMeshObject->SetAction(pActionSeq);
	//pActionSeq->Start();

	//SAFE_RELEASE(pActionSeq);


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

}


void cMainGame::Update(float delta){
	m_fAccumTime += delta;
	
	//m_pPlayer->Update(delta);
	m_cCamera->Update(delta);

	//if (m_pCharacter){
	//	m_pCharacter->Update(delta);
	//}

	//bool isLand = false;
	//if (m_pHeightMap){
	//	m_pHeightMap->GetHeight(isLand, m_pCharacter->GetPosition());
	//}
	//
	

	for (auto p : m_vecSkinnedMeshObjects){
		p->Update(delta);
	}
}

void cMainGame::Render(){
	D3DXMATRIXA16 matRot, matWorld;

	g_pD3DDevice->Clear(NULL,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		//D3DCOLOR_XRGB(47, 121, 112),
		D3DCOLOR_XRGB(0, 0, 0),
		1.0f, 0);
	g_pD3DDevice->BeginScene();
	
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_pPyramid->render();
	m_cAxis->render();
	m_cGrid->render();

	for (auto box : m_vecBox){
		box->render();
	}

	//for (auto p : m_vecEdges){
	//	p->Render();
	//}



	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);


	//SAFE_RENDER(m_pPlain);
	for (auto p : m_vecSkinnedMeshObjects){
		SAFE_RENDER(p);
	}

	//if (m_pSphere){
	//	m_pSphere->Render();
	//}

	//if (m_pHeightMap){
	//	m_pHeightMap->Render();
	//}
	//if (m_pCharacter){
	//	m_pCharacter->Render();
	//}

	//D3DXMATRIXA16 matI;
	//D3DXMatrixIdentity(&matI);
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);

	//if (m_pSkinnedMeshObject){
	//	m_pSkinnedMeshObject->Render();
	//}

	//for (auto p : m_pvecPoints){
	//	if (p){
	//		p->Render();
	//	}
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
		/*m_bClicked = true;*/
		{
			cMousePeeking m;
			Ray ray = m.CalcPickRay(LOWORD(lParam), HIWORD(lParam));

			D3DXMATRIXA16 view;
			g_pD3DDevice->GetTransform(D3DTS_VIEW, &view);

			// To World Space
			D3DXMatrixInverse(&view, 0, &view);
			m.TransformRay(&ray, view);

			if (m_bCharacterSelected){

				for (auto p : m_vecSkinnedMeshObjects){
					if (m.IsCrossWithSphere(&ray, p->GetSphere())){
						if (m_pSkinnedMeshObject){
							m_pSkinnedMeshObject->SetSelcted(false);
						}
						m_pSkinnedMeshObject = p;
						m_pSkinnedMeshObject->SetSelcted(true);
						m_bCharacterSelected = true;
						break;
					}
				}		
				//else{
				//	m_pSkinnedMeshObject->SetSelcted(false);
				//	m_bCharacterSelected = false;
				//	m_pSkinnedMeshObject = NULL;
				//}

			}

			else{
				for (auto p : m_vecSkinnedMeshObjects){
					if (m.IsCrossWithSphere(&ray, p->GetSphere())){
						p->SetSelcted(true);
						m_pSkinnedMeshObject = p;
						m_bCharacterSelected = true;
						break;
					}
				}					
			}			
		}
		break;
	}

	case WM_RBUTTONUP:{
		cMousePeeking m;
		Ray ray = m.CalcPickRay(LOWORD(lParam), HIWORD(lParam));

		D3DXMATRIXA16 view;
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &view);

		D3DXMatrixInverse(&view, 0, &view);
		m.TransformRay(&ray, view);

		if (m_bCharacterSelected && m_pSkinnedMeshObject){
			
			bool isCrossed = false;
			D3DXVECTOR3 crossed(0, 0, 0);

			for (auto p : m_vecBox){
				crossed = m.GetCrossSectionWithPlain(&ray, p->GetSurfacePoints(), isCrossed);
				if (isCrossed){
					break;
				}
			}			
			
			if (isCrossed){
				if (m_pSkinnedMeshObject){
					//m_pSkinnedMeshObject->SetPosition(crossed);
					//m_nCurrentNode = m_nDestination;
					//m_nDestination = TargetNode;

					//if (TargetNode == m_nCurrentNode){
					//	OnActionFinish(pSender);
					//	return;
					//}
					
					D3DXVECTOR3 playerCurpos 
						= m_pSkinnedMeshObject->GetTransform()->GetPosition();

					int gridx = (int)(abs(playerCurpos.x / 1.0f));
					int gridy = playerCurpos.y;
					int gridz = (int)(abs(playerCurpos.z / 1.0f));
					
					int crossedx = (int)(abs(crossed.x / 1.0f));
					int crossedy = crossed.y;
					int crossedz = (int)(abs(crossed.z / 1.0f));

					POINT start = { gridx, gridz };
					POINT dest = { crossedx, crossedz };

					cAstarSP sp(m_pTileMap, start, dest);
					sp.CalculatePath();

					std::vector<cTile*> path;
					sp.GetPathPointVector(path);

					//cAstarSP sp(m_pTileMap, );
					
							
					D3DXVECTOR3 pos = { path[path.size() - 2]->GetPosition().x * 1.0f, playerCurpos.y, path[path.size() - 2]->GetPosition().y * 1.0f };
					m_pSkinnedMeshObject->SetAnimationIndex(3);
					// new sequence
					cActionSeq* pActionSeq = new cActionSeq;	

					cActionMove* pActionMove = new cActionMove;
					pActionMove->SetFrom(playerCurpos
						= m_pSkinnedMeshObject->GetTransform()->GetPosition());
					pActionMove->SetTo(pos);
					float length = D3DXVec3Length(&(m_pSkinnedMeshObject->GetTransform()->GetPosition() - pos));

					pActionMove->SetActionTime(1.0f * (length / 5.0f));
					pActionMove->SetOwner(m_pSkinnedMeshObject);
					//pActionMove->SetDelegate(this);
					pActionSeq->AddAction(pActionMove);
					SAFE_RELEASE(pActionMove);


					for (int i = path.size() - 2; i >= 2; --i)
					{
						cActionMove* pActionMove = new cActionMove;
						D3DXVECTOR3 frompos = { path[i]->GetPosition().x * 1.0f, playerCurpos.y, path[i]->GetPosition().y * 1.0f };
						D3DXVECTOR3 topos = { path[i-1]->GetPosition().x * 1.0f, playerCurpos.y, path[i-1]->GetPosition().y * 1.0f };

						pActionMove->SetFrom(frompos);
						pActionMove->SetTo(topos);
						float length = D3DXVec3Length(&(frompos - topos));

						pActionMove->SetActionTime(1.0f * (length / 5.0f));
						pActionMove->SetOwner(m_pSkinnedMeshObject);
						//pActionMove->SetDelegate(this);
						pActionSeq->AddAction(pActionMove);
						SAFE_RELEASE(pActionMove);
					}

					pos = { path[1]->GetPosition().x * 1.0f, playerCurpos.y, path[1]->GetPosition().y * 1.0f };
					m_pSkinnedMeshObject->SetAnimationIndex(3);
					pActionMove = new cActionMove;

					pActionMove->SetFrom(pos);
					pActionMove->SetTo(crossed);

					length = D3DXVec3Length(&(crossed - pos));
					pActionMove->SetActionTime(1.0f * (length / 5.0f));
					pActionMove->SetOwner(m_pSkinnedMeshObject);
					//pActionMove->SetDelegate(this);
					pActionSeq->AddAction(pActionMove);
					SAFE_RELEASE(pActionMove);


					pActionSeq->SetDelegate(this);
					/*cActionRepeat* pActionRepeat = new cActionRepeat;
					pActionRepeat->SetAction(pActionSeq);*/
					//	pActionRepeat->SetDelegate(this);

					m_pSkinnedMeshObject->SetAction(pActionSeq);
					pActionSeq->Start();

					SAFE_RELEASE(pActionSeq);


				}
			}
		}
		break;
	}
						
	case WM_LBUTTONUP:
	{
		m_bClicked = false;
		break;
	}

	case WM_KEYDOWN:
	{
	/*	switch (wParam)
		{
		case '1':
			m_pSkinnedMeshObject->SetAnimationIndex(0);
			break;
		}*/
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

cBox* cMainGame::getBoxInfoFromGrid(int x, int z){
	if (x < m_nHeight && z < m_nWidth && x >= 0 && z >= 0){
		return m_vecBox[z + x * m_nWidth];
	}
	else {
		return NULL;
	}
}
