// This
#include "SceneManager.h"

// MyHedder
#include "BaseScene.h"

cSceneManager::cSceneManager() {
}

cSceneManager::~cSceneManager() {
	// 最後のシーンの終了と解放
	currentScene_->Finalize();
	delete currentScene_;
}

void cSceneManager::Update() {
	// シーン切り替え処理
	SwitchScene();
	// 現在のシーンの更新処理
	currentScene_->Update();
	// 現在のシーンの描画処理
	currentScene_->Draw();
}

void cSceneManager::SwitchScene() {
	// 次シーンの予約があるなら
	if (nextScene_) {
		// 旧シーン終了
		if (currentScene_) {
			currentScene_->Finalize();
			delete currentScene_;
		}

		// シーン切り替え
		currentScene_ = nextScene_;
		nextScene_ = nullptr;
		// 次のシーンを初期化
		currentScene_->Initialize();
	}

}