#include "MainWindow.h"
#include <windows.h>
#include <windowsx.h>
#include <wchar.h>
#include <dwmapi.h>
#include <Uxtheme.h>

#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "Uxtheme.lib")

#ifndef UNICODE
#def UNICODE
#endif

#define BTNSTYLE WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON

#define ID_TEXTFIELD 1001
#define ID_BUTTONZERO 10000
#define ID_BUTTONDOT 100001
#define ID_BUTTONPLUS 100002
#define ID_BUTTONMIN 100003
#define ID_BUTTONMULT 100004
#define ID_BUTTONDIVS 100005
#define ID_BUTTONCLEAR 100006
#define ID_BUTTONAC 100007
#define ID_BUTTONPARENLEFT 100008
#define ID_BUTTONPARENRIGHT 100009
#define ID_BUTTONEQUAL 1000010
#define ID_BUTTONONE 10001
#define ID_BUTTONTWO 10002
#define ID_BUTTONTHREE 10003
#define ID_BUTTONFOUR 10004
#define ID_BUTTONFIVE 10005
#define ID_BUTTONSIX 10006
#define ID_BUTTONSEVEN 10007
#define ID_BUTTONEIGHT 10008
#define ID_BUTTONNINE 10009

#define HORIZONTAL_OFFSET 3
#define VERTICAL_OFFSET 3
#define HORIZONTAL_MARGIN 5
#define VERTICAL_MARGIN 5

#define SIZE_X 53
#define SIZE_Y 40

#define LEFTEXTENDWIDTH 8
#define RIGHTEXTENDWIDTH 8
#define TOPEXTENDWIDTH 27
#define BOTTOMEXTENDWIDTH 20

#define TMT_CAPTIONFONT 0x0321

MainWindow::MainWindow() 
{
	x = CW_USEDEFAULT;
	y = CW_USEDEFAULT;

	ScreenResolution(width, height);

	
	height = (int)((width - height) - (height * .35));
	width = (int)(height * .75);

	//wchar_t str[50] = { 0 };

	//swprintf(str, _countof(str), L"height %i, - width %i", height, width);

	//OutputDebugStringW(str);

	// width and height by default
	height = 329;
	width = 246;


}

PCWSTR MainWindow::ClassName() const 
{
	return L"Calculator";
}

