// WinAPI
#include <Windows.h>

// C++
#include <memory>

// MyHedder

#include "Lazieal.h"
#include "GameApp.h"
#include "Logger.h"

#ifdef _DEBUG
#include "D3DResourceLeakChecker.h"
#endif // DEBUG

// エントリーポイント
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	// 開始時デバッグ用文字
	cLogger::Log("Hello,Lazieal!\n");

#ifdef _DEBUG
	// リークチェッカのインスタンスを最初に取得
	D3DResourceLeakChecker* leakCheck = D3DResourceLeakChecker::GetInstance();
#endif // DEBUG

	// フレームワークを動的確保
	std::unique_ptr<cLazieal> game = std::make_unique<cGameApp>();

	// 実行
	game->Run();

	// 終了時デバッグ用文字
	cLogger::Log("Bye,Lazieal!\n");

	// 無事終了
	return 0;
}