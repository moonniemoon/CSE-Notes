// 1st_Example.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "strsafe.h"
#include <string>
#include "1st_Example.h"

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
INT_PTR CALLBACK	Calculation(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_MY1STEXAMPLE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1STEXAMPLE));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1STEXAMPLE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY1STEXAMPLE);
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

            // XMENU
            case ID_XMENU_CALCULATION:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_CALCULATION), hWnd, Calculation);
                break;

            case ID_XMENU_DRINKS:
                hMenu = GetMenu(hWnd);
                //uRes = GetMenuState(hMenu, ID_XMENU_DRINKS, MF_BYCOMMAND);
                CheckMenuItem(hMenu, ID_XMENU_DRINKS, MF_BYCOMMAND | MF_CHECKED);
                CheckMenuItem(hMenu, ID_XMENU_FRUITS, MF_BYCOMMAND | MF_UNCHECKED);
                EnableMenuItem(hMenu, ID_ITEMS_TEA, MF_BYCOMMAND | MF_ENABLED);
                EnableMenuItem(hMenu, ID_ITEMS_APPLE, MF_BYCOMMAND | MF_DISABLED);

                /*bRes = ModifyMenu(hMenu, ID_TOOLS_CHECKME, MF_BYCOMMAND | uRes & MF_CHECKED ? MF_UNCHECKED : MF_CHECKED,
                    ID_TOOLS_CHECKME, uRes & MF_CHECKED ? L"Check Me" : L"Uncheck Me");*/
                break;

            case ID_XMENU_FRUITS:
                hMenu = GetMenu(hWnd);
                CheckMenuItem(hMenu, ID_XMENU_FRUITS, MF_BYCOMMAND | MF_CHECKED);
                CheckMenuItem(hMenu, ID_XMENU_DRINKS, MF_BYCOMMAND | MF_UNCHECKED);
                EnableMenuItem(hMenu, ID_ITEMS_APPLE, MF_BYCOMMAND | MF_ENABLED);
                EnableMenuItem(hMenu, ID_ITEMS_TEA, MF_BYCOMMAND | MF_DISABLED);
                break;

            case ID_XMENU_OTHER:
                hMenu = GetMenu(hWnd);
                hSubMenu = GetSubMenu(hMenu, 2);
                if (GetMenuState(hMenu, ID_XMENU_OTHER + 1, MF_BYPOSITION) == -1) {
                    ZeroMemory(&miinf, sizeof(miinf));
                    miinf.cbSize = sizeof(miinf);
                    miinf.fMask = MIIM_ID | MIIM_TYPE | MIIM_STATE;
                    miinf.wID = ID_XMENU_OTHER + 1;
                    miinf.fType = MFT_STRING;
                    miinf.dwTypeData = (LPWSTR)_T("Food");
                    miinf.fState = MFS_ENABLED;
                    bRes = InsertMenuItem(hMenu, ID_XMENU_FRUITS, FALSE, &miinf);
                }
                break;
           
            case ID_XMENU_OTHER + 1:
                hMenu = GetMenu(hWnd);
                 
                 if (LOWORD(wParam) == ID_XMENU_OTHER + 1)
                 {
                     int iMsgBox = MessageBox(hWnd,
                         L"  Are you Sure?",
                         L"Warning!",
                         MB_ICONERROR | MB_YESNO);
                     if (iMsgBox == IDYES) {
                         bRes = DeleteMenu(hMenu, ID_XMENU_OTHER + 1, MF_BYCOMMAND);
                         EndDialog(hWnd, LOWORD(wParam));
                     }
                     return (INT_PTR)TRUE;
                 }
                break;


            // Pop-up
            case ID_POPUP_DRINKS:   
                hMenu = GetMenu(hWnd);
                CheckMenuItem(hMenu, ID_XMENU_DRINKS, MF_BYCOMMAND | MF_CHECKED);
                CheckMenuItem(hMenu, ID_XMENU_FRUITS, MF_BYCOMMAND | MF_UNCHECKED);
                EnableMenuItem(hMenu, ID_ITEMS_TEA, MF_BYCOMMAND | MF_ENABLED);
                EnableMenuItem(hMenu, ID_ITEMS_APPLE, MF_BYCOMMAND | MF_DISABLED);
                break;
            case ID_POPUP_FRUITS:
                hMenu = GetMenu(hWnd);
                CheckMenuItem(hMenu, ID_XMENU_FRUITS, MF_BYCOMMAND | MF_CHECKED);
                CheckMenuItem(hMenu, ID_XMENU_DRINKS, MF_BYCOMMAND | MF_UNCHECKED);
                EnableMenuItem(hMenu, ID_ITEMS_APPLE, MF_BYCOMMAND | MF_ENABLED);
                EnableMenuItem(hMenu, ID_ITEMS_TEA, MF_BYCOMMAND | MF_DISABLED);
                break;

            case ID_POPUP_END:
                if (LOWORD(wParam) == ID_POPUP_END)
                {
                    int iMsgBox = MessageBox(hWnd,
                        L"   Good-Bye!",
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
            int iMsgBox = MessageBox(hDlg,
                L"Do you really want to exit?\nPlease, confirm",
                L"About exit...\nThe second row?",
                MB_ICONHAND | MB_YESNO);
            if (iMsgBox == IDYES)
                EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

double TryCatch(HWND hDlg, int definesmth) {
    std::string::size_type sz;
    double d_smth;
    try {
        if (!GetDlgItemText(hDlg, definesmth, szText, MAX_LOADSTRING))
            *szText = 0;
        d_smth = std::stod(szText, &sz);
        return d_smth;
    }
    catch (std::exception& e) {
        MessageBox(hDlg, L"Error to extract double value or missing value!", L"Error!",
            MB_ICONERROR | MB_OK);
        d_smth = 0.0;
        return d_smth;
    }
}

INT_PTR CALLBACK Calculation(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    double i_M, i_N, i_P, i_Res, i_A, i_B, i_C, D;
    BOOL bState;
    HWND smth;
    std::string::size_type sz;

    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDC_CHECK_M:
            bState = IsDlgButtonChecked(hDlg, IDC_CHECK_M);
            smth = GetDlgItem(hDlg, IDC_EDIT_M);
            EnableWindow(smth, bState & TRUE ? TRUE : FALSE);
            return (INT_PTR)TRUE;

        case IDC_CHECK_N:
            bState = IsDlgButtonChecked(hDlg, IDC_CHECK_N);
            smth = GetDlgItem(hDlg, IDC_EDIT_N);
            EnableWindow(smth, bState & TRUE ? TRUE : FALSE);
            return (INT_PTR)TRUE;

        case IDC_CHECK_P:
            bState = IsDlgButtonChecked(hDlg, IDC_CHECK_P);
            smth = GetDlgItem(hDlg, IDC_EDIT_P);
            EnableWindow(smth, bState & TRUE ? TRUE : FALSE);
            return (INT_PTR)TRUE;

        case IDC_BUTTON_CALC:
            i_M = TryCatch(hDlg, IDC_EDIT_M);
            i_N = TryCatch(hDlg, IDC_EDIT_N);
            i_P = TryCatch(hDlg, IDC_EDIT_P);
           
            i_Res = i_M + i_N - i_P;           

            StringCbPrintf(szText, ARRAYSIZE(szText), L"%.2f", i_Res);
            SetDlgItemText(hDlg, IDC_EDIT_RESULT, szText);

            return (INT_PTR)TRUE;


        case IDC_BUTTON_RESULT:
            i_A = TryCatch(hDlg, IDC_EDIT_A);
            i_B = TryCatch(hDlg, IDC_EDIT_B);
            i_C = TryCatch(hDlg, IDC_EDIT_C);


            D = ((i_B * i_B) - (4 * i_A * i_C));

            if (D < 0) { 
                MessageBox(hDlg, L"Nqma Koren!", L"Error!",
                    MB_OK);
            }
            else if (D == 0) {                                
                i_Res = ((-i_B) / (2 * i_A));
                StringCbPrintf(szText, ARRAYSIZE(szText), L"%.2f", i_Res);
                SetDlgItemText(hDlg, IDC_EDIT8, szText);
            } 
            else {
                double X1, X2;
                X1 = (-i_B + sqrt(D)) / (2 * i_A);
                X2 = (-i_B - sqrt(D)) / (2 * i_A); 
                StringCbPrintf(szText, ARRAYSIZE(szText), L"%.2f | %.2f ", X1, X2);
                SetDlgItemText(hDlg, IDC_EDIT8, szText);
            }


            return (INT_PTR)TRUE;

        case IDOK:
        case IDCANCEL:                 
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
    }
    return (INT_PTR)FALSE;
}
