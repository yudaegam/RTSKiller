#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <string_view>
#include <format>
#include <filesystem>
#include <memory>
#include <stdexcept>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wrl.h>
using Microsoft::WRL::ComPtr;

#include <d3d12.h>
#include <dxgi1_6.h>
#include <D3Dcompiler.h>
#include <DirectXMath.h>
#include "d3dx12.h"

#ifdef _DEBUG
#include <dxgidebug.h>
#endif