LRESULT MainWindow::HandleMessage(UINT message, WPARAM wParam, LPARAM lParam) 
{
	bool fCallDWP = true;
	BOOL fDwmEnabled = FALSE;
	
	LRESULT lRet = 0;
	HRESULT hr = S_OK;

	hr = DwmIsCompositionEnabled(&fDwmEnabled);

	if (SUCCEEDED(hr)) 
	{

		fCallDWP = !DwmDefWindowProc(m_hwnd, message, wParam, lParam, &lRet);

		if (message == WM_CREATE) 
		{
			RECT rcClient;
			GetWindowRect(m_hwnd, &rcClient);

			SetWindowPos(m_hwnd, NULL, rcClient.left, rcClient.top, RECTWIDTH(rcClient), RECTHEIGHT(rcClient), SWP_FRAMECHANGED);

			fCallDWP = true;
			lRet = 0;
		}

		if (message == WM_ACTIVATE)
		{
			MARGINS margins;

			margins.cxLeftWidth = LEFTEXTENDWIDTH;
			margins.cxRightWidth = RIGHTEXTENDWIDTH;
			margins.cyTopHeight = TOPEXTENDWIDTH;
			margins.cyBottomHeight = BOTTOMEXTENDWIDTH;

			hr = DwmExtendFrameIntoClientArea(m_hwnd, &margins);

			fCallDWP = true;
			lRet = 0;
		}
		
		if (message == WM_PAINT)
		{
			HDC hdc;
			PAINTSTRUCT ps;
			
			hdc = BeginPaint(m_hwnd, &ps);
		
			//FillRect(hdc, &ps.rcPaint, (HBRUSH)(CreateSolidBrush(RGB(100, 130, 255))));

			PaintCustomCaption(m_hwnd, hdc, ps);
			
			EndPaint(m_hwnd, &ps);

			fCallDWP = false;
			lRet = 0;
		}
		// Handle the non-client size message.
		if ((message == WM_NCCALCSIZE) && (wParam == TRUE))
		{
			// Calculate new NCCALCSIZE_PARAMS based on custom NCA inset.
			NCCALCSIZE_PARAMS* pncsp = reinterpret_cast<NCCALCSIZE_PARAMS*>(lParam);

			pncsp->rgrc[0].left = pncsp->rgrc[0].left + 0;
			pncsp->rgrc[0].top = pncsp->rgrc[0].top + 0;
			pncsp->rgrc[0].right = pncsp->rgrc[0].right - 0;
			pncsp->rgrc[0].bottom = pncsp->rgrc[0].bottom - 0;

			lRet = 0;

			// No need to pass the message on to the DefWindowProc.
			fCallDWP = false;
		}

		// Handle hit testing in the NCA if not handled by DwmDefWindowProc.
		if ((message == WM_NCHITTEST) && (lRet == 0))
		{
			lRet = HitTestNCA(m_hwnd, wParam, lParam);

			if (lRet != HTNOWHERE)
			{
				fCallDWP = false;
			}
		}

	}

	if (!fCallDWP)
	{
		return lRet;
	}


	switch (message)
	{

		case WM_CREATE: {

			RECT rcClient;
			GetWindowRect(m_hwnd, &rcClient);

			// Inform the application of the frame change.
			SetWindowPos(m_hwnd,
				NULL,
				rcClient.left, rcClient.top,
				RECTWIDTH(rcClient), RECTHEIGHT(rcClient),
				SWP_FRAMECHANGED);

			/*/
			hTextField = CreateWindowEx(0,
				L"EDIT",  // Predefined class; Unicode assumed
				NULL,      // Button text
				WS_VISIBLE | WS_CHILD,  // Styles
				10,         // x position
				10,         // y position
				100,        // Button width
				100,        // Button height
				m_hwnd,     // Parent window
				NULL,       // No menu.
				(HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE),
				NULL);      // Pointer not needed./**/


			HWND buttonZero = CreateWindow(L"BUTTON", L"0", BTNSTYLE,
				BtnPosition(0, 0, LEFTEXTENDWIDTH, HORIZONTAL_MARGIN), height - BtnPosition(SIZE_Y, 1, BOTTOMEXTENDWIDTH, VERTICAL_MARGIN),
				SIZE_X + SIZE_X + 2, SIZE_Y,
				m_hwnd,
				(HMENU)ID_BUTTONZERO,
				(HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE),
				NULL);

			HWND buttonDot = CreateWindow(L"Button", L".", BTNSTYLE,
				BtnPosition(SIZE_X, 2, LEFTEXTENDWIDTH, HORIZONTAL_MARGIN), height - BtnPosition(SIZE_Y, 1, BOTTOMEXTENDWIDTH, VERTICAL_MARGIN),
				SIZE_X, SIZE_Y,
				m_hwnd,
				(HMENU)ID_BUTTONDOT,
				(HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE),
				NULL);

			HWND btnOne = CreateWindow(L"Button", L"1", BTNSTYLE,
				BtnPosition(0, 0, LEFTEXTENDWIDTH, HORIZONTAL_MARGIN), height - BtnPosition(SIZE_Y, 2, BOTTOMEXTENDWIDTH, VERTICAL_MARGIN),
				SIZE_X, SIZE_Y,
				m_hwnd,
				(HMENU)ID_BUTTONONE,
				(HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE),
				NULL);

			HWND btnTwo = CreateWindow(L"Button", L"2", BTNSTYLE,
				BtnPosition(SIZE_X, 1, LEFTEXTENDWIDTH, HORIZONTAL_MARGIN), height - BtnPosition(SIZE_Y, 2, BOTTOMEXTENDWIDTH, VERTICAL_MARGIN),
				SIZE_X, SIZE_Y,
				m_hwnd,
				(HMENU)ID_BUTTONTWO,
				(HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE),
				NULL);

			HWND btnThree = CreateWindow(L"Button", L"3", BTNSTYLE,
				BtnPosition(SIZE_X, 2, LEFTEXTENDWIDTH, HORIZONTAL_MARGIN), height - BtnPosition(SIZE_Y, 2, BOTTOMEXTENDWIDTH, VERTICAL_MARGIN),
				SIZE_X, SIZE_Y,
				m_hwnd,
				(HMENU)ID_BUTTONTHREE,
				(HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE),
				NULL);

			HWND btnFour = CreateWindow(L"Button", L"4", BTNSTYLE,
				BtnPosition(0, 0, LEFTEXTENDWIDTH, HORIZONTAL_MARGIN), height - BtnPosition(SIZE_Y, 3, BOTTOMEXTENDWIDTH, VERTICAL_MARGIN),
				SIZE_X, SIZE_Y,
				m_hwnd,
				(HMENU)ID_BUTTONFOUR,
				(HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE),
				NULL);

			HWND btnFive = CreateWindow(L"Button", L"5", BTNSTYLE,
				BtnPosition(SIZE_X, 1, LEFTEXTENDWIDTH, HORIZONTAL_MARGIN), height - BtnPosition(SIZE_Y, 3, BOTTOMEXTENDWIDTH, VERTICAL_MARGIN),
				SIZE_X, SIZE_Y,
				m_hwnd,
				(HMENU)ID_BUTTONFIVE,
				(HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE),
				NULL);

			HWND btnSix = CreateWindow(L"Button", L"6", BTNSTYLE,
				BtnPosition(SIZE_X, 2, LEFTEXTENDWIDTH, HORIZONTAL_MARGIN), height - BtnPosition(SIZE_Y, 3, BOTTOMEXTENDWIDTH, VERTICAL_MARGIN),
				SIZE_X, SIZE_Y,
				m_hwnd,
				(HMENU)ID_BUTTONSIX,
				(HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE),
				NULL);

			HWND btnSeven = CreateWindow(L"Button", L"7", BTNSTYLE,
				BtnPosition(0, 0, LEFTEXTENDWIDTH, HORIZONTAL_MARGIN), height - BtnPosition(SIZE_Y, 4, BOTTOMEXTENDWIDTH, VERTICAL_MARGIN),
				SIZE_X, SIZE_Y,
				m_hwnd,
				(HMENU)ID_BUTTONFOUR,
				(HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE),
				NULL);

			HWND btnEight = CreateWindow(L"Button", L"8", BTNSTYLE,
				BtnPosition(SIZE_X, 1, LEFTEXTENDWIDTH, HORIZONTAL_MARGIN), height - BtnPosition(SIZE_Y, 4, BOTTOMEXTENDWIDTH, VERTICAL_MARGIN),
				SIZE_X, SIZE_Y,
				m_hwnd,
				(HMENU)ID_BUTTONFIVE,
				(HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE),
				NULL);

			HWND btnNine = CreateWindow(L"Button", L"9", BTNSTYLE,
				BtnPosition(SIZE_X, 2, LEFTEXTENDWIDTH, HORIZONTAL_MARGIN), height - BtnPosition(SIZE_Y, 4, BOTTOMEXTENDWIDTH, VERTICAL_MARGIN),
				SIZE_X, SIZE_Y,
				m_hwnd,
				(HMENU)ID_BUTTONSIX,
				(HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE),
				NULL);

			HWND ac = CreateWindow(L"Button", L"AC", BTNSTYLE,
				BtnPosition(SIZE_X, 0, LEFTEXTENDWIDTH, HORIZONTAL_MARGIN), height - BtnPosition(SIZE_Y, 5, BOTTOMEXTENDWIDTH, VERTICAL_MARGIN),
				SIZE_X, SIZE_Y,
				m_hwnd,
				(HMENU)ID_BUTTONAC,
				(HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE),
				NULL);

			HWND parenLeft = CreateWindow(L"Button", L"(", BTNSTYLE,
				BtnPosition(SIZE_X, 1, LEFTEXTENDWIDTH, HORIZONTAL_MARGIN), height - BtnPosition(SIZE_Y, 5, BOTTOMEXTENDWIDTH, VERTICAL_MARGIN),
				SIZE_X, SIZE_Y,
				m_hwnd,
				(HMENU)ID_BUTTONPARENLEFT,
				(HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE),
				NULL);

			HWND parenRight = CreateWindow(L"Button", L")", BTNSTYLE,
				BtnPosition(SIZE_X, 2, LEFTEXTENDWIDTH, HORIZONTAL_MARGIN), height - BtnPosition(SIZE_Y, 5, BOTTOMEXTENDWIDTH, VERTICAL_MARGIN),
				SIZE_X, SIZE_Y,
				m_hwnd,
				(HMENU)ID_BUTTONPARENRIGHT,
				(HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE),
				NULL);


			/* Operators and Equals */

			HWND divs = CreateWindow(L"Button", L"/", BTNSTYLE,
				BtnPosition(SIZE_X, 3, LEFTEXTENDWIDTH, HORIZONTAL_MARGIN), height - BtnPosition(SIZE_Y, 5, BOTTOMEXTENDWIDTH, VERTICAL_MARGIN),
				SIZE_X, SIZE_Y,
				m_hwnd,
				(HMENU)ID_BUTTONDIVS,
				(HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE),
				NULL);

			HWND mult = CreateWindow(L"Button", L"*", BTNSTYLE,
				BtnPosition(SIZE_X, 3, LEFTEXTENDWIDTH, HORIZONTAL_MARGIN), height - BtnPosition(SIZE_Y, 4, BOTTOMEXTENDWIDTH, VERTICAL_MARGIN),
				SIZE_X, SIZE_Y,
				m_hwnd,
				(HMENU)ID_BUTTONMULT,
				(HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE),
				NULL);

			HWND minus = CreateWindow(L"Button", L"-", BTNSTYLE,
				BtnPosition(SIZE_X, 3, LEFTEXTENDWIDTH, HORIZONTAL_MARGIN), height - BtnPosition(SIZE_Y, 3, BOTTOMEXTENDWIDTH, VERTICAL_MARGIN),
				SIZE_X, SIZE_Y,
				m_hwnd,
				(HMENU)ID_BUTTONMIN,
				(HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE),
				NULL);

			HWND addition = CreateWindow(L"Button", L"+", BTNSTYLE,
				BtnPosition(SIZE_X, 3, LEFTEXTENDWIDTH, HORIZONTAL_MARGIN), height - BtnPosition(SIZE_Y, 2, BOTTOMEXTENDWIDTH, VERTICAL_MARGIN),
				SIZE_X, SIZE_Y,
				m_hwnd,
				(HMENU)ID_BUTTONPLUS,
				(HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE),
				NULL);

			HWND equal = CreateWindow(L"Button", L"=", BTNSTYLE,
				BtnPosition(SIZE_X, 3, LEFTEXTENDWIDTH, HORIZONTAL_MARGIN), height - BtnPosition(SIZE_Y, 1, BOTTOMEXTENDWIDTH, VERTICAL_MARGIN),
				SIZE_X, SIZE_Y,
				m_hwnd,
				(HMENU)ID_BUTTONEQUAL,
				(HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE),
				NULL);

			HWND display = CreateWindow(L"STATIC", L"0.0", WS_VISIBLE | WS_CHILD | SS_RIGHT,
				BtnPosition(SIZE_X, 0, LEFTEXTENDWIDTH, HORIZONTAL_MARGIN), height - BtnPosition(SIZE_Y, 6, BOTTOMEXTENDWIDTH, VERTICAL_MARGIN + 10),
					(SIZE_X * 4) + 6, SIZE_Y + 5,
					m_hwnd,
					(HMENU)ID_TEXTFIELD,
					(HINSTANCE)GetWindowLong(m_hwnd, GWL_HINSTANCE),
					NULL);

			HFONT hFont = CreateFont(20, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");
			SendMessage(display, WM_SETFONT, WPARAM(hFont), TRUE);

			return 0;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);

			return 0;
		}
		case WM_COMMAND:
		{

			if (LOWORD(wParam) == ID_BUTTONZERO)
			{

			}


			return 0;
		}
		/*case WM_CTLCOLORBTN:
		{
			RECT crect;
			HBRUSH brush;
			COLORREF background_color = RGB(100, 100, 100);
			HDC hdc = (HDC)wParam;
			HWND button_handle = (HWND)lParam;

			GetClientRect(button_handle, &crect);
			SetBkColor(hdc, background_color);
			SetTextColor(hdc, RGB(255, 255, 255));
			DrawText(hdc, L"BTN", _countof(L"BTN") - 1, &crect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

			brush = CreateSolidBrush(background_color);

			return (LRESULT)brush;
			break;
		}*/
		
		/*
		case WM_PAINT:
		{
			
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(m_hwnd, &ps);


			FillRect(hdc, &ps.rcPaint, (HBRUSH)(CreateSolidBrush(RGB(100, 130, 255))));

			EndPaint(m_hwnd, &ps);
			
			break;
		}*/
		default:
			return DefWindowProc(m_hwnd, message, wParam, lParam);
	}

	return TRUE;

}

