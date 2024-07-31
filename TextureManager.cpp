// This
#include "TextureManager.h"

// MyHedder
#include "DirectXCommon.h"
#include "SrvManager.h"

cTextureManager::cTextureManager() {
}

cTextureManager::~cTextureManager() {
}

void cTextureManager::Initialize() {
}

uint32_t cTextureManager::AllocateSrvIndex(const std::string& filePath) {
	// 今回ぶち込むテクスチャーの箱
	Texture& texture = textures_[filePath];
	DirectX::ScratchImage mipImage_ = LoadTexture(filePath);
	texture.metaData = mipImage_.GetMetadata();
	texture.resource = CreateTextureResource(directX_->GetDevice(), texture.metaData);
	Microsoft::WRL::ComPtr<ID3D12Resource> intermediateResource = UploadTextureData(texture.resource.Get(), mipImage_, directX_->GetDevice(), directX_->GetCommandList());

	// コマンドのクローズと実行
	KickCommand();

	// SRVを作成するDescriptorHeapの場所を決める
	texture.srvIndex = srvManager_->Allocate();
	// srvの作成
	srvManager_->CreateSrvTexture2d(texture.srvIndex, textures_[filePath].resource.Get(), texture.metaData.format, UINT(texture.metaData.mipLevels));

	// テクスチャ枚数上限チェック
	assert(srvManager_->IsLowerSrvMax());

	return texture.srvIndex;
}

const DirectX::TexMetadata& cTextureManager::GetMetaData(const std::string& filePath) {
	assert(&GetTexture()[filePath]);
	Texture& texture = GetTexture()[filePath];
	return texture.metaData;
}


Microsoft::WRL::ComPtr<ID3D12Resource> cTextureManager::CreateBufferResource(ID3D12Device* device, size_t sizeInBytes) {
	return Microsoft::WRL::ComPtr<ID3D12Resource>();
}

void cTextureManager::CreateFence() {
}

void cTextureManager::KickCommand() {
}

DirectX::ScratchImage cTextureManager::LoadTexture(const std::string& filePath) {
	return DirectX::ScratchImage();
}

Microsoft::WRL::ComPtr<ID3D12Resource> cTextureManager::CreateTextureResource(ID3D12Device* device, const DirectX::TexMetadata& metadata) {
	return Microsoft::WRL::ComPtr<ID3D12Resource>();
}

Microsoft::WRL::ComPtr<ID3D12Resource> cTextureManager::UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages, ID3D12Device* device, ID3D12GraphicsCommandList* commandList) {
	return Microsoft::WRL::ComPtr<ID3D12Resource>();
}


