#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#include "ConsoleCalculator.h"
#include <iostream>
#include <windows.h>
#include "MainWindow.h"

//using namespace Console;

//int main() 
//{
	/*
		Console Calculator
		-- Start --
	*/
	
	//ConsoleCalculator cons;

	//cons.SelectOperation();

	/*
		Console Calculator
		-- End --
	*/


	//return 0;
//}


/*
	Graphical Calculator
	-- Start --
*/


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) 
{
	MainWindow main;

	if (!main.Create(L"Calculator", WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU))
	{
		return 0;
	}

	ShowWindow(main.Window(), nCmdShow);

	MSG msg = {};

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;


}
























//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//void OnSize(HWND hwnd, UINT flag, int width, int height);

/*
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR cCmdLine, int nCmdShow)
{	

	const wchar_t CLASS_NAME[] = L"Sample Window Class";

	WNDCLASS wc = {};

	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;

	RegisterClass(&wc);

	// Create the window

	HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"Learn to program windows", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);

	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_SIZE:
		{
			int width = LOWORD(lParam);
			int height = HIWORD(lParam);

			OnSize(hwnd, (UINT)wParam, width, height);
			
			return 0;
		}
		break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);


			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

			EndPaint(hwnd, &ps);
			
			return 0;
		}
		break;
		case WM_CLOSE:
		{
			if (MessageBox(hwnd, L"Really Quit?", L"My Application", MB_OKCANCEL) == IDOK)
			{
				DestroyWindow(hwnd);
			}
			
			return 0;
		}
		break;
		case WM_DESTROY:
		{
			PostQuitMessage(0);

			return 0;
		}
		default:
		{
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}

	}
}
*/
/*
void OnSize(HWND hwnd, UINT flag, int width, int height)
{

	
}
*/

/*
	Graphical Calculator
	-- End --
*/