void MainWindow::ScreenResolution(int& horizontal, int& vertical)
{
	RECT desktop;

	const HWND hDesktop = GetDesktopWindow();

	GetWindowRect(hDesktop, &desktop);

	horizontal = desktop.right;
	vertical = desktop.bottom;

}


int MainWindow::RECTWIDTH(RECT rect)
{
	return rect.right - rect.left;
}

int MainWindow::RECTHEIGHT(RECT rect)
{
	return rect.bottom - rect.top;
}

void MainWindow::PaintCustomCaption(HWND hWnd, HDC hdc, PAINTSTRUCT ps)
{
	RECT rcClient;
	GetClientRect(hWnd, &rcClient);

	HRESULT hr;
	HTHEME hTheme = OpenThemeData(NULL, L"CompositedWindow::Window");
	if (hTheme)
	{
		HDC hdcPaint = CreateCompatibleDC(hdc);
		if (hdcPaint)
		{
			int cx = RECTWIDTH(rcClient);
			int cy = RECTHEIGHT(rcClient);

			// Define the BITMAPINFO structure used to draw text.
			// Note that biHeight is negative. This is done because
			// DrawThemeTextEx() needs the bitmap to be in top-to-bottom
			// order.
			BITMAPINFO dib = { 0 };
			dib.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			dib.bmiHeader.biWidth = cx;
			dib.bmiHeader.biHeight = -cy;
			dib.bmiHeader.biPlanes = 1;
			dib.bmiHeader.biBitCount = 32;
			dib.bmiHeader.biCompression = BI_RGB;

			HBITMAP hbm = CreateDIBSection(hdc, &dib, DIB_RGB_COLORS, NULL, NULL, 0);
			if (hbm)
			{
				HBITMAP hbmOld = (HBITMAP)SelectObject(hdcPaint, hbm);

				// Setup the theme drawing options.
				DTTOPTS DttOpts = { sizeof(DTTOPTS) };
				DttOpts.dwFlags = DTT_COMPOSITED | DTT_GLOWSIZE;
				DttOpts.iGlowSize = 15;

				// Select a font.
				LOGFONT lgFont;
				HFONT hFontOld = NULL;

				hr = GetThemeSysFont(hTheme, TMT_CAPTIONFONT, &lgFont);

				if (SUCCEEDED(GetThemeSysFont(hTheme, TMT_CAPTIONFONT, &lgFont)))
				{
					HFONT hFont = CreateFontIndirect(&lgFont);
					hFontOld = (HFONT)SelectObject(hdcPaint, hFont);
				}

				// Draw the title.
				RECT rcPaint = rcClient;
				rcPaint.top += 3;
				rcPaint.right -= 125;
				rcPaint.left += 10;
				rcPaint.bottom = 50;

				DrawThemeTextEx(hTheme,
					hdcPaint,
					0, 0,
					windowTitle,
					-1,
					DT_LEFT | DT_WORD_ELLIPSIS,
					&rcPaint,
					&DttOpts);
				
				// Draw custom color for the border
				//FillRect(hdc, &rcClient, (HBRUSH)(CreateSolidBrush(RGB(100, 130, 255))));

				// Blit text to the frame.
				BitBlt(hdc, 0, 0, cx, cy, hdcPaint, 0, 0, SRCCOPY);


				SelectObject(hdcPaint, hbmOld);
				if (hFontOld)
				{
					SelectObject(hdcPaint, hFontOld);
				}
				DeleteObject(hbm);
			}

			DeleteDC(hdcPaint);
		}
		CloseThemeData(hTheme);
	}
	
}

