#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <chrono>
#include <format>
#include <string_view>
#include <filesystem>
#include <stdexcept>
#include <numbers>

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