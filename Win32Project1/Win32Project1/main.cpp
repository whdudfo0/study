#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
TCHAR* lpszClass = L"WINDOW";

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, 500, 200, 1000, 800, NULL, (HMENU)NULL, hInstance, NULL);

	if (hWnd == 0)
	{
		return false;
	}

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	HBRUSH MyBrush, OldBrush;

	static short nGraph = 0;
	static short nColor = 0;
	
	switch (iMessage)
	{
	case WM_CREATE:
		CreateWindow(L"button", L"도형", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 5, 220, 100, 100, hWnd, (HMENU)0, g_hInst, NULL);
		CreateWindow(L"button", L"색상", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, 140, 220, 100, 150, hWnd, (HMENU)1, g_hInst, NULL);
		CreateWindow(L"button", L"사각형", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 20, 240, 80, 25, hWnd, (HMENU)401, g_hInst, NULL);
		CreateWindow(L"button", L"타원", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 20, 280, 80, 25, hWnd, (HMENU)402, g_hInst, NULL);
		CreateWindow(L"button", L"빨강", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON | WS_GROUP, 150, 240, 80, 25, hWnd, (HMENU)403, g_hInst, NULL);
		CreateWindow(L"button", L"초록", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 280, 80, 25, hWnd, (HMENU)404, g_hInst, NULL);
		CreateWindow(L"button", L"파랑", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, 150, 320, 80, 25, hWnd, (HMENU)405, g_hInst, NULL);

		CheckRadioButton(hWnd, 401, 402, 401);
		CheckRadioButton(hWnd, 403, 405, 403);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 401:
			nGraph = 0;
			break;
		case 402:
			nGraph = 1;
			break;
		case 403:
			nColor = 0;
			break;
		case 404:
			nColor = 1;
			break;
		case 405:
			nColor = 2;
			break;
		}
		InvalidateRect(hWnd, NULL, true);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		switch (nColor)
		{
		case 0:
			MyBrush = CreateSolidBrush(RGB(255, 0, 0));
			break;
		case 1:
			MyBrush = CreateSolidBrush(RGB(0, 255, 0));
			break;
		case 2:
			MyBrush = CreateSolidBrush(RGB(0, 0, 255));
			break;
		}
		OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);

		switch (nGraph)
		{
		case 0:
			Rectangle(hdc, 10, 400, 200, 500);
			break;
		case 1:
			Ellipse(hdc, 10, 400, 200, 500);
			break;
		}

		SelectObject(hdc, OldBrush);
		DeleteObject(MyBrush);

		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}