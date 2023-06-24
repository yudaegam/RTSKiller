#pragma once
#include "Win32App.h"
namespace rtsk { class Win32Framework; }

class rtsk::Win32Framework
{
public:
	Win32Framework(Win32App* pApp);
	int Run();

private:
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};
