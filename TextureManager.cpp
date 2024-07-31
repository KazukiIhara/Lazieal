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
	return 0;
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


