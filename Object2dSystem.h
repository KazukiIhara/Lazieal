#pragma once

// 前方宣言
class cDirectXCommon;
class cPipelineManager;

class cObject2DSystem {
public: // インスタンスセット関数
	// DirectXCommon
	void SetDirectXCommon(cDirectXCommon* directX) {
		directX_ = directX;
	}
	// PipelineManager
	void SetPipelineManager(cPipelineManager* pipelineManager) {
		pipelineManager_ = pipelineManager;
	}
public: // 公開メンバ変数
	cObject2DSystem();
	~cObject2DSystem();

	// 描画前処理
	void PreDraw();

private: // インスタンスを受け取るポインタ
	// DirectXCommon
	cDirectXCommon* directX_ = nullptr;
	// PipelineManager
	cPipelineManager* pipelineManager_ = nullptr;

};

