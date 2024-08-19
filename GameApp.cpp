// This
#include "GameApp.h"

// MyHedder
#include "Logger.h"
#include "SceneFactory.h"
#include "SceneManager.h"

cGameApp::cGameApp() {
}

cGameApp::~cGameApp() {
}

void cGameApp::Initialize() {
	// 基底システムの初期化
	cLazieal::Initialize();

	// シーンファクトリ生成
	sceneFactory_ = new cSceneFactory();

	// シーンマネージャにシーンファクトリをセット
	cLazieal::SetSceneFactory(sceneFactory_);
	// 初期シーンのセット
	cLazieal::ChangeScene("TITLE");
}

void cGameApp::Finalize() {
	// 基底システムの終了
	cLazieal::Finalize();
}

void cGameApp::Update() {
	// 基底システムの更新
	cLazieal::Update();
	// シーンの更新処理
	cLazieal::UpdateScene();
}

void cGameApp::Draw() {
	// 基底システムの描画後処理
	cLazieal::PreDraw();
	// シーンの描画処理
	cLazieal::DrawScene();
	// 基底システムの描画後処理
	cLazieal::PostDraw();
}
