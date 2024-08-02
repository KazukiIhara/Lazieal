// This
#include "Model.h"

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

void cModel::Initialize(const std::string& filename) {
}

void cModel::Update() {
}

void cModel::Draw() {
}

void cModel::LoadModel(const std::string& filename, const std::string& directoryPath) {
}

void cModel::CreateVertexResource() {
}

void cModel::CreateVretexBufferView() {
}

void cModel::MapVertexData() {
}

void cModel::CreateMaterialResource() {
}

void cModel::MapMaterialData() {
}

Microsoft::WRL::ComPtr<ID3D12Resource> cModel::CreateBufferResource(ID3D12Device* device, size_t sizeInBytes) {
	return Microsoft::WRL::ComPtr<ID3D12Resource>();
}
