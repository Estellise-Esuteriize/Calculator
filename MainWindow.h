#pragma once
#include "BaseWindow.h"

class MainWindow : public BaseWindow<MainWindow>
{

	LPCWSTR windowTitle = L"Calculator";

	void ScreenResolution(int&, int&);
	void PaintCustomCaption(HWND, HDC, PAINTSTRUCT);
	LRESULT HitTestNCA(HWND, WPARAM, LPARAM);
	int RECTWIDTH(RECT);
	int RECTHEIGHT(RECT);

	int BtnPosition(int, int, int, int);
	
	public:
		MainWindow();
		PCWSTR ClassName() const;
		LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam);


};

