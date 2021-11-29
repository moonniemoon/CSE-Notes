// LAB_07.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "strsafe.h"
#include <string>
#include "LAB_07.h"

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
INT_PTR CALLBACK	DegreeConverter(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	LengthConverter(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_LAB07, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB07));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB07));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LAB07);
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
    HMENU hMenu, hSubMenu;
    BOOL bRes;
    UINT uRes;

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            // Dialog
            case ID_FILE_DEGREECONVERTER:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DEGREE_CONVERTER), hWnd, DegreeConverter);
                break;
            case ID_FILE_LENGTHCONVERTER:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_LENGTH_CALCULATOR), hWnd, LengthConverter);
                break;

            // Check me - Disable me ???
            case ID_TOOLS_CHECKME:
                hMenu = GetMenu(hWnd);
                uRes = GetMenuState(hMenu, ID_TOOLS_CHECKME, MF_BYCOMMAND);
                bRes = ModifyMenu(hMenu, ID_TOOLS_CHECKME, MF_BYCOMMAND | uRes & MF_CHECKED ? MF_UNCHECKED : MF_CHECKED,
                    ID_TOOLS_CHECKME, uRes & MF_CHECKED ? L"Check Me" : L"Uncheck Me");
                              
               /* dwRes = CheckMenuItem(hMenu, ID_TOOLS_CHECKME,
                    uRes & MF_CHECKED ? MF_UNCHECKED : MF_CHECKED); */ 
                
                break;

            case ID_TOOLS_DISABLEME:
                hMenu = GetMenu(hWnd);
                uRes = GetMenuState(hMenu, ID_TOOLS_CHECKME, MF_BYCOMMAND);
                bRes = EnableMenuItem(hMenu, ID_TOOLS_CHECKME, MF_BYCOMMAND | uRes & MF_DISABLED ? MF_ENABLED : MF_DISABLED);
                break;

            // Popup
            case ID_POPUP_DEGREECONVERTER:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_DEGREE_CONVERTER), hWnd, DegreeConverter);
                break;
            case ID_POPUP_LENGTHCONVERTER:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_LENGTH_CALCULATOR), hWnd, LengthConverter);
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


// Message handler for IDD_DEGREE_CONVERTER box.
INT_PTR CALLBACK DegreeConverter(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
  
    UNREFERENCED_PARAMETER(lParam);
    UINT A_cel, A_fah, A_kel, B_cel, B_fah, B_kel;
    double d_A, d_Res;
    std::string::size_type sz;

    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case WM_INITDIALOG:
            SetFocus(GetDlgItem(hDlg, IDC_ENTER_A));
            return (INT_PTR)TRUE;

        case IDC_CALCULATE:
            A_cel = IsDlgButtonChecked(hDlg, IDC_A_CELSIUS);
            A_fah = IsDlgButtonChecked(hDlg, IDC_A_FAHRENHEIT);
            A_kel = IsDlgButtonChecked(hDlg, IDC_A_KELVIN);
            B_cel = IsDlgButtonChecked(hDlg, IDC_B_CELSIUS);
            B_fah = IsDlgButtonChecked(hDlg, IDC_B_FAHRENHEIT);
            B_kel = IsDlgButtonChecked(hDlg, IDC_B_KELVIN);

            try {
                if (!GetDlgItemText(hDlg, IDC_ENTER_A, szText, MAX_LOADSTRING)) 
                    *szText = 0;
                d_A = std::stod(szText, &sz);
            }
            catch (std::exception& e) {
                MessageBox(hDlg, L"Error to extract double value!", L"Error!",
                    MB_ICONERROR | MB_OK);
                d_A = 0.0;
            }

            // TODO : Button IDC_CALCULATE only works when both groups are checked
            // A_BOX  and B_BOX == BST_CHECKED

            if (A_cel == BST_CHECKED && B_fah == BST_CHECKED) {
                d_Res = 1.8 * d_A + 32;
            }
            else if (A_cel == BST_CHECKED && B_kel == BST_CHECKED) {
                d_Res = d_A + 273.15;
            }
            else if ((A_fah == BST_CHECKED) && B_cel == BST_CHECKED) {
                d_Res = (d_A - 32) * (5.0 / 9); 
            }
            else if ((A_fah == BST_CHECKED) && B_kel == BST_CHECKED) {
                d_Res = (d_A - 32) * (5.0 / 9) + 273.15;
            }
            else if ((A_kel == BST_CHECKED) && B_cel == BST_CHECKED) {
                d_Res = d_A - 273.15;
            }
            else if ((A_kel == BST_CHECKED) && B_fah == BST_CHECKED) {
                d_Res = (d_A - 273.15) * (9.0 / 5) + 32;
            }
            else {
                MessageBox(hDlg, L"Error, you have checked the same degrees!", L"Error!",
                    MB_ICONERROR | MB_OK);
                d_Res = 0.0;
                // un-check 2nd one ??
                CheckDlgButton(hDlg, IDC_B_CELSIUS, BST_UNCHECKED);  // .... datz stupid .. i'm sleepy
                CheckDlgButton(hDlg, IDC_B_FAHRENHEIT, BST_UNCHECKED);
                CheckDlgButton(hDlg, IDC_B_KELVIN, BST_UNCHECKED);
            }

            StringCbPrintf(szText, ARRAYSIZE(szText), L"%.2f", d_Res);
            SetDlgItemText(hDlg, IDC_RESULT_B, szText);
            return (INT_PTR)TRUE;

            return (INT_PTR)TRUE;

        case IDOK:
        case IDCANCEL:
        case ID_CNCL_DEGREE: 
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
    }
    return (INT_PTR)FALSE;
}



