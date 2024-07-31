// This
// This
#include "ImGuiManager.h"

// MyHedder
#include "WinAPI.h"
#include "DirectXCommon.h"
#include "SrvManager.h"

cImGuiManager::cImGuiManager() {
}

cImGuiManager::~cImGuiManager() {
}

void cImGuiManager::Initialize() {
	/*ImGuiの初期化*/
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(win_->GetHwnd());
	ImGui_ImplDX12_Init(directX_->GetDevice(),
		directX_->GetSwapChainDesc().BufferCount,
		directX_->GetRTVDesc().Format,
		srvManager_->GetDescriptorHeap(),
		srvManager_->GetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart(),
		srvManager_->GetDescriptorHeap()->GetGPUDescriptorHandleForHeapStart()
	);
	srvManager_->Allocate();
}

void cImGuiManager::BeginFrame() {
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void cImGuiManager::EndFrame() {
	// ImGui内部コマンドの生成
	ImGui::Render();
}

void cImGuiManager::Draw() {
	// 実際のCommandListのImGuiの描画コマンドを積む
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), directX_->GetCommandList());
}

void cImGuiManager::Finalize() {
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
