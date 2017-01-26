// assignment3.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "assignment3.h"
#include <cstdio>

#define MAX_LOADSTRING 100

TrafficLight* tlHoriz = new TrafficLight(0);
TrafficLight* tlVert = new TrafficLight(1);

Lane* north = new Lane(tlVert);
Lane* south = new Lane(tlVert);
Lane* east = new Lane(tlHoriz);
Lane* west = new Lane(tlHoriz);

int pw = 20; // 20 in 100
int pn = 20;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Settings(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ASSIGNMENT3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ASSIGNMENT3));

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

    return (int) msg.wParam;
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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASSIGNMENT3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ASSIGNMENT3);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   SetTimer(hWnd, 1, 10, 0); // Tick timer
   SetTimer(hWnd, 2, 1000, 0); // Spawn timer

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void tick() {
    east->tick();
    north->tick();
    west->tick();
    south->tick();
    tlHoriz->tick();
    tlVert->tick();
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
    case WM_LBUTTONDOWN:
        {
            west->addCar();
            east->addCar();
        }
        break;
    case WM_RBUTTONDOWN:
        {
            north->addCar();
            south->addCar();
        }
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case ID_FILE_SETTINGS:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Settings);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_TIMER:
        {
            if (wParam == 1) {
                tick();
                tick();
            } else if (wParam == 2) {
                east->attemptSpawn(pw);
                north->attemptSpawn(pn);
                west->attemptSpawn(pw);
                south->attemptSpawn(pn);
            }
            InvalidateRect(hWnd, 0, true);
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            RECT rc;
            GetClientRect(hWnd, &rc);
            east->setLength(rc.right);
            north->setLength(rc.bottom);
            west->setLength(rc.right);
            south->setLength(rc.bottom);

            HDC virt = CreateCompatibleDC(hdc);
            HBITMAP bitmap = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
            SelectObject(virt, bitmap);

            Drawing::setScreenSize(rc);
            Drawing::drawBackground(virt);
            Drawing::drawTrafficLight(virt, tlVert, -35, -100);
            Drawing::drawTrafficLight(virt, tlVert, 35, 100);
            Drawing::drawTrafficLight(virt, tlHoriz, -80, 50);
            Drawing::drawTrafficLight(virt, tlHoriz, 80, -50);
            Drawing::drawLane(virt, east, DIRECTION_RIGHT);
            Drawing::drawLane(virt, north, DIRECTION_UP);
            Drawing::drawLane(virt, west, DIRECTION_LEFT);
            Drawing::drawLane(virt, south, DIRECTION_DOWN);

            WCHAR wc[4];
            wsprintf(wc, _T("%d"), pw);
            Drawing::write(virt, wc, -110, 30);
            Drawing::write(virt, wc, 95, -70);
            wsprintf(wc, _T("%d"), pn);
            Drawing::write(virt, wc, -65, -125);
            Drawing::write(virt, wc, 50, 80);

            /*/
            if (east->getFirstCar() != 0) {
                WCHAR sz[100];
                wsprintf(sz, _T("%d"), north->countCars());
                TextOut(virt, 100, 100, sz, wcslen(sz));
            }
            /**/

            BitBlt(hdc, 0, 0, rc.right, rc.bottom, virt, 0, 0, SRCCOPY);

            DeleteObject(bitmap);
            DeleteDC(virt);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_KEYDOWN:
    {
        switch(wParam)
        {
        case VK_UP:
            pn += 10;
            break;
        case VK_DOWN:
            pn -= 10;
            break;
        case VK_LEFT:
            pw -= 10;
            break;
        case VK_RIGHT:
            pw += 10;
            break;
        }
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
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

INT_PTR CALLBACK Settings(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        {
            HWND pwedit = GetDlgItem(hDlg, IDC_EDIT1);
            HWND pnedit = GetDlgItem(hDlg, IDC_EDIT3);
            WCHAR str[4];
            wsprintf(str, L"%d", pw);
            SetWindowText(pwedit, str);
            wsprintf(str, L"%d", pn);
            SetWindowText(pnedit, str);
            return (INT_PTR)TRUE;
        }

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            HWND pwedit = GetDlgItem(hDlg, IDC_EDIT1);
            HWND pnedit = GetDlgItem(hDlg, IDC_EDIT3);
            WCHAR str[4];
            char c[4];
            GetWindowText(pwedit, str, 4);
            sprintf_s(c, "%ws", str);
            pw = atoi(c);
            GetWindowText(pnedit, str, 4);
            sprintf_s(c, "%ws", str);
            pn = atoi(c);
        }
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}