// Seed.cpp : Defines the entry point for the application.
//


#include "stdafx.h"
#include <shellapi.h>
#include "Seed.h"
#include "Application.h"

#define MAX_LOADSTRING 100
#define DONATE_URL L"https://paypal.me/jackisaacssoftware"
#define USERMANUAL_URL L"https://paypal.me/jackisaacssoftware"

// Global Variables:
HWND windowHWND;
HWND currentWindowPaneHWND;
HINSTANCE hInst;
HMENU hMenu;

WCHAR szTitle[MAX_LOADSTRING];					// The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    LODManagerCallback(HWND, UINT, WPARAM, LPARAM);

Application application;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,	_In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_SEED, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SEED));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SEED);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassExW(&wcex);
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
	hInst = hInstance; // Store instance handle in our global variable

	windowHWND = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1500, 800, nullptr, nullptr, hInstance, nullptr);

	if (!windowHWND)
	{
		return FALSE;
	}

	hMenu = GetMenu(windowHWND);

	application.Init(windowHWND, hInst, hMenu);

	ShowWindow(windowHWND, nCmdShow);
	UpdateWindow(windowHWND);
	
	SetActiveWindowPane(IDD_BROADLEAF_FORM, hInstance, BroadLeafCallback);
	
	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case ID_LOD_LODMANAGER:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_LODMANAGER), hWnd, LODManagerCallback);
			break;
		case ID_HELP_USERMANUAL:
			ShellExecute(NULL, L"open", USERMANUAL_URL, NULL, NULL, SW_SHOW);
			break;
		case IDC_DONATE:
			ShellExecute(NULL, L"open", DONATE_URL, NULL, NULL, SW_SHOW);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

		case ID_TREETYPE_BROADLEAF:
			application.SetActiveTreeWindow(TREETYPE_BROADLEAF);
			break;
		case ID_TREETYPE_PINE:
			application.SetActiveTreeWindow(TREETYPE_PINE);
			break;
		case ID_TREETYPE_PALM:
			application.SetActiveTreeWindow(TREETYPE_PALM);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box
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

		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDC_DONATE:
			ShellExecute(NULL, L"open", DONATE_URL, NULL, NULL, SW_SHOW);
			break;
		}

		break;
	}

	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK LODManagerCallback(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		CheckDlgButton(hDlg, IDC_LOD_0_CHECK, BST_CHECKED);
		EnableWindow(GetDlgItem(hDlg, IDC_LOD_0_CHECK), false);

		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDC_DONATE:
			ShellExecute(NULL, L"open", DONATE_URL, NULL, NULL, SW_SHOW);
			break;
		}

		break;
	}
	return (INT_PTR)FALSE;
}

void SetActiveWindowPane(int id, HINSTANCE hInstance, DLGPROC callback)
{
	DestroyWindow(currentWindowPaneHWND);

	DialogBox(hInstance, MAKEINTRESOURCE(id), windowHWND, callback);
}

void SetFontLarge(HWND dlg, int id)
{
	HFONT font = CreateFont(20, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, L"MS Sans Serif");
	SendDlgItemMessage(dlg, id, WM_SETFONT, (WPARAM)font, (LPARAM)TRUE);
}

// Message handler for the broadleaf form
INT_PTR CALLBACK BroadLeafCallback(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
	case WM_INITDIALOG:
	{
		currentWindowPaneHWND = hDlg;
		EnableWindow(windowHWND, true);

		SetWindowPos(hDlg, NULL, 0, 0, 400, 800, 0);

		SetFontLarge(hDlg, IDC_BROADLEAFPROPERIES_LABEL);

		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:

		break;
	}

	return (INT_PTR)FALSE;
}

// Message handler for the pine 
INT_PTR CALLBACK PineCallback(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
	case WM_INITDIALOG:
	{
		currentWindowPaneHWND = hDlg;
		EnableWindow(windowHWND, true);

		SetWindowPos(hDlg, NULL, 0, 0, 400, 800, 0);

		SetFontLarge(hDlg, IDC_PINEPROPERTIES_LABEL);


		return (INT_PTR)TRUE;
	}
	case WM_COMMAND:

		break;
	}

	return (INT_PTR)FALSE;
}

// Message handler for the palm form
INT_PTR CALLBACK PalmCallback(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);

	switch (message)
	{
	case WM_INITDIALOG:
		currentWindowPaneHWND = hDlg;
		EnableWindow(windowHWND, true);
		SetWindowPos(hDlg, NULL, 0, 0, 400, 800, 0);

		SetFontLarge(hDlg, IDC_PALMPROPERTIES_LABEL);

		return (INT_PTR)TRUE;

	case WM_COMMAND:

		break;
	}

	return (INT_PTR)FALSE;
}