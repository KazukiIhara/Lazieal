// This
#include "LaziealFramework.h"

// WinAPI
#include <Windows.h>

// MyHedder
#include "Logger.h"
#include "WinAPI.h"
#include "AbstractSceneFactory.h"

void cLaziealFramework::Initialize() {
	// デバッグ用文字
	cLogger::Log("Lazieal,Initialized\n");
	// 基底システムの初期化処理を実行

	// WinAPIの生成と初期化
	win_ = new cWinAPI();
	win_->Initialize();

}

void cLaziealFramework::Finalize() {
	// デバッグ用文字出力
	cLogger::Log("Lazieal,Finalized\n");
	// 基底システムの解放処理を実行

	// シーンファクトリーを開放
	delete sceneFactory_;

	// WinAPIの終了と解放
	win_->Finalize();
	delete win_;
}

void cLaziealFramework::Update() {
	// デバッグ用文字出力
	cLogger::Log("Lazieal,Update\n");
	// 基底システムの更新処理を実行

	// ウィンドウにメッセージが来ていたら最優先で処理
	if (win_->ProcessMessage()) {
		endRequest_ = true;
	}
}

void cLaziealFramework::Run() {
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
