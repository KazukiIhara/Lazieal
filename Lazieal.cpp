// This
#include "Lazieal.h"

// WinAPI
#include <Windows.h>

// MyHedder
#include "Logger.h"
#include "WinAPI.h"
#include "DirectXCommon.h"
#include "SrvManager.h"
#include "ImGuiManager.h"
#include "TextureManager.h"
#include "PipelineManager.h"
#include "ModelManager.h"
#include "Camera.h"
#include "Object3dSystem.h"
#include "AbstractSceneFactory.h"

// staticメンバ変数の初期化
cDirectXCommon* cLazieal::directX_ = nullptr;
cSrvManager* cLazieal::srvManager_ = nullptr;
cTextureManager* cLazieal::textureManager_ = nullptr;
cPipelineManager* cLazieal::pipelineManager_ = nullptr;
cModelManager* cLazieal::modelManager_ = nullptr;
cObject3dSystem* cLazieal::object3dSystem_ = nullptr;

void cLazieal::Initialize() {
	// デバッグ用文字
	cLogger::Log("Lazieal,Initialized\n");
	// 基底システムの初期化処理を実行

#pragma region WinAPI
	// WinAPIの生成と初期化
	win_ = new cWinAPI();
	win_->Initialize();
#pragma endregion

#pragma region DirectXCommon
	// DirectXCommonの生成
	directX_ = new cDirectXCommon();
	// WinAPIのインスタンスをセット
	directX_->SetWinAPI(win_);
	// DirectXCommonの初期化
	directX_->Initialize();
#pragma endregion

#pragma region SrvManager
	// SrvManagerの生成
	srvManager_ = new cSrvManager();
	// DirectXのCommonインスタンスをセット
	srvManager_->SetDirectXCommon(directX_);
	srvManager_->Initialize();
#pragma endregion

#pragma region ImGuiManager
	// ImGuiManagerの作成
	imguiManager_ = new cImGuiManager();
	// WinAPIのインスタンスをセット
	imguiManager_->SetWinAPI(win_);
	// DirectXのCommonインスタンスをセット
	imguiManager_->SetDirectXCommon(directX_);
	// SrvManagerのインスタンスをセット
	imguiManager_->SetSrvManager(srvManager_);
	// ImGuiManagerの初期化
	imguiManager_->Initialize();
#pragma endregion

#pragma region TextureManager
	// TextureManagerの生成
	textureManager_ = new cTextureManager();
	// DirextXCommonのインスタンスをセット
	textureManager_->SetDirectXCommon(directX_);
	// SrvManagerのインスタンスをセット
	textureManager_->SetSrvManager(srvManager_);
	// TextureManagerの初期化
	textureManager_->Initialize();
#pragma endregion

#pragma region GraphicsPipelineManager
	// GraphicsPipelineManagerの生成
	pipelineManager_ = new cPipelineManager();
	// DirectXCommonのインスタンスをセット
	pipelineManager_->SetDirectXCommon(directX_);
	// GraphicsPipelineManagerの初期化
	pipelineManager_->Initialize();
#pragma endregion

#pragma region ModelManager
	// ModelManagerの生成
	modelManager_ = new cModelManager();
	// ModelManagerの初期化
	modelManager_->Initialize();
#pragma endregion

#pragma region DebugCamera
	// DebugCameraを生成
	debugCamera_ = new cCamera();
	// DebugCameraのトランスフォームを初期化
	debugCameraTransform_.Initialize();
	// DebugCameraを初期化
	debugCamera_->Initialize(&debugCameraTransform_);
#pragma endregion

#pragma region Object3dSystem
	// Object3dSystemの生成
	object3dSystem_ = new cObject3dSystem();
	// DirectXCommonのインスタンスをセット
	object3dSystem_->SetDirectXCommon(directX_);
	// GraphicsPipelineManagerのインスタンスをセット
	object3dSystem_->SetPipelineManager(pipelineManager_);
	// デフォルトカメラをセット
	object3dSystem_->SetDefaultCamera(debugCamera_);
#pragma endregion

}

void cLazieal::Finalize() {
	// デバッグ用文字出力
	cLogger::Log("Lazieal,Finalized\n");
	// 基底システムの解放処理を実行

	// シーンファクトリーを開放
	delete sceneFactory_;

	// Object3dSystemの解放
	delete object3dSystem_;

	// DebugCameraの開放
	delete debugCamera_;

	// ModelManagerの終了と開放
	modelManager_->Finalize();
	delete modelManager_;

	// PipelineManagerの解放
	delete pipelineManager_;

	// TextureManagerの開放
	delete textureManager_;

	// ImGuiManagerの終了と開放
	imguiManager_->Finalize();
	delete imguiManager_;

	// SrvManagerを開放
	delete srvManager_;

	// DirectXCommonを解放
	delete directX_;

	// WinAPIの終了と解放
	win_->Finalize();
	delete win_;
}

void cLazieal::Update() {
	// 基底システムの更新処理を実行

	// ウィンドウにメッセージが来ていたら最優先で処理
	if (win_->ProcessMessage()) {
		endRequest_ = true;
	}

	// ImGui開始処理
	imguiManager_->BeginFrame();

}

void cLazieal::Run() {
	// 初期化
	Initialize();
	// メインループ
	while (true) {
		// 更新
		Update();

		// 終了リクエストがあったらループを抜ける;
		if (IsEndRequest()) {
			break;
		}

		// 描画
		Draw();
	}

	// 終了
	Finalize();
}

void cLazieal::PreDraw() {
	// ImGui内部コマンド生成
	imguiManager_->EndFrame();
	// DirectX描画前処理
	directX_->PreDraw();
	// SrvManager描画前処理
	srvManager_->PreDraw();
}

void cLazieal::PostDraw() {
	// ImGui描画処理
	imguiManager_->Draw();
	// DirectX描画後処理
	directX_->PostDraw();
}

ID3D12Device* cLazieal::GetDirectXDevice() {
	return directX_->GetDevice();
}

ID3D12GraphicsCommandList* cLazieal::GetDirectXCommandList() {
	return directX_->GetCommandList();
}

void cLazieal::SetGraphicsRootDescriptorTable(UINT rootParameterIndex, uint32_t srvIndex) {
	srvManager_->SetGraphicsRootDescriptorTable(rootParameterIndex, srvIndex);
}

void cLazieal::LoadTexture(const std::string& filePath) {
	textureManager_->Load(filePath);
}

std::unordered_map<std::string, cTextureManager::Texture>& cLazieal::GetTexture() {
	return textureManager_->GetTexture();
}

ID3D12PipelineState* cLazieal::GetPipelineState(cPipelineManager::ePipelineState pipelineState, cPipelineManager::eBlendMode blendMode) {
	return pipelineManager_->GetPipelineState(pipelineState, blendMode);
}

void cLazieal::LoadModel(const std::string& filePath) {
	modelManager_->Load(filePath);
}

cModel* cLazieal::FindModel(const std::string& filePath) {
	return modelManager_->Find(filePath);
}

void cLazieal::PreDrawObject3D() {
	object3dSystem_->PreDraw();
}

cCamera* cLazieal::GetDefaultCamera() {
	return object3dSystem_->GetDefaultCamera();
}
