#pragma once

// c++
#include <string>

// MyHedder
#include "AbstractSceneFactory.h"

// 前方宣言
class cBaseScene;

// シーン管理クラス
class cSceneManager {
public: // メンバ関数
	cSceneManager();
	~cSceneManager();

	// 更新
	void Update();
	// 描画
	void Draw();

	// シーン変更処理
	void SwitchScene();

	// 次のシーンを指定
	void ChangeScene(const std::string& sceneName);

	// シーンファクトリのセッター
	void SetSceneFactory(cAbstractSceneFactory* sceneFactory) {
		sceneFactory_ = sceneFactory;
	};

private:
	// 現在のシーン
	cBaseScene* currentScene_ = nullptr;
	// 次のシーン
	cBaseScene* nextScene_ = nullptr;

	// シーンファクトリ(借りてくる)
	cAbstractSceneFactory* sceneFactory_ = nullptr;
};