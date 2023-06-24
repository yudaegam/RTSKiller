#pragma once
#include "app/Win32App.h"
#include "app/D3D12App.h"
namespace rtsk { class RTSKiller; }
class rtsk::RTSKiller : public rtsk::Win32App, public rtsk::D3D12App
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
	float m_clearColor[4]{ 0.0f, 0.2f, 0.4f, 1.0f };
};

