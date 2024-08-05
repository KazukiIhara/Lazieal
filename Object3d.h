#pragma once

// C++
#include <memory>
#include <wrl.h>
#include <string>

// DirectX
#include <d3d12.h>

// MyHedder
#include "ObjectStruct.h"
#include "WorldTransform.h"
#include "PipelineManager.h"
#include "Model.h"
#include "Camera.h"
#include "PunctualLight.h"

// 3Dモデル
class cObject3D {
public:
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw(cPipelineManager::eBlendMode blendMode = cPipelineManager::kBlendModeNormal);
	void DrawUnUV(cPipelineManager::eBlendMode blendMode = cPipelineManager::kBlendModeNormal);
private:

#pragma region WVP
	/*wvp用のリソース作成*/
	void CreateWVPResource();
	/*データを書き込む*/
	void MapWVPData();
#pragma endregion

	/*バッファリソースを作成する*/
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(ID3D12Device* device, size_t sizeInBytes);
public: // Setter
	// modelのセット
	void SetModel(const std::string& filePath);
	// 拡縮のセット
	void SetScale(const Vector3& scale) {
		this->transform_.scale = scale;
	}
	// 回転のセット
	void SetRotate(const Vector3& rotate) {
		this->transform_.rotate = rotate;
	}
	// 移動量のセット
	void SetTranslate(const Vector3& translate) {
		this->transform_.translate = translate;
	}
	// トランスフォームのセット
	void SetTransform(const cWorldTransform& transform) {
		this->transform_.scale = transform.scale;
		this->transform_.rotate = transform.rotate;
		this->transform_.translate = transform.translate;
	}
	// ライトのセット
	void SetPunctualLight(const cPunctualLight& punctualLight) {
		punctualLight_ = punctualLight;
	}
public: // Getter
	// 拡縮のゲッター
	const Vector3& GetScale() const {
		return transform_.scale;
	}
	// 回転のゲッター
	const Vector3& GetRotate() const {
		return transform_.rotate;
	}
	// 移動量のゲッター
	const Vector3& GetTranslate() const {
		return transform_.translate;
	}
	// オブジェクトの名前のゲッター
	const std::string& GetName()const {
		return objectname_;
	}
	cModel* GetModel() {
		return model;
	}

private:/*メンバ変数*/
#pragma region Model
	cModel* model = nullptr;
#pragma endregion

#pragma region Camera
	// カメラを受け取る箱
	cCamera* camera_ = nullptr;
#pragma endregion

#pragma region 変換
	/*WVP用のリソース*/
	Microsoft::WRL::ComPtr<ID3D12Resource> transformationResource_ = nullptr;
	// シェーダーに送るトランスフォームデータ
	sTransformationMatrix* transformationData_ = nullptr;
	/*トランスフォーム*/
	cWorldTransform transform_;
	/*ビュープロジェクションを受け取る箱*/
	Matrix4x4* viewProjection_;
#pragma endregion

#pragma region PunctualLight
	// ライトを受け取る箱
	cPunctualLight punctualLight_{};
#pragma endregion


	std::string objectname_{};
};