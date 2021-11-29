// 2nd_Example.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "strsafe.h"
#include <string>
#include "2nd_Example.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szText[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hDlgModeless;								// the modeless dialog box

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Calculate(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_MY2NDEXAMPLE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY2NDEXAMPLE));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        /* Showcase for Modeless Dialog Box
if (IsWindow(hWndAlt3) && IsDialogMessage(hWndAlt3, &msg))
    continue;
*/
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2NDEXAMPLE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY2NDEXAMPLE);
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
    HMENU hMenu, hSubMenu, hmenuTrackPopup;
    BOOL bRes, bRes2;
    UINT uRes, uRes2;
    MENUITEMINFO miinf;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            // Roles
            case ID_FUNCTIONS_CALC:
                DialogBox(hInst, MAKEINTRESOURCE(IDC_CALCULATE), hWnd, Calculate);
                break;

            case ID_ROLES_USER:
                hMenu = GetMenu(hWnd);
                CheckMenuItem(hMenu, ID_ROLES_USER, MF_BYCOMMAND | MF_CHECKED);
                CheckMenuItem(hMenu, ID_ROLES_ADMIN, MF_BYCOMMAND | MF_UNCHECKED);
                EnableMenuItem(hMenu, ID_FUNCTIONS_SEARCH, MF_BYCOMMAND | MF_ENABLED);
                EnableMenuItem(hMenu, ID_FUNCTIONS_UPDATE, MF_BYCOMMAND | MF_DISABLED);
                EnableMenuItem(hMenu, ID_FUNCTIONS_CALC, MF_BYCOMMAND | MF_DISABLED);
                break;

            case ID_ROLES_ADMIN:
                hMenu = GetMenu(hWnd);
                CheckMenuItem(hMenu, ID_ROLES_ADMIN, MF_BYCOMMAND | MF_CHECKED);
                CheckMenuItem(hMenu, ID_ROLES_USER, MF_BYCOMMAND | MF_UNCHECKED);
                EnableMenuItem(hMenu, ID_FUNCTIONS_SEARCH, MF_BYCOMMAND | MF_DISABLED);
                EnableMenuItem(hMenu, ID_FUNCTIONS_UPDATE, MF_BYCOMMAND | MF_ENABLED);
                EnableMenuItem(hMenu, ID_FUNCTIONS_CALC, MF_BYCOMMAND | MF_ENABLED);
                break;

            case ID_ROLES_NEW:
                hMenu = GetMenu(hWnd);
                hSubMenu = GetSubMenu(hMenu, 2);
                if (GetMenuState(hMenu, ID_ROLES_NEW + 1, MF_BYPOSITION) == -1) {                   
                    if (LOWORD(wParam) == ID_ROLES_NEW)
                    {
                        int iMsgBox = MessageBox(hWnd,
                            L"  Are you sure that you want to add a new item?",
                            L"Warning!",
                            MB_ICONEXCLAMATION | MB_YESNO);
                        if (iMsgBox == IDYES) {
                            ZeroMemory(&miinf, sizeof(miinf));
                            miinf.cbSize = sizeof(miinf);
                            miinf.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
                            miinf.wID = ID_ROLES_NEW + 1;
                            miinf.fType = MFT_STRING;
                            miinf.dwTypeData = (LPWSTR)_T("Special");
                            miinf.fState = MFS_ENABLED;
                            bRes = InsertMenuItem(hMenu, ID_ROLES_ADMIN, FALSE, &miinf);
                            EndDialog(hWnd, LOWORD(wParam));
                        }
                        return (INT_PTR)TRUE;
                    }
                }
                break;

            case ID_ROLES_DELETE:
                hMenu = GetMenu(hWnd);
                bRes = DeleteMenu(hMenu, ID_ROLES_OLD, MF_BYCOMMAND);
                break;

            // PopUp
            case ID_POPUP_FINISH:
                if (LOWORD(wParam) == ID_POPUP_FINISH)
                {
                    int iMsgBox = MessageBox(hWnd,
                        L"  Final Work!",
                        L"Good-Bye!",
                        MB_ICONHAND | MB_OK);
                    if (iMsgBox == IDOK)
                        EndDialog(hWnd, LOWORD(wParam));
                    return (INT_PTR)TRUE;
                }
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
    case WM_RBUTTONDOWN:
    {
        hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_POPUP));
        hSubMenu = GetSubMenu(hMenu, 0);
        POINT pt = { LOWORD(lParam), HIWORD(lParam) };
        ClientToScreen(hWnd, &pt);
        TrackPopupMenu(hSubMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
        DestroyMenu(hMenu);
        break;
    }
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


