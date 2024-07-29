// WinAPI
#include <Windows.h>

// C++
#include <memory>

// MyHedder
#include "Lazieal.h"

// エントリーポイント
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	// 開始時デバッグ用文字
	OutputDebugStringA("Hello,Lazieal!\n");

	std::unique_ptr<cLazieal> lazieal = std::make_unique<cLazieal>();
	lazieal->Run();

	// 終了字デバッグ用文字
	OutputDebugStringA("Bye,Lazieal!\n");

	// 無事終了
	return 0;
}