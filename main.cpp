#include <Windows.h>
#include <memory>
#include "DirectXCommon.h"
#include "SceneManager.h"

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dxcompiler.lib")

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	CoInitializeEx(0, COINIT_MULTITHREADED);

	/*リークチェッカC++環境ならSingltonもチェックしてくれるはず*/
	D3DResourceLeakChecker* leakCheck = nullptr;
	leakCheck = D3DResourceLeakChecker::GetInstance();

	/*ゲーム*/
	std::unique_ptr<cSceneManager> game = std::make_unique<cSceneManager>();

	/*実行*/
	game->Run();

	CoUninitialize();

	/*終わり*/
	return 0;
}