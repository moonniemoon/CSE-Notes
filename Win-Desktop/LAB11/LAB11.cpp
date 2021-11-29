// LAB_11.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "LAB_11.h"
#include <string>
#include "strsafe.h"
#include <CommCtrl.h>

#define MAX_LOADSTRING 100
#define TIMER1 1001
#define TIMER2 1002

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
WCHAR szText[MAX_LOADSTRING];

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Test(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

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
    LoadStringW(hInstance, IDC_LAB11, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB11));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB11));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB11);
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
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_DIALOG:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG), hWnd, Test);
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

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); // black, to make it thick
        SelectObject(hdc, hPen);

        POINT pp[7];
        pp[0] = { 150, 100 };
        pp[1] = { 200, 133 };
        pp[2] = { 200, 165 };
        pp[3] = { 150, 200 };
        pp[4] = { 100, 165 };
        pp[5] = { 100, 133 };
        pp[6] = { 230, 300 };
        Polygon(hdc, pp, 6);   // Първите 6 май

        // в момента полигона са е затворил откадето е почнал, затова сме в позиция 0, трябва да отидем в позиция 1
        MoveToEx(hdc, pp[1].x, pp[1].y, NULL);
        LineTo(hdc, pp[6].x, pp[6].y);
        LineTo(hdc, pp[2].x, pp[2].y);

        MoveToEx(hdc, pp[3].x, pp[3].y, NULL);
        LineTo(hdc, pp[6].x, pp[6].y);
        LineTo(hdc, pp[4].x, pp[4].y);


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


double TryCatch_stod(HWND hDlg, int definesmth) {
    std::string::size_type sz;
    double d_smth;
    try {
        if (!GetDlgItemText(hDlg, definesmth, szText, MAX_LOADSTRING))
            *szText = 0;
        d_smth = std::stod(szText, &sz);
        StringCbPrintf(szText, ARRAYSIZE(szText), L"%.2f", d_smth);
        return d_smth;
    }
    catch (std::exception& e) {
        MessageBox(hDlg, L"Error to extract int value!", L"Error!",
            MB_ICONERROR | MB_OK);
        d_smth = 0.0;
        SetFocus(GetDlgItem(hDlg, definesmth));
        return d_smth;
    }
}

INT_PTR CALLBACK Test(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);

    double d_num;
    BOOL b_Ch1, b_Ch2;
    int index;
    std::string::size_type sz;
    static int iRange = 0, iStep = 0, iCurPos = 0, iCurPos2 = 0;  

    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_TIMER:
        b_Ch1 = IsDlgButtonChecked(hDlg, IDC_CHECK_P1) == BST_CHECKED;
        b_Ch2 = IsDlgButtonChecked(hDlg, IDC_CHECK_P2) == BST_CHECKED;
        if (b_Ch1) {
            SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_STEPIT, NULL, NULL);
            iCurPos += iStep;
        }
        else if (b_Ch2 && iCurPos2 < iRange) {
            SendDlgItemMessage(hDlg, IDC_PROGRESS2, PBM_STEPIT, NULL, NULL);
            iCurPos2 += iStep;
        }
        else if (b_Ch1 && b_Ch2) {
            if (iCurPos < iRange) {
                SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_STEPIT, (WPARAM)0, NULL);
                iCurPos += iStep;
            }
            else if (iCurPos2 < iRange) {
                SendDlgItemMessage(hDlg, IDC_PROGRESS2, PBM_STEPIT, (WPARAM)0, NULL);
                iCurPos2 += iStep;
            }
        }
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        switch (wmId) {

        case IDC_MOVE_TO_LIST:
            try {
                if (!GetDlgItemText(hDlg, IDC_ED_REAL, szText, MAX_LOADSTRING))
                    *szText = 0;
                d_num = std::stod(szText, &sz);
                StringCbPrintf(szText, ARRAYSIZE(szText), L"%.2f", d_num);
            }
            catch (std::exception& e) {
                MessageBox(hDlg, L"Error to extract int value!", L"Error!",
                    MB_ICONERROR | MB_OK);
                d_num = 0.0;
                SetFocus(GetDlgItem(hDlg, IDC_ED_REAL));
            }
            SendDlgItemMessage(hDlg, IDC_LIST, LB_ADDSTRING, NULL, (LPARAM)szText);
            return (INT_PTR)TRUE;

        case IDC_MOVE_TO_COMBO:
            index = SendDlgItemMessage(hDlg, IDC_LIST, LB_GETCURSEL, NULL, NULL);
            if (index != LB_ERR) {  // We have a selected element
                index = SendDlgItemMessage(hDlg, IDC_LIST, LB_GETTEXT, (WPARAM)index, (LPARAM)szText);
                if (index != LB_ERR)
                    SendDlgItemMessage(hDlg, IDC_COMBO, CB_ADDSTRING, NULL, (LPARAM)szText);
                else
                    MessageBox(hDlg, L"Error getting the selected item",
                        L"ERROR!", MB_OK | MB_ICONERROR);
            }
            return (INT_PTR)TRUE;

        case IDC_BTN_START:
            // LIST BOX:
            index = SendDlgItemMessage(hDlg, IDC_LIST, LB_GETCURSEL, NULL, NULL);  
            if (index == LB_ERR) {
                MessageBox(hDlg, L"No selected item in the list box!",
                    L"ERROR!", MB_OK | MB_ICONERROR);
                return (INT_PTR)TRUE;   // error
            }

            index = SendDlgItemMessage(hDlg, IDC_LIST, LB_GETTEXT, (WPARAM)index, (LPARAM)szText);
            iRange = std::stod(szText, NULL);

            // COMBO BOX:
            index = SendDlgItemMessage(hDlg, IDC_COMBO, CB_GETCURSEL, NULL, NULL);  // get from list
            if (index == CB_ERR) {
                MessageBox(hDlg, L"No selected item in the list box!",
                    L"ERROR!", MB_OK | MB_ICONERROR);
                return (INT_PTR)TRUE;   // error
            }

            index = SendDlgItemMessage(hDlg, IDC_COMBO, CB_GETLBTEXT, (WPARAM)index, (LPARAM)szText);
            iStep = std::stod(szText, NULL);

            SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETRANGE, NULL, MAKELPARAM(0, iRange));
            SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETSTEP, (WPARAM)iStep, NULL);
            SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETPOS, (WPARAM)0, NULL);  // да почва от 0
            iCurPos = 0;  // reset position

            SendDlgItemMessage(hDlg, IDC_PROGRESS2, PBM_SETRANGE, NULL, MAKELPARAM(0, iRange));
            SendDlgItemMessage(hDlg, IDC_PROGRESS2, PBM_SETSTEP, (WPARAM)iStep, NULL);
            SendDlgItemMessage(hDlg, IDC_PROGRESS2, PBM_SETPOS, (WPARAM)0, NULL);  // да почва от 0
            iCurPos = 0;

            SetTimer(hDlg, TIMER1, 1000, NULL);
            return (INT_PTR)TRUE;


        case IDC_BTN_STOP:
            KillTimer(hDlg, TIMER1);
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
