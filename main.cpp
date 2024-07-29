// WinAPI
#include <Windows.h>

// C++
#include <memory>

// MyHedder
#include "LaziealFramework.h"

// エントリーポイント
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	// 開始時デバッグ用文字
	OutputDebugStringA("Hello,Lazieal!\n");

	// フレームワークを動的確保
	std::unique_ptr<cLaziealFramework> lazieal = std::make_unique<cLaziealFramework>();

	// 実行
	lazieal->Run();

	// 終了時デバッグ用文字
	OutputDebugStringA("Bye,Lazieal!\n");

	// 無事終了
	return 0;
}