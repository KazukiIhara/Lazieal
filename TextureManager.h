#pragma once
#pragma once

// C++
#include <cstdint>
#include <wrl.h>

// DirectX
#include <d3d12.h>

// DirectxTex
#include "externals/DirectXTex/DirectXTex.h"
#include "externals/DirectXTex/d3dx12.h"

// 前方宣言
class cDirectXCommon;
class cSrvManager;

class cTextureManager {
public: // 構造体
	// テクスチャ構造体
	struct Texture {
		// テクスチャリソース
		Microsoft::WRL::ComPtr<ID3D12Resource> resource;
		// メタデータ
		DirectX::TexMetadata metaData;
		// srvIndex
		uint32_t srvIndex;
	};

public: // 公開メンバ関数
	cTextureManager();
	~cTextureManager();

	// 初期化
	void Initialize();

	// テクスチャのロード
	uint32_t AllocateSrvIndex(const std::string& filePath);

	// Textureを渡す
	std::unordered_map<std::string, Texture>& GetTexture() {
		return textures_;
	}
	// メタデータを渡す
	const DirectX::TexMetadata& GetMetaData(const std::string& filePath);


private: // 非公開メンバ関数
	// バッファリソースを作成する
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(ID3D12Device* device, size_t sizeInBytes);
	// テクスチャー転送用のfence作成
	void CreateFence();
	// テクスチャー転送のコマンドを実行する関数
	void KickCommand();
	// Texture読み込み
	DirectX::ScratchImage LoadTexture(const std::string& filePath);
	// テクスチャリソースを作る
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata);
	// テクスチャデータを送る
	Microsoft::WRL::ComPtr<ID3D12Resource> UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages, ID3D12Device* device, ID3D12GraphicsCommandList* commandList);


private: // メンバ変数
	// テクスチャコンテナ
	std::unordered_map<std::string, Texture> textures_;
	// フェンス
	Microsoft::WRL::ComPtr<ID3D12Fence> fence_ = nullptr;
	UINT fenceValue_ = 0;
private: // インスタンス受け取り変数
	// DirectXCommon
	cDirectXCommon* directX_ = nullptr;
	// SrvManager
	cSrvManager* srvManager_ = nullptr;

};