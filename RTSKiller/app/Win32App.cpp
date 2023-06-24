#include "pch.h"
#include "Win32App.h"

rtsk::Win32App::Win32App()
{
	WNDCLASSEXW wc{ sizeof(wc), CS_CLASSDC, DefWindowProcW, 0L, 0L, GetModuleHandle(NULL), 
		NULL, NULL, NULL, NULL, m_class_name, NULL };
	::RegisterClassExW(&wc);

	RECT rect{ 0, 0, static_cast<LONG>(m_width), static_cast<LONG>(m_height) };
	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	int adjusted_width{ rect.right - rect.left };
	int adjusted_height{ rect.bottom - rect.top };

	m_hwnd = ::CreateWindowW(m_class_name, m_window_name, WS_OVERLAPPEDWINDOW, 100, 100,
		adjusted_width, adjusted_height, NULL, NULL, GetModuleHandle(NULL), NULL);

	::ShowWindow(GetHwnd(), SW_SHOWDEFAULT);
}

rtsk::Win32App::~Win32App()
{
	::DestroyWindow(m_hwnd);
	::UnregisterClassW(m_class_name, GetModuleHandle(NULL));
}
