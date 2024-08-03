#pragma once
// C++
#include <memory>

// MyHedder
#include "WorldTransform.h"
#include "MathFunction.h"

class cCamera {
public:
	// 初期化
	void Initialize(cWorldTransform* transform);

	// 更新
	void Update();

	// ビュープロジェクションマトリックスを送る関数
	Matrix4x4* GetViewProjectionMatrix() {
		return &viewProjectionMatrix_;
	}
	// ワールド行列を送る関数
	Matrix4x4* GetWorldMatrix() {
		return &worldMatrix_;
	}
	// ワールド座標を送る関数
	Vector3* GetWorldPos() {
		return &worldPos_;
	}

private:
	// カメラのトランスフォームを受け取る箱
	cWorldTransform* transform_{};
	// カメラのワールドマトリックス
	Matrix4x4 worldMatrix_{};
	// カメラのワールドポジション
	Vector3 worldPos_{};
	// ビュープロジェクションマトリックス
	Matrix4x4 viewProjectionMatrix_{};
	// 水平方向視野角
	float fovY_ = 0.45f;
	// アスペクト比
	float aspectRaito_ = 16.0f / 9.0f;
	// ニアクリップ距離
	float nearClipRange_ = 0.1f;
	// ファークリップ距離
	float farClipRange_ = 100.0f;
};
