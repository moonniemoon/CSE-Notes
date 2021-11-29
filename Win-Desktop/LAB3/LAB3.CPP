// LabDialogBox.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "strsafe.h"
#include <string>
#include "LabDialogBox.h"

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
INT_PTR CALLBACK	MyFirstDialog(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_LABDIALOGBOX, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LABDIALOGBOX));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LABDIALOGBOX));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LABDIALOGBOX);
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
			case ID_FILE_MYFIRSTDIALOG:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DLG_MYFIRST), hWnd, MyFirstDialog);
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

// Message handler for IDD_DLG_MYFIRST box.
INT_PTR CALLBACK MyFirstDialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
    UINT PLUS, MINUS, MUL, DIVISION, MUL_7, DIV_7;
    double d_A, d_B, d_Res;
    BOOL bSigned, bSuccess;
    double dVal;
    std::string::size_type sz;

	switch (message)
	{
    case WM_INITDIALOG: 
        CheckDlgButton(hDlg, IDC_RADIO2, BST_CHECKED);
        return (INT_PTR)TRUE;
        SetFocus(GetDlgItem(hDlg, IDC_BUTTON4));
        return (INT_PTR)FALSE;

	case WM_COMMAND:
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
        case WM_INITDIALOG:
            SetFocus(GetDlgItem(hDlg, IDC_A));
            return (INT_PTR)TRUE;

        case IDC_CALCULATE:
            PLUS = IsDlgButtonChecked(hDlg, IDC_PLUS);
            MINUS = IsDlgButtonChecked(hDlg, IDC_MINUS);
            MUL = IsDlgButtonChecked(hDlg, IDC_MUL);
            DIVISION = IsDlgButtonChecked(hDlg, IDC_DIVISION);

            MUL_7 = IsDlgButtonChecked(hDlg, IDC_TIMES_7);
            PLUS = IsDlgButtonChecked(hDlg, IDC_DIV_7);

            try {
                if (!GetDlgItemText(hDlg, IDC_A, szText, MAX_LOADSTRING))
                    *szText = 0;
                d_A = std::stod(szText, &sz);
            }
            catch (std::exception& e) {
                MessageBox(hDlg, L"Error to extract double value", L"Error!", 
                    MB_ICONERROR | MB_OK);
                d_A = 0.0;
            }
            try {
                if (!GetDlgItemText(hDlg, IDC_B, szText, MAX_LOADSTRING))
                    *szText = 0;
                d_B = std::stod(szText, &sz);
            }
            catch (std::exception& e) {
                MessageBox(hDlg, L"Error to extract double value", L"Error!",
                    MB_ICONERROR | MB_OK);
                d_B = 0.0;
            }
            

            if (PLUS == BST_CHECKED) {
                d_Res = d_A + d_B;
            }
            else if (MINUS == BST_CHECKED) {
                d_Res = d_A - d_B;
            }
            else if (MINUS == BST_CHECKED) {
                d_Res = d_A * d_B;
            }
            else {
                d_Res = d_A / d_B;
            }

            if (IsDlgButtonChecked(hDlg, IDC_TIMES_7)) {
                d_Res = d_Res * 7;
            }
            else {
                d_Res = d_Res / 7;
            }

            StringCbPrintf(szText, ARRAYSIZE(szText), L"%f", d_Res);
            SetDlgItemText(hDlg, IDC_RESULT, szText);
            return (INT_PTR)TRUE;
            
            return (INT_PTR)TRUE;



        /*case IDC_CHECK_RO:
            status = IsDlgButtonChecked(hDlg, IDC_CHECK_RO);
            MessageBox(hDlg, status == BST_CHECKED ? L"\"Checked" : L"\"Unchecked",
                L"Info", MB_OK);
            return (INT_PTR)TRUE;

        case IDC_RADIO_ADULT:

        case IDC_RADIO_CHILD:
            SetDlgItemInt(hDlg, IDC_EDIT_EGN, IsDlgButtonChecked(hDlg, IDC_RADIO_ADULT),
                FALSE);
            return (INT_PTR)TRUE;

        case IDC_CHECK_HIDDEN:
            status = IsDlgButtonChecked(hDlg, IDC_CHECK_HIDDEN);
            StringCbPrintf(szText, ARRAYSIZE(szText), L"Checkbox Hidden is %s",
                status == BST_CHECKED ? L"\"Checked\"" : L"\"Unchecked\"");
            SetDlgItemText(hDlg, IDC_EDIT_EGN, szText);
            return (INT_PTR)TRUE;*/


        case IDCANCEL:                          // X button
		case IDC_BUTTON3:                       // Krai button
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
	}
	return (INT_PTR)FALSE;
}
