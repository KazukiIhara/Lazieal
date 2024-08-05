#pragma once

// C++
#include <string>

// MyHedder
#include "PipelineManager.h"
#include "MathFunction.h"
#include "ObjectStruct.h"
#include "WorldTransform.h"

class cSprite {
public: // メンバ関数
	// 初期化
	void Initialize(const std::string& textureFilePath);
	// 更新
	void Update();
	// 描画
	void Draw(cPipelineManager::eBlendMode blendMode = cPipelineManager::kBlendModeNormal);

	// ゲッター
	// textureHandle_
	const std::string& GetTextureFilePath()const {
		return textureFilePath_;
	}
	// 座標
	const Vector2& GetPosition()const {
		return position;
	}
	// 回転
	const float& GetRotation()const {
		return rotation;
	}
	// 色
	const Vector4& GetColor()const {
		return materialData_->color;
	}
	// サイズ
	const Vector2& GetSize()const {
		return size;
	}
	// アンカーポイント
	const Vector2& GetAnchorPoint()const {
		return anchorPoint;
	}
	// 左右フリップ
	const bool& GetIsFlipX()const {
		return isFlipX_;
	}
	// 上下フリップ
	const bool& GetIsFlipY()const {
		return isFlipY_;
	}
	// テクスチャ左上座標
	const Vector2& GetTextureLeftTop()const {
		return textureLeftTop;
	}
	// テクスチャ切り出し
	const Vector2& GetTextureSize()const {
		return textureSize;
	}

	// セッター
	// textureHandle_
	void SetTextureHandle(const std::string& textureFilePath) {
		this->textureFilePath_ = textureFilePath;
	}
	// 座標
	void SetPosition(const Vector2& position) {
		this->position = position;
	}
	// 回転
	void SetRotation(const float& rotation) {
		this->rotation = rotation;
	}
	// 色
	void SetColor(const Vector4& color) {
		materialData_->color = color;
	}
	// サイズ
	void SetSize(const Vector2& size) {
		this->size = size;
	}
	// アンカーポイント
	void SetAnchorPoint(const Vector2& anchorPoint) {
		this->anchorPoint = anchorPoint;
	}
	// 左右フリップ
	void SetIsFlipX(const bool& isFlipX) {
		this->isFlipX_ = isFlipX;
	}
	// 上下フリップ
	void SetIsFlipY(const bool& isFlipY) {
		this->isFlipY_ = isFlipY;
	}
	// テクスチャ左上座標
	void SetTextureLeftTop(const Vector2& textureLeftTop) {
		this->textureLeftTop = textureLeftTop;
	}
	// テクスチャ切り出しサイズ
	void SetTextureSize(const Vector2& textureSize) {
		this->textureSize = textureSize;
	}

private: // メンバ関数
#pragma region Vertex
	/*頂点リソースの作成*/
	void CreateVertexResource();
	/*頂点バッファビューの作成*/
	void CreateVretexBufferView();
	/*頂点データの書き込み*/
	void MapVertexData();
#pragma endregion

#pragma region Index
	/*描画用のインデックスリソースを作成*/
	void CreateIndexResource();
	/*インデックスバッファビューの作成*/
	void CreateIndexBufferView();
	/*インデックスリソースにデータを書き込む*/
	void MapIndexResource();
#pragma endregion

#pragma region Material
	/*マテリアルリソースの作成*/
	void CreateMaterialResource();
	/*マテリアルデータの書き込み*/
	void MapMaterialData();
#pragma endregion

#pragma region WVP
	/*wvp用のリソース作成*/
	void CreateWVPResource();
	/*データを書き込む*/
	void MapWVPData();
#pragma endregion
#pragma region BufferResource
	/*バッファリソースを作成する*/
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(ID3D12Device* device, size_t sizeInBytes);
#pragma endregion

	// テクスチャサイズをイメージに合わせる
	void AdjustTextureSize();

private:/*メンバ変数*/

	// TextureHandle
	std::string textureFilePath_;

	// 座標
	Vector2 position = { 0.0f,0.0f };
	// 回転
	float rotation = 0.0f;
	// サイズ
	Vector2 size = { 100.0f,100.0f };

	// アンカーポイント
	Vector2 anchorPoint = { 0.0f,0.0f };

	// 左右フリップ
	bool isFlipX_ = false;
	// 上下フリップ
	bool isFlipY_ = false;

	// テクスチャ左上座標
	Vector2 textureLeftTop = { 0.0f,0.0f };
	// テクスチャ切り出しサイズ
	Vector2	textureSize = { 100.0f,100.0f };

#pragma region 頂点
	/*頂点リソース*/
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource_ = nullptr;
	/*VBV*/
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_;
	/*頂点データ*/
	sVertexData2D* vertexData_;
#pragma endregion

#pragma region インデックス
	/*インデックスリソース*/
	Microsoft::WRL::ComPtr<ID3D12Resource> indexResource_ = nullptr;
	/*インデックスバッファビュー*/
	D3D12_INDEX_BUFFER_VIEW indexBufferView_{};
	/*インデックスデータ*/
	uint32_t* indexData_;
#pragma endregion

#pragma region マテリアル
	/*マテリアルリソース*/
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource_ = nullptr;
	/*マテリアルデータ*/
	sMaterial2D* materialData_ = nullptr;
	/*マテリアル情報を受け取る箱*/
	sMaterial2D material_;
#pragma endregion

#pragma region 変換
	/*WVP用のリソース*/
	Microsoft::WRL::ComPtr<ID3D12Resource> transformationResource_ = nullptr;
	Matrix4x4* wvpData_;
	/*トランスフォームデータを受け取る箱*/
	cWorldTransform worldTransform_;
#pragma endregion

};
