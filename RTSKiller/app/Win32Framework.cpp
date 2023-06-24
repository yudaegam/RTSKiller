#include "pch.h"
#include "Win32Framework.h"


rtsk::Win32Framework::Win32Framework(Win32App* pApp)
{
	const HWND hwnd = pApp->GetHwnd();
	::SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pApp));
	::SetWindowLongPtrW(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc));
}

int rtsk::Win32Framework::Run()
{
	MSG msg{};
	while (msg.message != WM_QUIT)
	{
		if (::PeekMessageW(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessageW(&msg);
		}
	}
	return static_cast<char>(msg.wParam);
}

LRESULT rtsk::Win32Framework::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Win32App* pApp = reinterpret_cast<Win32App*>(::GetWindowLongPtrW(hwnd, GWLP_USERDATA));

	switch (msg)
	{
	case WM_PAINT:
		if (pApp)
		{
			pApp->OnUpdate();
			pApp->OnRender();
		}
		return 0;

	case WM_DESTROY:
		::PostQuitMessage(0);
		return 0;
	}

	return ::DefWindowProcW(hwnd, msg, wParam, lParam);
}

