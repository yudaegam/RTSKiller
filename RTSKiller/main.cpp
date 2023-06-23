#include "pch.h"
#include "RTSKiller.h"

int main()
{
	auto app = std::make_unique<rtsk::RTSKiller>();
	return app->Run();
}