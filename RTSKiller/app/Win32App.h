#pragma once
namespace rtsk { class Win32App; }

class rtsk::Win32App
{
public:
	Win32App();
	virtual ~Win32App();

	virtual void OnUpdate() abstract;
	virtual void OnRender() abstract;

	HWND GetHwnd() const noexcept { return m_hwnd; }
	std::uint32_t GetWidth() const noexcept { return m_width; }
	std::uint32_t GetHeight() const noexcept { return m_height; }

private:
	HWND m_hwnd{};
	std::uint32_t m_width{ 1280 };
	std::uint32_t m_height{ 720 };

	static inline const wchar_t* m_class_name = L"rtsk::Win32App";
	static inline const wchar_t* m_window_name = L"rts killer";
};

