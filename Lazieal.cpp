// This
#include "Lazieal.h"

// WinAPI
#include <Windows.h>

// MyHedder
#include "Logger.h"
#include "WinAPI.h"
#include "DirectXCommon.h"
#include "SrvManager.h"
#include "ImGuiManager.h"
#include "TextureManager.h"
#include "AbstractSceneFactory.h"

// staticメンバ変数の初期化
cTextureManager* cLazieal::textureManager_ = nullptr;

void cLazieal::Initialize() {
	// デバッグ用文字
	cLogger::Log("Lazieal,Initialized\n");
	// 基底システムの初期化処理を実行

	// WinAPIの生成と初期化
	win_ = new cWinAPI();
	win_->Initialize();

	// DirectXCommonの生成
	directX_ = new cDirectXCommon();
	// WinAPIのインスタンスをセット
	directX_->SetWinAPI(win_);
	// DirectXCommonの初期化
	directX_->Initialize();

	// SrvManagerの生成
	srvManager_ = new cSrvManager();
	// DirectXのCommonインスタンスをセット
	srvManager_->SetDirectXCommon(directX_);
	srvManager_->Initialize();

	// ImGuiManagerの作成
	imguiManager_ = new cImGuiManager();
	// WinAPIのインスタンスをセット
	imguiManager_->SetWinAPI(win_);
	// DirectXのCommonインスタンスをセット
	imguiManager_->SetDirectXCommon(directX_);
	// SrvManagerのインスタンスをセット
	imguiManager_->SetSrvManager(srvManager_);
	// ImGuiManagerの初期化
	imguiManager_->Initialize();


	// TextureManagerの生成
	textureManager_ = new cTextureManager();
	// DirextXCommonのインスタンスをセット
	textureManager_->SetDirectXCommon(directX_);
	// SrvManagerのインスタンスをセット
	textureManager_->SetSrvManager(srvManager_);
	// TextureManagerの初期化
	textureManager_->Initialize();

}

void cLazieal::Finalize() {
	// デバッグ用文字出力
	cLogger::Log("Lazieal,Finalized\n");
	// 基底システムの解放処理を実行

	// シーンファクトリーを開放
	delete sceneFactory_;

	// TextureManagerの開放
	delete textureManager_;

	// ImGuiManagerの開放
	imguiManager_->Finalize();
	delete imguiManager_;

	// SrvManagerを開放
	delete srvManager_;

	// DirectXCommonを解放
	delete directX_;

	// WinAPIの終了と解放
	win_->Finalize();
	delete win_;
}

void cLazieal::Update() {
	// 基底システムの更新処理を実行

	// ウィンドウにメッセージが来ていたら最優先で処理
	if (win_->ProcessMessage()) {
		endRequest_ = true;
	}

	// ImGui開始処理
	imguiManager_->BeginFrame();

}

void cLazieal::Run() {
	// 初期化
	Initialize();
	// メインループ
	while (true) {
		// 更新
		Update();

		// 終了リクエストがあったらループを抜ける;
		if (IsEndRequest()) {
			break;
		}

		// 描画
		Draw();
	}

	// 終了
	Finalize();
}

void cLazieal::PreDraw() {
	// ImGui内部コマンド生成
	imguiManager_->EndFrame();
	// DirectX描画前処理
	directX_->PreDraw();
	// SrvManager描画前処理
	srvManager_->PreDraw();
}

void cLazieal::PostDraw() {
	// ImGui描画処理
	imguiManager_->Draw();
	// DirectX描画後処理
	directX_->PostDraw();
}

void cLazieal::LoadTexture(const std::string& filePath) {
	textureManager_->Load(filePath);
}
