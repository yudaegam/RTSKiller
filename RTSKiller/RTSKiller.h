#pragma once
#include "app/IntegrationApp.h"
namespace rtsk { class RTSKiller; }
class rtsk::RTSKiller : public rtsk::IntegrationApp
{
public:
	RTSKiller();
	~RTSKiller();

	RTSKiller(const RTSKiller&) = delete;
	RTSKiller(RTSKiller&&) = delete;

private:
	virtual void OnUpdate() override;
	virtual void OnRender() override;

public:
	int a{ 1 };
	int b{ 2 };
};

