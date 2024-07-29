// This
#include "SceneFactory.h"

// MyHedder
#include "TitleScene.h"

cBaseScene* cSceneFactory::CreateScene(const std::string& sceneName) {
	// 次のシーンを生成
	cBaseScene* newScene = nullptr;

	// タイトルシーン
	if (sceneName == "TITLE") {
		newScene = new cTitleScene();
	}

	return newScene;
}