int TryCatch_stoi(HWND hDlg, int definesmth) {
    std::string::size_type sz;
    int i_smth;
    try {
        if (!GetDlgItemText(hDlg, definesmth, szText, MAX_LOADSTRING))
            *szText = 0;
        i_smth = std::stoi(szText, &sz);
        return i_smth;
    }
    catch (std::exception& e) {
        MessageBox(hDlg, L"Error to extract int value!", L"Error!",
            MB_ICONERROR | MB_OK);
        i_smth = 0;
        return i_smth;
    }
}
double TryCatch_stod(HWND hDlg, int definesmth) {
    std::string::size_type sz;
    double d_smth;
    try {
        if (!GetDlgItemText(hDlg, definesmth, szText, MAX_LOADSTRING))
            *szText = 0;
        d_smth = std::stod(szText, &sz);
        return d_smth;
    }
    catch (std::exception& e) {
        MessageBox(hDlg, L"Error to extract int value!", L"Error!",
            MB_ICONERROR | MB_OK);
        d_smth = 0.0;
        return d_smth;
    }
}


INT_PTR CALLBACK Calculate(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    double d_A, d_B, d_C, d_Result;
    BOOL bState;
    HWND smth;

    UINT M, N, P, F1, F2;
    BOOL bSigned1, bSigned2, bSigned3, bSuccess1, bSuccess2, bSuccess3;
    int i_M, i_N, i_P, i_Calc;

    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDC_BUTTON_INT:
            bSigned1 = bSigned2 = bSigned3 = FALSE;
            i_M = GetDlgItemInt(hDlg, IDC_EDIT_M, &bSuccess1, bSigned1);
            i_N = GetDlgItemInt(hDlg, IDC_EDIT_N, &bSuccess2, bSigned2);
            i_P = GetDlgItemInt(hDlg, IDC_EDIT_P, &bSuccess3, bSigned3);

            M = IsDlgButtonChecked(hDlg, IDC_CHECK_M);
            N = IsDlgButtonChecked(hDlg, IDC_CHECK_N);
            P = IsDlgButtonChecked(hDlg, IDC_CHECK_P);

            if (!bSuccess1 || !bSuccess2 || !bSuccess3) {
                MessageBox(hDlg, L"Error to extract int value!", L"Error!",
                    MB_ICONERROR | MB_OK);
            }
            else {
                i_M = GetDlgItemInt(hDlg, IDC_EDIT_M, &bSuccess1, TRUE);
                i_N = GetDlgItemInt(hDlg, IDC_EDIT_N, &bSuccess1, TRUE);
                i_P = GetDlgItemInt(hDlg, IDC_EDIT_P, &bSuccess1, TRUE);

                if ((M == BST_UNCHECKED && i_M ) || (N == BST_UNCHECKED && i_N == NULL) || (P == BST_UNCHECKED && i_P == NULL)) {
                    MessageBox(hDlg, L"Please check the values you want t!", L"Error!",
                        MB_ICONERROR | MB_OK);
                    break;
                }
                else {
                    i_Calc = (2 * i_M - i_N) * i_P;
                }
                StringCbPrintf(szText, ARRAYSIZE(szText), L"%d", i_Calc);
                    SetDlgItemText(hDlg, IDC_EDIT_INTEGER_RESULT, szText);
            }
            return (INT_PTR)TRUE;


        case IDC_BUTTON_REAL:
            d_A = TryCatch_stod(hDlg, IDC_EDIT_A);
            d_B = TryCatch_stod(hDlg, IDC_EDIT_B);
            d_C = TryCatch_stod(hDlg, IDC_EDIT_C);

            if (IsDlgButtonChecked(hDlg, IDC_RADIO_F1) == BST_CHECKED) {
                d_Result = (sqrt(d_B * d_B - 4 * d_A * d_C)) / 2 * d_B;
            }
            else if (IsDlgButtonChecked(hDlg, IDC_RADIO_F2) == BST_CHECKED) {
                d_Result = (d_A * d_A + d_B * d_B) / (d_C - d_A);
            }
            else {
                MessageBox(hDlg, L"Please check a radio button!", L"Error!",
                    MB_ICONERROR | MB_OK);
                break;
            }
            StringCbPrintf(szText, ARRAYSIZE(szText), L"%.2f", d_Result);
            SetDlgItemText(hDlg, IDC_EDIT_REAL_RESULT, szText);
            


            return (INT_PTR)TRUE;
        
        case IDOK:
        case IDCANCEL:
        case ID_CANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;

        }

    }
    return (INT_PTR)FALSE;
}

