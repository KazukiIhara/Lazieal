#pragma once

// C++
#include <cstdint>
#include <wrl.h>

// DirectX
#include <d3d12.h>

// 前方宣言
class cDirectXCommon;

class cSrvManager {
public: // インスタンスコピー関数
	// DirectX
	void SetDirectXCommon(cDirectXCommon* directX) {
		directX_ = directX;
	}

public: // 公開メンバ関数
	cSrvManager();
	~cSrvManager();

	// 初期化
	void Initialize();
	// 割り当て関数
	uint32_t Allocate();
	// CPUの特定のインデックスハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(uint32_t index);
	// GPUの特定のインデックスハンドルを取得
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(uint32_t index);
	// SRV生成(テクスチャ用)
	void CreateSrvTexture2d(uint32_t srvIndex, ID3D12Resource* pResource, DXGI_FORMAT format, UINT MipLevels);
	// Srvの数が最大数を上回っているかどうか
	bool IsLowerSrvMax();
	// 描画前処理
	void PreDraw();
	// ルートパラメータインデックスと、srv番号に対応したDescriptorTableを取得
	void SetGraphicsRootDescriptorTable(UINT rootParameterIndex, uint32_t srvIndex);

public: // 公開メンバ変数
	// 最大SRV数
	static const uint32_t kMaxSRVCount = 512;
private: // 非公開メンバ変数
	// SRV用
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap_ = nullptr;
	// SrvDiscriptorのサイズ
	uint32_t descriptorSize_ = 0u;
	// 使用しているSrvのインデックス
	uint32_t useIndex = 0;
private: // インスタンスコピーポインタ
	// DirectXCommon
	cDirectXCommon* directX_;
};