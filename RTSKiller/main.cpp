#include "pch.h"
#include "app/Win32Framework.h"
#include "RTSKiller.h"

int main()
{
	rtsk::RTSKiller app{};
	rtsk::Win32Framework win32Framework{ &app };
	return win32Framework.Run();
}