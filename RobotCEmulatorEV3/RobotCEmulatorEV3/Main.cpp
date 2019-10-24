#include "stdafx.h"
#include "robotC_EV3_display.h"

using namespace Gdiplus;
using namespace RobotC::Ev3;
using namespace RobotC::Ev3::Impl;


VOID OnPaint(HDC hdc)
{
  Graphics graphics(hdc);
  Pen      pen(Color(255, 0, 0, 255));
  graphics.DrawLine(&pen, 0, 0, 200, 100);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
  HWND                hWnd;
  MSG                 msg;
  WNDCLASS            wndClass;
  GdiplusStartupInput gdiplusStartupInput;
  ULONG_PTR           gdiplusToken;

  // Initialize GDI+.
  GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

  wndClass.style = CS_HREDRAW | CS_VREDRAW;
  wndClass.lpfnWndProc = WndProc;
  wndClass.cbClsExtra = 0;
  wndClass.cbWndExtra = 0;
  wndClass.hInstance = hInstance;
  wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
  wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  wndClass.lpszMenuName = nullptr;
  wndClass.lpszClassName = TEXT("RobotCEmulator");

  RegisterClass(&wndClass);

  hWnd = CreateWindowEx(
    WS_EX_CLIENTEDGE,
    TEXT("RobotCEmulator"),      // window class name
    TEXT("RobotC Emulator"),     // window caption
    WS_OVERLAPPED | WS_SYSMENU,  // window style   // WS_OVERLAPPEDWINDOW - to resizable
    CW_USEDEFAULT,               // initial x position
    CW_USEDEFAULT,               // initial y position
    ScreenWidth * ScreenRatio,                 // initial x size
    ScreenHeight * ScreenRatio,                // initial y size
    nullptr,                     // parent window handle
    nullptr,                     // window menu handle
    hInstance,                   // program instance handle
    nullptr);                    // creation parameters

  ShowWindow(hWnd, iCmdShow);
  UpdateWindow(hWnd);

  //PAINTSTRUCT  ps;
  //HDC hdc = BeginPaint(hWnd, &ps);
  //EndPaint(hWnd, &ps);

  while (GetMessage(&msg, nullptr, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  GdiplusShutdown(gdiplusToken);
  return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
  WPARAM wParam, LPARAM lParam)
{
  HDC          hdc;
  PAINTSTRUCT  ps;

  switch (message)
  {
  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);
    OnPaint(hdc);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
} // WndProc