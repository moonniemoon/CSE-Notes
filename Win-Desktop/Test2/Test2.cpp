// FN19621447.cpp : Defines the entry point for the application.
// Selin Tahsin Kayar - 19621447 - KST - 1A 

#include "framework.h"
#include "FN19621447.h"
#include <string>
#include "strsafe.h"
#include "commctrl.h"
#include <math.h>

#define MAX_LOADSTRING 100
#define TIMER1 1001
#define TIMER2 1002

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
WCHAR szText[MAX_LOADSTRING];
HWND hDlgModeless;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Test(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Dialog2(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_FN19621447, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FN19621447));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FN19621447));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_FN19621447);
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
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case ID_TEST2:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG), hWnd, Test);
                break;
            case ID_DIALOG2:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_2), hWnd, Dialog2);
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
            
            POINT pp[9];
            pp[0] = { 100, 125 };
            pp[1] = { 200, 100 };
            pp[2] = { 300, 125 };
            pp[3] = { 230, 150 };
            pp[4] = { 170, 150 };
            pp[5] = { 100, 270 };
            pp[6] = { 170, 300 };
            pp[7] = { 230, 300 };
            pp[8] = { 300, 270 };
            Polygon(hdc, pp, 5);

            MoveToEx(hdc, pp[0].x, pp[0].y, NULL);
            LineTo(hdc, pp[5].x, pp[5].y);
            LineTo(hdc, pp[6].x, pp[6].y);
            LineTo(hdc, pp[4].x, pp[4].y);

            MoveToEx(hdc, pp[3].x, pp[3].y, NULL);
            LineTo(hdc, pp[7].x, pp[7].y);
            LineTo(hdc, pp[8].x, pp[8].y);
            LineTo(hdc, pp[2].x, pp[2].y);

            MoveToEx(hdc, pp[6].x, pp[6].y, NULL);
            LineTo(hdc, pp[7].x, pp[7].y);


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

    double d_num, d_res, d_f2;
    int index, i_num;
    BOOL bState, bSigned, bSuccess;
    HWND smth;

    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        switch (wmId)
        {

        case IDC_CHECK_F1:
            bState = IsDlgButtonChecked(hDlg, IDC_CHECK_F1);
            smth = GetDlgItem(hDlg, IDC_EDIT_F1);
            EnableWindow(smth, bState & TRUE ? TRUE : FALSE);
            return (INT_PTR)TRUE;

        case IDC_CHECK_F2:
            bState = IsDlgButtonChecked(hDlg, IDC_CHECK_F2);
            smth = GetDlgItem(hDlg, IDC_COMBO_F2);
            EnableWindow(smth, bState & TRUE ? TRUE : FALSE);
            return (INT_PTR)TRUE;

        case IDC_CHECK_F3:
            bState = IsDlgButtonChecked(hDlg, IDC_CHECK_F3);
            smth = GetDlgItem(hDlg, IDC_EDIT_F3);
            EnableWindow(smth, bState & TRUE ? TRUE : FALSE);
            return (INT_PTR)TRUE;


        case IDC_BTN_MOVE:
            d_num = TryCatch_stod(hDlg, IDC_EDIT_F1);
            index = SendDlgItemMessage(hDlg, IDC_COMBO_F2, CB_FINDSTRING, NULL, (LPARAM)szText);
            if (index == -1)     // d_Num not found
                SendDlgItemMessage(hDlg, IDC_COMBO_F2, CB_ADDSTRING, NULL, (LPARAM)szText);
            else {
                MessageBox(hDlg, L"You have already added this number!",
                    L"ERROR!", MB_OK | MB_ICONERROR);
            }
            return (INT_PTR)TRUE;


        case IDC_BTN_CALC:
            bSigned = FALSE;
            i_num = GetDlgItemInt(hDlg, IDC_EDIT_F3, &bSuccess, bSigned);
            if (!bSuccess)
            {
                MessageBox(hDlg, L"Error to extract int value!\nDouble, String values are forbidden.", L"Error!",
                    MB_ICONERROR | MB_OK);
            }
            else {
                i_num = GetDlgItemInt(hDlg, IDC_EDIT_F3, &bSuccess, TRUE);
                d_num = TryCatch_stod(hDlg, IDC_EDIT_F1);

                index = SendDlgItemMessage(hDlg, IDC_COMBO_F2, CB_GETCURSEL, (WPARAM)NULL, (LPARAM)NULL);
                if (index != CB_ERR) {
                    index = SendDlgItemMessage(hDlg, IDC_COMBO_F2, CB_GETLBTEXT, (WPARAM)index, (LPARAM)szText);
                }
                d_f2 = std::stod(szText, NULL);

                d_res = (d_num + d_f2) / i_num;

                StringCbPrintf(szText, ARRAYSIZE(szText), L"%.2f", d_res);
                SetDlgItemText(hDlg, IDC_EDIT_CALC, szText);
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

INT_PTR CALLBACK Dialog2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);

    switch (message)
    {
    case WM_INITDIALOG:
        SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETRANGE, NULL, MAKELPARAM(0, 10));
        SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETPOS, (WPARAM)10, NULL);
        SendDlgItemMessage(hDlg, IDC_PROGRESS2, PBM_SETPOS, (WPARAM)-1, NULL);
        return (INT_PTR)TRUE;

    
    case WM_TIMER:
        SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_STEPIT, NULL, NULL);
        SendDlgItemMessage(hDlg, IDC_PROGRESS2, PBM_STEPIT, NULL, NULL);
        return (INT_PTR)TRUE;



    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDC_BTN_START:
            SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETRANGE, NULL, MAKELPARAM(0, 10));   // 0-10
            SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETSTEP, (WPARAM)1, NULL);  

            SendDlgItemMessage(hDlg, IDC_PROGRESS2, PBM_SETRANGE, NULL, MAKELPARAM(0, 10));  // 0-10
            SendDlgItemMessage(hDlg, IDC_PROGRESS2, PBM_SETSTEP, (WPARAM)-1, NULL);
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
