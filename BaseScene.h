#pragma once

// 前方宣言
class cSceneManager;

// シーンの基底クラス
class cBaseScene {
public: // 仮想関数
	// 仮想デストラクタ
	virtual ~cBaseScene() = default;
	// 初期化
	virtual void Initialize() = 0;
	// 終了
	virtual void Finalize() = 0;
	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Draw() = 0;

	// シーンマネージャのセット
	virtual void SetSceneManager(cSceneManager* sceneManager) {
		sceneManager_ = sceneManager;
	}
private:
	// シーンマネージャ
	cSceneManager* sceneManager_ = nullptr;
};