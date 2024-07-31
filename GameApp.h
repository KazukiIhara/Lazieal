#pragma once

// MyHedder
#include "Lazieal.h"

// 前方宣言
class cSceneFactory;
class cSceneManager;

// ゲームクラス
class cGameApp :public cLazieal {
public: // 公開メンバ関数
	cGameApp();
	~cGameApp();

	// 初期化
	void Initialize()override;
	// 終了
	void Finalize()override;
	// 更新
	void Update()override;
	// 描画
	void Draw()override;

private: // メンバ変数
	// シーンファクトリ
	cSceneFactory* sceneFactory_ = nullptr;
	// シーンマネージャ
	cSceneManager* sceneManager_ = nullptr;
};