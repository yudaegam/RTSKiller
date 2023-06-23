#include "pch.h"
#include "IntegrationApp.h"

rtsk::IntegrationApp::IntegrationApp()
	: rtsk::Win32App()
	, rtsk::D3D12App(GetHwnd())
{
	::SetWindowLongPtrW(GetHwnd(), GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	::SetWindowLongPtrW(GetHwnd(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc));
}

rtsk::IntegrationApp::~IntegrationApp()
{
}

int rtsk::IntegrationApp::Run()
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

LRESULT CALLBACK rtsk::IntegrationApp::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	IntegrationApp* pApp = reinterpret_cast<IntegrationApp*>(::GetWindowLongPtrW(hwnd, GWLP_USERDATA));

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