LRESULT MainWindow::HitTestNCA(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	// Get the point coordinates for the hit test.
	POINT ptMouse = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };

	// Get the window rectangle.
	RECT rcWindow;
	GetWindowRect(hWnd, &rcWindow);

	// Get the frame rectangle, adjusted for the style without a caption.
	RECT rcFrame = { 0 };
	AdjustWindowRectEx(&rcFrame, WS_OVERLAPPEDWINDOW & ~WS_CAPTION, FALSE, NULL);

	// Determine if the hit test is for resizing. Default middle (1,1).
	USHORT uRow = 1;
	USHORT uCol = 1;
	bool fOnResizeBorder = false;

	// Determine if the point is at the top or bottom of the window.
	if (ptMouse.y >= rcWindow.top && ptMouse.y < rcWindow.top + TOPEXTENDWIDTH)
	{
		fOnResizeBorder = (ptMouse.y < (rcWindow.top - rcFrame.top));
		uRow = 0;
	}
	else if (ptMouse.y < rcWindow.bottom && ptMouse.y >= rcWindow.bottom - BOTTOMEXTENDWIDTH)
	{
		uRow = 2;
	}

	// Determine if the point is at the left or right of the window.
	if (ptMouse.x >= rcWindow.left && ptMouse.x < rcWindow.left + LEFTEXTENDWIDTH)
	{
		uCol = 0; // left side
	}
	else if (ptMouse.x < rcWindow.right && ptMouse.x >= rcWindow.right - RIGHTEXTENDWIDTH)
	{
		uCol = 2; // right side
	}

	// Hit test (HTTOPLEFT, ... HTBOTTOMRIGHT)
	LRESULT hitTests[3][3] =
	{
		{ HTTOPLEFT,    fOnResizeBorder ? HTTOP : HTCAPTION,    HTTOPRIGHT },
		{ HTLEFT,       HTNOWHERE,     HTRIGHT },
		{ HTBOTTOMLEFT, HTBOTTOM, HTBOTTOMRIGHT },
	};

	return hitTests[uRow][uCol];
}



int MainWindow::BtnPosition(int size, int mult, int extend, int addi)
{
	return (size * mult) + extend + (addi + (mult * 2));
}
