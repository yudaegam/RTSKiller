#include "pch.h"
#include "D3D12App.h"
#include <comdef.h>

rtsk::D3D12App::D3D12App(HWND hwnd)
{
	// Create DXGI factory
	ComPtr<IDXGIFactory4> factory;
	ThrowIfFailed(CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&factory)));

	// Create D3D12 device
	ThrowIfFailed(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&m_device)));


	// Create command queue
	constexpr D3D12_COMMAND_QUEUE_DESC commandQueueDesc{
		.Type = D3D12_COMMAND_LIST_TYPE_DIRECT,
		.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL,
		.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE,
		.NodeMask = 0,
	};

	ThrowIfFailed(m_device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&m_commandQueue)));

	// Create swap chain
	constexpr DXGI_SWAP_CHAIN_DESC1 swapChainDesc{
		.Width = 0,
		.Height = 0,
		.Format = DXGI_FORMAT_R8G8B8A8_UNORM,
		.Stereo = FALSE,
		.SampleDesc = {.Count = 1, .Quality = 0 },
		.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT,
		.BufferCount = FrameCount,
		.Scaling = DXGI_SCALING_STRETCH,
		.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD,
		.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED,
		.Flags = 0,
	};

	ComPtr<IDXGISwapChain1> swapChain1;
	ThrowIfFailed(factory->CreateSwapChainForHwnd(
		m_commandQueue.Get(), hwnd, &swapChainDesc, nullptr, nullptr, &swapChain1));

	ThrowIfFailed(swapChain1.As(&m_swapChain));

	// Create RTV descriptor heap
	constexpr D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc{
		.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV,
		.NumDescriptors = FrameCount,
		.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
		.NodeMask = 0,
	};

	ThrowIfFailed(m_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&m_rtvHeap)));

	const std::uint32_t rtvSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle{ m_rtvHeap->GetCPUDescriptorHandleForHeapStart() };

	// Create RTV for each back buffer
	for (int i = 0; i < FrameCount; ++i)
	{
		ThrowIfFailed(m_swapChain->GetBuffer(i, IID_PPV_ARGS(&m_backBuffers[i])));
		m_device->CreateRenderTargetView(m_backBuffers[i].Get(), nullptr, rtvHandle);
		rtvHandle.Offset(rtvSize);
	}

	// Create command allocator
	ThrowIfFailed(m_device->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocator)));

	// Create command list
	ThrowIfFailed(m_device->CreateCommandList(
		0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator.Get(), nullptr, IID_PPV_ARGS(&m_commandList)));

	// Close command list
	ThrowIfFailed(m_commandList->Close());

	// Create fence
	ThrowIfFailed(m_device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence)));

	// Create fence event
	m_fenceEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
	if (!m_fenceEvent)
	{
		ThrowIfFailed(GetLastError());
	}

	m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();
}

rtsk::D3D12App::~D3D12App()
{
}

void rtsk::D3D12App::ThrowIfFailed(HRESULT hr)
{
	if (FAILED(hr))
	{
		_com_error err(hr);
		LPCTSTR errMsg = err.ErrorMessage();
		::OutputDebugString(errMsg);
		throw hr;
	}
}
