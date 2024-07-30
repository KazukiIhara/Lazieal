#pragma once

// C++
#include <cstdint>

// DirectX
#include <d3d12.h>

class cSrvManager {
public: // 公開メンバ関数
	cSrvManager();
	~cSrvManager();

	// 初期化
	void Initialize();
	// 割り当て関数
	void Allocate();
	// CPUの特定のインデックスハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(uint32_t index);
	// GPUの特定のインデックスハンドルを取得
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(uint32_t index);
	// SRV生成(テクスチャ用)
	void CreateSrvTexture2d(uint32_t srvIndex, ID3D12Resource* pResource, DXGI_FORMAT format, UINT MipLevels);

private:

};