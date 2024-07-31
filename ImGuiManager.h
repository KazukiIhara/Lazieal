#pragma once

// WindowsAPI
#include <Windows.h>

// imgui
#include "externals/imgui/imgui.h"
#include "externals/imgui/imgui_impl_dx12.h"
#include "externals/imgui/imgui_impl_win32.h"

// 前方宣言
class cWinAPI;
class cDirectXCommon;
class cSrvManager;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam
);

// imguiマネージャ
class cImGuiManager {
public: // インスタンスセット関数
	void SetWinAPI(cWinAPI* win) {
		win_ = win;
	}
	void SetDirectXCommon(cDirectXCommon* directX) {
		directX_ = directX;
	}
	void SetSrvManager(cSrvManager* srvManager) {
		srvManager_ = srvManager;
	}
public: // 公開メンバ関数
	cImGuiManager();
	~cImGuiManager();

	// 初期化
	void Initialize();

	// 更新処理の先頭に呼び出す処理
	void BeginFrame();

	// 更新処理の最後に呼び出す処理
	void EndFrame();

	// 描画
	void Draw();

	// ImGuiの終了処理
	void Finalize();

private: // インスタンスを受け取る変数
	// WinAPI
	cWinAPI* win_ = nullptr;
	// DirectXCommon
	cDirectXCommon* directX_ = nullptr;
	// SrvManager
	cSrvManager* srvManager_ = nullptr;
};