// Message handler for IDD_LENGTH_CONVERTER box.
INT_PTR CALLBACK LengthConverter(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    UINT X_km, X_mi, Y_km, Y_mi;
    double d_X, d_Res;
    std::string::size_type sz;

    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case WM_INITDIALOG:
            SetFocus(GetDlgItem(hDlg, IDC_ENTER_X));
            return (INT_PTR)TRUE;

        case IDC_CALCULATE_XY:
            X_km = IsDlgButtonChecked(hDlg, IDC_X_KM);
            X_mi = IsDlgButtonChecked(hDlg, IDC_X_MI);
            Y_km = IsDlgButtonChecked(hDlg, IDC_Y_KM);
            Y_mi = IsDlgButtonChecked(hDlg, IDC_Y_MI);

            try {
                if (!GetDlgItemText(hDlg, IDC_ENTER_X, szText, MAX_LOADSTRING))
                    *szText = 0;
                d_X = std::stod(szText, &sz);
            }
            catch (std::exception& e) {
                MessageBox(hDlg, L"Error to extract double value!", L"Error!",
                    MB_ICONERROR | MB_OK);
                d_X = 0.0;
            }

            if (X_km == BST_CHECKED && Y_mi == BST_CHECKED) {
                d_Res = d_X / 1.609;
            }
            else if (X_mi == BST_CHECKED && Y_km == BST_CHECKED) {
                d_Res = d_X * 1.609;
            }
            else {
                MessageBox(hDlg, L"Error, you have checked the same lengths!", L"Error!",
                    MB_ICONERROR | MB_OK);
                d_Res = 0.0;
                // un-check 2nd one ??
                CheckDlgButton(hDlg, IDC_Y_KM, BST_UNCHECKED);  // .... datz stupid .. i'm sleepy
                CheckDlgButton(hDlg, IDC_Y_MI, BST_UNCHECKED);
            }

            StringCbPrintf(szText, ARRAYSIZE(szText), L"%.3f", d_Res);
            SetDlgItemText(hDlg, IDC_RESULT_Y, szText);
            return (INT_PTR)TRUE;

        return (INT_PTR)TRUE;        case IDOK2:
        case IDCANCEL:
        case ID_CNCL_LENGTH:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
    }
    return (INT_PTR)FALSE;
    
}
