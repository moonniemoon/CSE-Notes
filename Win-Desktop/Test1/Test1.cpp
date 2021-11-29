// FN19621447.cpp : Defines the entry point for the application.
// Selin Tahsin Kayar, FN : 19621447, 1A

#include "framework.h"
#include "strsafe.h"
#include <string>
#include "FN19621447.h"

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
INT_PTR CALLBACK	Test1(HWND, UINT, WPARAM, LPARAM);

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
    HMENU hMenu, hSubMenu;
    BOOL bRes;
    UINT uRes;
    MENUITEMINFO miinf;

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
                // TEST1 and POPUP
            case ID_SHOWDIALOG:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_TEST1_DIALOG), hWnd, Test1);
                break;

                // TEST1
            case ID_TEST1_ERROR_MESSAGE:
                MessageBox(hWnd, L"Error Message!", L"Error", MB_ICONEXCLAMATION | MB_OK);
                break;
            case ID_TEST1_CHECK:
                hMenu = GetMenu(hWnd);
                uRes = GetMenuState(hMenu, ID_TEST1_CHECK, MF_BYCOMMAND);
                bRes = ModifyMenu(hMenu, ID_TEST1_CHECK, MF_BYCOMMAND | (uRes & MF_CHECKED ? MF_UNCHECKED : MF_CHECKED),
                    ID_TEST1_CHECK, uRes & MF_CHECKED ? L"Check Me" : L"Uncheck Me");
                break;
            case ID_TEST1_REMOVEGARBAGE:
                hMenu = GetMenu(hWnd);
                bRes = DeleteMenu(hMenu, ID_TEST1_GARBAGE, MF_BYCOMMAND);
                break;
            case ID_TEST1_GARBAGE:
                MessageBox(hWnd, L"Garbage's Message!", L"Info", MB_ICONEXCLAMATION | MB_OK);
                break;

                // POPUP
            case ID_POPUP_WARNINGMESSAGE:
                hMenu = GetMenu(hWnd);
                if (LOWORD(wParam) == ID_POPUP_WARNINGMESSAGE)
                {
                    int iMsgBox = MessageBox(hWnd,
                        L"  You just pressed 'Warning Message'",
                        L"Warning!",
                        MB_ICONERROR | MB_YESNO);
                    if (iMsgBox == IDYES) {
                        EndDialog(hWnd, LOWORD(wParam));
                    }
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

INT_PTR CALLBACK Test1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
    UNREFERENCED_PARAMETER(lParam);
    int i_A, i_B, i_Calc;
    double d_C, d_D, d_E, d_Result;
    BOOL bSigned1, bSigned2, bSuccess1, bSuccess2;

    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
        case IDC_BUTTON_INTEGER: // with int numbers

            //i_A = TryCatch_stoi(hDlg, IDC_EDIT_A);  // Function with try-catch with stoi, starts at row 247
            //i_B = TryCatch_stoi(hDlg, IDC_EDIT_B);  // i know that i can use GetDlgItemInt too, but i like try-catch more
            

            // Reshih da polzvam GetDlgItemInt, shtot moje bi tova iskate da vidite?, a try-catch go polzvah dolo 
            bSigned1 = bSigned2 = FALSE;
            i_A = GetDlgItemInt(hDlg, IDC_EDIT_A, &bSuccess1, bSigned1);
            i_B = GetDlgItemInt(hDlg, IDC_EDIT_B, &bSuccess2, bSigned2);
             
            if (!bSuccess1 || !bSuccess2)            
            {
                MessageBox(hDlg, L"Error to extract int value!\nDouble, String values are forbidden.", L"Error!",
                    MB_ICONERROR | MB_OK);
            }
            else {
                i_A = GetDlgItemInt(hDlg, IDC_EDIT_A, &bSuccess1, TRUE);
                i_B = GetDlgItemInt(hDlg, IDC_EDIT_B, &bSuccess1, TRUE);

                if (i_A < -1001 || i_A > 1001 || i_B < -1001 || i_B > 1001) {
                    MessageBox(hDlg, L"Please enter numbers between -1001 and 1000!", L"Error!",
                        MB_ICONERROR | MB_OK);
                    break;
                }
                else {
                    i_Calc = i_A + i_B;
                    StringCbPrintf(szText, ARRAYSIZE(szText), L"%d", i_Calc);
                    SetDlgItemText(hDlg, IDC_EDIT_APLUSB, szText);
                }
            }

            return (INT_PTR)TRUE;


        case IDC_BUTTON_REAL:  // With double numbers
            d_C = TryCatch_stod(hDlg, IDC_EDIT_C); // Function for try-catch, starts at 263
            d_D = TryCatch_stod(hDlg, IDC_EDIT_D);
            d_E = TryCatch_stod(hDlg, IDC_EDIT_E);

            if (d_C < -1001 || d_C > 1001 || d_D < -1001 || d_D > 1001 || d_E < -1001 || d_E > 1001) {
                MessageBox(hDlg, L"Please enter numbers between -1001 and 1000!", L"Error!",
                    MB_ICONERROR | MB_OK);
            }
            else {

                if (IsDlgButtonChecked(hDlg, IDC_RADIO_MINUS) == BST_CHECKED) {
                    d_Result = (d_C - d_D) / (d_E);                    // didn't understand if it's (C + D) / E
                                                                       // or C + (D / E) but it doesn't matter, can be changed easily
                }
                else if (IsDlgButtonChecked(hDlg, IDC_RADIO_PLUS) == BST_CHECKED) {
                    d_Result = (d_C + d_D) / (d_E);
                }
                else {
                    MessageBox(hDlg, L"Please check a radio button!", L"Error!",
                        MB_ICONERROR | MB_OK);
                    break;
                }


                if (d_E == 0) {  // 0/number = 0;  number/0 = undefined;
                    MessageBox(hDlg, L"A number cannot be divided by 0!", L"Error!",
                        MB_ICONERROR | MB_OK);
                    break;
                }

                StringCbPrintf(szText, ARRAYSIZE(szText), L"%.2f", d_Result);
                SetDlgItemText(hDlg, IDC_EDIT_Result, szText);
            }

            return (INT_PTR)TRUE;

        case IDOK:
        case IDCANCEL:   // X 
        case ID_CANCEL:  // Cancel button
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;

        }

    }
    return (INT_PTR)FALSE;
}
