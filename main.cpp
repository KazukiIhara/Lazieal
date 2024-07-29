// WinAPI
#include <Windows.h>

// C++
#include <memory>

// MyHedder
#include "Lazieal.h"

// エントリーポイント
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// デバッグ用文字
	OutputDebugStringA("Hello,Lazieal!\n");

	std::unique_ptr<cLazieal> lazieal = std::make_unique<cLazieal>();
	lazieal->Run();

	// 無事終了
	return 0;
}