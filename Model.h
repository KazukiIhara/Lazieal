#pragma once

//  C++
#include <string>
#include <vector>
#include <wrl.h>

// DirectX
#include <d3d12.h>

// MyHedder
#include "ObjectStruct.h"

// 3Dモデル
class cModel {
public: // 構造体

	// マテリアルデータ
	struct sMaterialData {
		std::string textureFilePath;
		uint32_t srvIndex;
		Vector4 color;
	};

	// モデルデータ
	struct sModelData {
		std::vector<sVertexData3D> vertices;
		sMaterialData material;
	};

public: // メンバ関数
	// 初期化
	void Initialize(const std::string& filename);
	// 更新
	void Update();
	// 描画
	void Draw();
	// モデルの読み込み
	void LoadModel(const std::string& filename, const std::string& directoryPath = "Game/Resources");

private: // メンバ関数
#pragma region Vertex
	/*頂点リソースの作成*/
	void CreateVertexResource();
	/*頂点バッファビューの作成*/
	void CreateVretexBufferView();
	/*頂点データの書き込み*/
	void MapVertexData();
#pragma endregion

#pragma region Material
	/*マテリアルリソースの作成*/
	void CreateMaterialResource();
	/*マテリアルデータの書き込み*/
	void MapMaterialData();
#pragma endregion
	/*バッファリソースを作成する*/
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(ID3D12Device* device, size_t sizeInBytes);

private: // メンバ変数
#pragma region モデル
	/*モデルデータを受け取る箱*/
	sModelData modelData;
#pragma endregion

#pragma region 頂点
	/*頂点リソース*/
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource_ = nullptr;
	/*頂点データ*/
	sVertexData3D* vertexData_ = nullptr;
	/*VBV*/
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_;
#pragma endregion

#pragma region マテリアル
	/*マテリアルリソース*/
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource_ = nullptr;
	/*マテリアルデータ*/
	sMaterial3D* materialData_ = nullptr;
	// マテリアル
	sMaterial3D material_;
	/*uvTransform*/
	sUVTransform uvTransform_;
#pragma endregion
};