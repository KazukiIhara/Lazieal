#pragma once

// C++
#include <cmath>
#include <numbers>

// MyHedder
#include "MathFunction.h"

// ワールドトランスフォームクラス
class cWorldTransform {
public: // メンバ関数
	cWorldTransform() = default;
	~cWorldTransform() = default;

	// 初期化
	void Initialize();
	// 更新
	void Update();

private: // コピー禁止
	// コピー禁止
	cWorldTransform(const cWorldTransform&) = delete;
	cWorldTransform& operator=(const cWorldTransform&) = delete;

public: // メンバ変数
	// ローカルトランスフォーム
	Vector3 scale = { 1.0f,1.0f,1.0f };// 拡縮量
	Vector3 rotate = { 0.0f,0.0f,0.0f };// 回転量
	Vector3 translate = { 0.0f,0.0f,0.0f };// 移動量

	// ワールド行列
	Matrix4x4 worldMatrix_{};
};
