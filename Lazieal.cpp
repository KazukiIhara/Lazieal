// This
#include "Lazieal.h"

// WinAPI
#include <Windows.h>

void cLazieal::Initialize() {
	// デバッグ用文字
	OutputDebugStringA("Lazieal,Initialized\n");
	// 初期化処理を実行
}

void cLazieal::Finalize() {
	// デバッグ用文字出力
	OutputDebugStringA("Lazieal,Finalized\n");
	// 解放処理を実行

}

void cLazieal::Update() {
	// 更新処理を実行

}

void cLazieal::Draw() {
	// 描画処理を実行

}

void cLazieal::Run() {
	// 初期化
	Initialize();
	// 更新
	Update();
	// 描画
	Draw();
	// 終了
	Finalize();
}
