// LAB_9.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "LAB_9.h"
#include <math.h>
#include <string>
#include "strsafe.h"
#include <Commctrl.h>


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
POINT ptLMDown;
WCHAR szText[MAX_LOADSTRING];
UINT_PTR TIMER1;
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hDlgModeless;								// the modeless dialog box

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
int                 LenOfLine(POINT pt1, POINT pt2);
INT_PTR CALLBACK    DlgKeyMouTmrFunc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

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
    LoadStringW(hInstance, IDC_LAB9, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB9));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB9));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB9);
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
   hDlgModeless = NULL;

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    POINT pt;
    int iLen;


    switch (message)
    {
   

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_TESTDIALOG:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_KEYMOUTMR), hWnd, DlgKeyMouTmrFunc);
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    
    case WM_RBUTTONUP:
        // в помощна променлива получаваме точката на натискане на десния бутон на мишката
        pt = { LOWORD(lParam), HIWORD(lParam) };
        iLen = LenOfLine(pt, { 100, 100 });   
        // форматираме и извеждаме съобщение за дължината
        StringCbPrintf(szText, ARRAYSIZE(szText),
            L"Point of click {%i,%i}. \nDistance to target %i.", pt.x, pt.y, iLen);
        MessageBox(hWnd, szText, L"Info", MB_OK);
        break;

    case WM_LBUTTONDOWN:  // натискане на левия бутон
        ptLMDown = { LOWORD(lParam), HIWORD(lParam) };
        break;

    case WM_LBUTTONUP:   // отпускане на левия бутон
        pt = { LOWORD(lParam), HIWORD(lParam) };
        iLen = LenOfLine(pt, ptLMDown);   // pt = където сме отпуснали бутона
        // ptLMDown = където сме натиснали бутона
        StringCbPrintf(szText, ARRAYSIZE(szText),
            L"Line {%i,%i} - {%i,%i}. \nLength of line %i.", ptLMDown.x, ptLMDown.y, pt.x, pt.y, iLen);
        MessageBox(hWnd, szText, L"Info", MB_OK);
        break;

    case WM_KEYDOWN:
        if (wParam == VK_F5)
            ShowWindow(hWnd, SW_MAXIMIZE);   // максимизиране на основния прозорец
        if (wParam == VK_F6)
            ShowWindow(hWnd, SW_RESTORE);    // възстановяване на нормалния размер на основния прозорец
        if (wParam == VK_F7)
            ShowWindow(hWnd, SW_MINIMIZE);   // минимизиране на основния прозорец
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

int LenOfLine(POINT pt1, POINT pt2) {
    //d=√((x_2-x_1)²+(y_2-y_1)²) to find the distance between any two points.
    int square_difference_x = (pt2.x - pt1.x) * (pt2.x - pt1.x);
    int square_difference_y = (pt2.y - pt1.y) * (pt2.y - pt1.y);
    int sum = square_difference_x + square_difference_y;
    int value = sqrt(sum);
    return value;
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


INT_PTR CALLBACK DlgKeyMouTmrFunc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    BYTE wTmp;

    switch (message)
    {
    case WM_INITDIALOG:
        SendDlgItemMessage(hDlg, IDC_ED_PASS, EM_SETLIMITTEXT, (WPARAM)16, NULL);   // установяваме максималната дължина на 16
        SendDlgItemMessage(hDlg, IDC_ED_PASS, EM_SETPASSWORDCHAR, (WPARAM)'o', NULL);  // променяме символа за парола от "*" на "о"
        return (INT_PTR)TRUE;

    case WM_LBUTTONDOWN:
        SendDlgItemMessage(hDlg, IDC_PROGRESS, PBM_SETRANGE, NULL, MAKELPARAM(0, 100));   // 0-100
        SendDlgItemMessage(hDlg, IDC_PROGRESS, PBM_SETSTEP, (WPARAM)1, NULL);  // за една секунда 1 напред?
        SetTimer(hDlg, TIMER1, 100, NULL);        // овеличява стойността на IDC_PROGRESS на 0.1 секундa веднъж
        return (INT_PTR)TRUE;

    case WM_LBUTTONUP:
        KillTimer(hDlg, TIMER1);                 // спира таймера
        return (INT_PTR)TRUE;

    case WM_TIMER:
        SendDlgItemMessage(hDlg, IDC_PROGRESS, PBM_STEPIT, NULL, NULL);
        return (INT_PTR)TRUE;


    // for RIGHT button
    case WM_RBUTTONDOWN:
        SendDlgItemMessage(hDlg, IDC_PROGRESS, PBM_SETRANGE, NULL, MAKELPARAM(0, 10));  // 0-10
        SendDlgItemMessage(hDlg, IDC_PROGRESS, PBM_SETSTEP, (WPARAM)-1, NULL);   
        SetTimer(hDlg, TIMER1, 1000, NULL); // 1 сек
        return (INT_PTR)TRUE;

    case WM_RBUTTONUP:
        KillTimer(hDlg, TIMER1);                 // спира таймера
        return (INT_PTR)TRUE;

       


    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        switch (wmId) {

        case IDC_BTN_CHECK:
            wTmp = SendDlgItemMessage(hDlg, IDC_ED_PASS, EM_LINELENGTH, NULL, NULL);
            if (wTmp < 8) {
                MessageBox(hDlg, L"The minimum length is 8!", L"Error", MB_OK);
            }
            return (INT_PTR)TRUE;

        case IDOK:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
    }
    return (INT_PTR)FALSE;
}
