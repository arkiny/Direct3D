// 121614 Simple2DGame.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include "121614 Simple2DGame.h"
#include "cMainGame.h"
#include "cGameTimer.h"

#include <sstream>
#include <time.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
///
HWND g_hWnd;
RECT g_wndRect;
cMainGame* g_pMainGame;
cGameTimer g_Timer;
std::wstring g_wsMainWndCaption;
///
// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
///
void				CalculateFrameStats();
///
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_MY121614SIMPLE2DGAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	g_pMainGame = new cMainGame;
	g_pMainGame->Setup();
	srand(GetCurrentTime());

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY121614SIMPLE2DGAME));

	g_Timer.Reset();

	// 기본 메시지 루프입니다.
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			g_Timer.Tick();
			CalculateFrameStats();
			g_pMainGame->Update(g_Timer.DeltaTime());
			g_pMainGame->Render();
		}
	}

	delete g_pMainGame;
	return (int) msg.wParam;
}

void CalculateFrameStats(){
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if ((g_Timer.TotalTime() - timeElapsed) >= 1.0f)
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::wostringstream outs;
		outs.precision(6);
		outs << g_wsMainWndCaption << L"    "
			<< L"FPS: " << fps << L"    "
			<< L"Frame Time: " << mspf << L" (ms)";
		SetWindowText(g_hWnd, outs.str().c_str());

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY121614SIMPLE2DGAME));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MY121614SIMPLE2DGAME);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   RECT windRect = { 0, 0, 400, 800 };
   ::AdjustWindowRect(&windRect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, NULL);
   g_wndRect = windRect;

   hWnd = CreateWindow(szWindowClass,
	   szTitle,
	   WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
	   CW_USEDEFAULT, 0,
	   windRect.right - windRect.left,
	   windRect.bottom - windRect.top,
	   NULL,
	   NULL,
	   hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   g_hWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	///
	case WM_KEYDOWN:
		cControl::GetInstance()->OnKeyDown(wParam);
		break;

	case WM_KEYUP:
		cControl::GetInstance()->OnKeyUP(wParam);
		break;

	case WM_LBUTTONDOWN:
		cControl::GetInstance()->OnKeyDown(wParam);
		cControl::GetInstance()->OnMouseClick(lParam);
		break;

	case WM_LBUTTONUP:
		// 이상하게 wParam에서 마우스 뗄때는 감지를 못한다.
		// 0으로 wParam값이 나옴
		cControl::GetInstance()->OnKeyUP(VK_LBUTTON);
		break;

	case WM_RBUTTONDOWN:
		cControl::GetInstance()->OnKeyDown(wParam);
		break;

	case WM_RBUTTONUP:
		cControl::GetInstance()->OnKeyUP(VK_RBUTTON);
		break;


		//case WM_LBUTTONDBLCLK:
		//	m_pControl->onKeyDown(wParam);
		//	break;

	case WM_MOUSEMOVE:
		cControl::GetInstance()->OnMouseMove(lParam);
		break;
	///
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
