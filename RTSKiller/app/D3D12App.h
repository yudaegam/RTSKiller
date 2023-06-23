#pragma once
namespace rtsk { class D3D12App; }

class rtsk::D3D12App
{
public:
	D3D12App(HWND hwnd);
	~D3D12App();

	D3D12App(D3D12App& other) = delete;
	D3D12App(D3D12App&& other) = delete;

protected:
	void ThrowIfFailed(HRESULT hr);

protected:
	static constexpr std::uint32_t FrameCount = 2;

	ComPtr<IDXGISwapChain4> m_swapChain;
	ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
	ComPtr<ID3D12Resource> m_backBuffers[FrameCount];
	ComPtr<ID3D12Device2> m_device;
	ComPtr<ID3D12CommandQueue> m_commandQueue;
	ComPtr<ID3D12GraphicsCommandList> m_commandList;
	ComPtr<ID3D12CommandAllocator> m_commandAllocator;
	ComPtr<ID3D12RootSignature> m_rootSignature;
	ComPtr<ID3D12PipelineState> m_pipelineState;

	// Synchronization objects.
	int m_frameIndex;
	HANDLE m_fenceEvent;
	ComPtr<ID3D12Fence> m_fence;
	UINT64 m_fenceValue;
};

