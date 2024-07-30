#pragma once

// C++
#include <chrono>
#include <cmath>
#include <cassert>
#include <wrl.h>

// DirectX
#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>
#include <dxcapi.h>

// 前方宣言
class cWinAPI;

// DirectX基本処理クラス
class cDirectXCommon {
public: // インスタンスコピー関数

	// WinAPIのインスタンスをコピー
	void SetWinAPI(cWinAPI* win) {
		win_ = win;
	}

public: // 公開メンバ関数
	cDirectXCommon();
	~cDirectXCommon();

	// 初期化
	void Initialize(bool enableDebugLayer = true);
	// 描画前処理
	void PreDraw();
	// 描画後処理
	void PostDraw();

	// デバイスの取得
	ID3D12Device* GetDevice() {
		return device_.Get();
	}
	// 描画コマンドリストの取得
	ID3D12GraphicsCommandList* GetCommandList() {
		return commandList_.Get();
	}
	// コマンドキューの取得
	ID3D12CommandQueue* GetCommandQueue() {
		return commandQueue_.Get();
	}
	// コマンドアロケータの取得
	ID3D12CommandAllocator* GetCommandAllocator() {
		return commandAllocator_.Get();
	}
	// スワップチェインディスクリプタを取得
	DXGI_SWAP_CHAIN_DESC1 GetSwapChainDesc() const {
		return swapChainDesc_;
	}
	// rtvDescを取得
	D3D12_RENDER_TARGET_VIEW_DESC GetRTVDesc() const {
		return rtvDesc_;
	}

	// CPUの特定のインデックスのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);
	// GPUの特定のインデックスのハンドルを取得
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);

	// ディスクリプタヒープの作成
	static Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);

private: // プライベートメンバ関数
	// DXGIデバイスの生成と初期化
	void InitializeDXGIDevice(bool enableDebugLayer);

	// コマンド関連初期化
	void InitializeCommand();

	// スワップチェーンを生成する
	void CreateSwapChain();

	// レンダーターゲットビューを生成する
	void CreateRenderTargetView();

	// デプスステンシルビューを生成する
	void CreateDepthStencilView();

	// フェンスを生成する
	void CreateFence();

	// 深度クリア
	void ClearDepthView();
	// レンダーターゲットのクリア
	void ClearRenderTarget(float clearColor[]);
	// レンダーターゲットのセット
	void SetRenderTargets();

	// ビューポートの設定
	void SettingViewport();

	// シザー矩形の設定
	void SettingScissorRect();

	// FPS固定処理

	// FPS固定処理初期化
	void InitializeFixFPS();
	// FPS固定処理更新
	void UpdateFixFPS();

	// デプスステンシルリソースの作成
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateDepthStencilTextureResource(ID3D12Device* device, int32_t width, int32_t height);

private: // メンバ変数
	// SUCCEEDEDでエラー判別君
	HRESULT hr_ = S_FALSE;

	// DXGIファクトリー
	Microsoft::WRL::ComPtr <IDXGIFactory7> dxgiFactory_ = nullptr;
	// 使用するアダプタ用の変数
	Microsoft::WRL::ComPtr<IDXGIAdapter4> useAdapter_ = nullptr;
	// Device
	Microsoft::WRL::ComPtr<ID3D12Device> device_ = nullptr;
	// コマンドキュー
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue_ = nullptr;
	// コマンドアロケータ
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator_ = nullptr;
	// コマンドリスト
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList_ = nullptr;
	// スワップチェーン
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc_{};
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain_ = nullptr;

	// DepthStencilResource
	Microsoft::WRL::ComPtr<ID3D12Resource> depthStencilResource_ = nullptr;

	// ディスクリプタヒープ
	// DSV用
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvDescriptorHeap_ = nullptr;
	// RTV用
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap_ = nullptr;
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc_{};

	// スワップチェーンリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> swapChainResources_[2] = { nullptr };

	// フェンス
	Microsoft::WRL::ComPtr<ID3D12Fence> fence_ = nullptr;

	// RTVを2つ作るのでディスクリプタを2つ用意
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles_[2] = { 0 };

	// DSVのディスクリプタ
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle_;

	// バリア
	D3D12_RESOURCE_BARRIER barrier_{};

	// バックバッファインデックス
	UINT backBufferIndex_ = 0;

	// フェンスバリュー
	UINT64 fenceValue_ = 0;

	// 記録時間(FPS固定用)
	std::chrono::steady_clock::time_point reference_;

	// DescriptorSize取得
	uint32_t descriptorSizeRTV_ = 0u;
	uint32_t descriptorSizeDSV_ = 0u;

private: // インスタンスコピーポインタ
	cWinAPI* win_ = nullptr;
};