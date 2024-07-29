#pragma once

// 前方宣言
class cBaseScene;

// シーン管理クラス
class cSceneManager {
public: // メンバ関数
	cSceneManager();
	~cSceneManager();

	// 更新
	void Update();
	// シーン変更処理
	void SwitchScene();

	// 次のシーンをセット
	void SetNextScene(cBaseScene* nextScene) { nextScene_ = nextScene; }
private:
	// 現在のシーン
	cBaseScene* currentScene_ = nullptr;
	// 次のシーン
	cBaseScene* nextScene_ = nullptr;
};