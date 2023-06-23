#pragma once
#include "Win32App.h"
#include "D3D12App.h"

namespace rtsk { class IntegrationApp; }
class rtsk::IntegrationApp : public rtsk::Win32App, public rtsk::D3D12App
{
public:
	IntegrationApp();
	~IntegrationApp();

	IntegrationApp(const IntegrationApp&) = delete;
	IntegrationApp(IntegrationApp&&) = delete;

	int Run();
private:
	virtual void OnUpdate() abstract;
	virtual void OnRender() abstract;

private:
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

