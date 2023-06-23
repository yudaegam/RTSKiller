#include "pch.h"
#include "RTSKiller.h"

rtsk::RTSKiller::RTSKiller()
{
}

rtsk::RTSKiller::~RTSKiller()
{
}

void rtsk::RTSKiller::OnUpdate()
{

}

void rtsk::RTSKiller::OnRender()
{
	ComPtr<ID3D12Resource>& backBuffer = m_backBuffers[m_frameIndex];
	ThrowIfFailed(m_commandAllocator->Reset());
	ThrowIfFailed(m_commandList->Reset(m_commandAllocator.Get(), nullptr));

	const auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(
		backBuffer.Get(),
		D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);

	m_commandList->ResourceBarrier(1, &barrier);

	float clearColor[] = { 0.0f, 0.2f, 0.4f, 1.0f };
	const std::uint32_t rtvSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle{ m_rtvHeap->GetCPUDescriptorHandleForHeapStart(), m_frameIndex, rtvSize };
	m_commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

	const CD3DX12_RESOURCE_BARRIER barrier2 = CD3DX12_RESOURCE_BARRIER::Transition(
		backBuffer.Get(),
		D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);

	m_commandList->ResourceBarrier(1, &barrier2);

	ThrowIfFailed(m_commandList->Close());

	m_commandQueue->ExecuteCommandLists(1, CommandListCast(m_commandList.GetAddressOf()));

	ThrowIfFailed(m_commandQueue->Signal(m_fence.Get(), m_fenceValue++));
	ThrowIfFailed(m_swapChain->Present(0, 0));

	ThrowIfFailed(m_fence->SetEventOnCompletion(m_fenceValue - 1, m_fenceEvent));


	if (::WaitForSingleObject(m_fenceEvent, INFINITE) == WAIT_FAILED)
	{
		throw std::runtime_error("Failed to wait for single object.");
	}

	m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();

}
