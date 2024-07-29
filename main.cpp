// WinAPI
#include <Windows.h>

// C++
#include <memory>

// MyHedder
#include "LaziealFramework.h"
#include "GameApp.h"
#include "Logger.h"

// エントリーポイント
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	// 開始時デバッグ用文字
	cLogger::Log("Hello,Lazieal!\n");

	// フレームワークを動的確保
	std::unique_ptr<cLaziealFramework> game = std::make_unique<cGameApp>();

	// 実行
	game->Run();

	// 終了時デバッグ用文字
	cLogger::Log("Bye,Lazieal!\n");

	// 無事終了
	return 0;
}