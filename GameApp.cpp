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
	// シーンマネージャ作成
	sceneManager_ = new cSceneManager();
	// シーンマネージャにシーンファクトリをセット
	sceneManager_->SetSceneFactory(sceneFactory_);
	// 初期シーンのセット
	sceneManager_->ChangeScene("TITLE");
}

void cGameApp::Finalize() {
	// ゲーム固有の終了処理
	delete sceneManager_;
	// 基底システムの終了
	cLazieal::Finalize();
}

void cGameApp::Update() {
	// 基底システムの更新
	cLazieal::Update();
	// シーンの更新処理
	sceneManager_->Update();
}

void cGameApp::Draw() {
	// 基底システムの描画後処理
	cLazieal::PreDraw();
	// シーンの描画処理
	sceneManager_->Draw();
	// 基底システムの描画後処理
	cLazieal::PostDraw();
}
