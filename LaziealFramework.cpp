// This
#include "LaziealFramework.h"

// WinAPI
#include <Windows.h>

// MyHedder
#include "Logger.h"

void cLaziealFramework::Initialize() {
	// デバッグ用文字
	cLogger::Log("Lazieal,Initialized\n");
	// 初期化処理を実行
}

void cLaziealFramework::Finalize() {
	// デバッグ用文字出力
	cLogger::Log("Lazieal,Finalized\n");
	// 解放処理を実行

}

void cLaziealFramework::Update() {
	// 更新処理を実行

}

void cLaziealFramework::Draw() {
	// 描画処理を実行

}

void cLaziealFramework::Run() {
	// 初期化
	Initialize();
	// 更新
	Update();
	// 描画
	Draw();
	// 終了
	Finalize();
}
