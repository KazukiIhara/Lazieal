#pragma once

// MyHedder
#include "Camera.h"

// 前方宣言
class cDirectXCommon;
class cPipelineManager;

class cObject3dSystem {
public: // インスタンスセット関数
	// DirectXCommon
	void SetDirectXCommon(cDirectXCommon* directX) {
		directX_ = directX;
	}
	// PipelineManager
	void SetPipelineManager(cPipelineManager* pipelineManager) {
		pipelineManager_ = pipelineManager;
	}

public: // 公開メンバ関数
	cObject3dSystem();
	~cObject3dSystem();

	// 描画前処理
	void PreDraw();

	// UVなし描画前処理
	void PreDrawUnUV();

	// デフォルトカメラを取得
	cCamera* GetDefaultCamera()const {
		return defaultCamera_;
	}
	// デフォルトカメラをセット
	void SetDefaultCamera(cCamera* camera) {
		defaultCamera_ = camera;
	}

private: // インスタンスを受け取るポインタ
	// DirectXCommon
	cDirectXCommon* directX_ = nullptr;
	// PipelineManager
	cPipelineManager* pipelineManager_ = nullptr;

private: // 非公開メンバ変数
	// デフォルトカメラ
	cCamera* defaultCamera_ = nullptr;
};