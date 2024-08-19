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
#include "SoundManager.h"
#include "ModelManager.h"
#include "SceneManager.h"
#include "Camera.h"
#include "Object3dSystem.h"
#include "Object2dSystem.h"
#include "Object3d.h"
#include "Sprite.h"
#include "AbstractSceneFactory.h"

// staticメンバ変数の初期化
cDirectXCommon* cLazieal::directX_ = nullptr;
cSrvManager* cLazieal::srvManager_ = nullptr;
cTextureManager* cLazieal::textureManager_ = nullptr;
cPipelineManager* cLazieal::pipelineManager_ = nullptr;
cSoundManager* cLazieal::soundManager_ = nullptr;
cModelManager* cLazieal::modelManager_ = nullptr;
cSceneManager* cLazieal::sceneManager_ = nullptr;
cObject3dSystem* cLazieal::object3dSystem_ = nullptr;
cObject2DSystem* cLazieal::object2dSystem_ = nullptr;

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

#pragma region SoundManager
	// SoundManagerの生成
	soundManager_ = new cSoundManager();
#pragma endregion

#pragma region ModelManager
	// ModelManagerの生成
	modelManager_ = new cModelManager();
	// ModelManagerの初期化
	modelManager_->Initialize();
#pragma endregion

#pragma region SceneManager
	// SceneManagerの生成
	sceneManager_ = new cSceneManager();
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

#pragma region Object2dSystem
	// Object2dSystemの生成
	object2dSystem_ = new cObject2DSystem();
	// DirectXCommonのインスタンスをセット
	object2dSystem_->SetDirectXCommon(directX_);
	// GraphicsPipelineManagerのインスタンスをセット
	object2dSystem_->SetPipelineManager(pipelineManager_);
#pragma endregion

}

void cLazieal::Finalize() {
	// デバッグ用文字出力
	cLogger::Log("Lazieal,Finalized\n");
	// 基底システムの解放処理を実行

	// SceneManagerを解放
	delete sceneManager_;

	// シーンファクトリーを開放
	delete sceneFactory_;

	// Object3dSystemの解放
	delete object3dSystem_;

	// DebugCameraの開放
	delete debugCamera_;

	// ModelManagerの終了と開放
	modelManager_->Finalize();
	delete modelManager_;

	// SoundManagerの解放
	delete soundManager_;

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

#pragma region ImGuiDebugCamera
	ImGui::SetNextWindowSize(ImVec2(400.0f, 80.0f));
	ImGui::Begin("DebugCamera");
	ImGui::DragFloat3("Rotate", &debugCameraTransform_.rotate.x, 0.001f);
	ImGui::DragFloat3("Translate", &debugCameraTransform_.translate.x, 0.01f);
	ImGui::End();
#pragma endregion

	// デバッグカメラの更新
	debugCamera_->Update();

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

const DirectX::TexMetadata& cLazieal::GetTextureMetaData(const std::string& filePath) {
	return textureManager_->GetMetaData(filePath);
}

ID3D12PipelineState* cLazieal::GetPipelineState(cPipelineManager::ePipelineState pipelineState, cPipelineManager::eBlendMode blendMode) {
	return pipelineManager_->GetPipelineState(pipelineState, blendMode);
}

void cLazieal::InitializeSoundManager() {
	soundManager_->Initialize();
}

void cLazieal::FinalizeSoundManager() {
	soundManager_->Finalize();
}

cSoundManager::SoundData cLazieal::LoadSoundWave(const char* fileName) {
	return soundManager_->SoundLoadWave(fileName);
}

void cLazieal::UnloadSound(cSoundManager::SoundData* soundData) {
	soundManager_->SoundUnload(soundData);
}

void cLazieal::PlaySoundWave(const cSoundManager::SoundData& soundData) {
	soundManager_->SoundPlayWave(soundData);
}

void cLazieal::LoadModel(const std::string& filePath) {
	modelManager_->Load(filePath);
}

void cLazieal::CreateSphere(const std::string& textureFilePath) {
	modelManager_->CreateSphere(textureFilePath);
}

cModel* cLazieal::FindModel(const std::string& filePath) {
	return modelManager_->Find(filePath);
}

void cLazieal::SetSceneFactory(cAbstractSceneFactory* sceneFactory) {
	sceneManager_->SetSceneFactory(sceneFactory);
}

void cLazieal::ChangeScene(const std::string& sceneName) {
	sceneManager_->ChangeScene(sceneName);
}

void cLazieal::UpdateScene() {
	sceneManager_->Update();
}

void cLazieal::DrawScene() {
	sceneManager_->Draw();
}

void cLazieal::PreDrawObject3D() {
	object3dSystem_->PreDraw();
}

void cLazieal::PreDrawObject3DUnUV() {
	object3dSystem_->PreDrawUnUV();
}

cCamera* cLazieal::GetDefaultCamera() {
	return object3dSystem_->GetDefaultCamera();
}

void cLazieal::PreDrawObject2D() {
	object2dSystem_->PreDraw();
}

void cLazieal::ImGuiDebug3dObject(cWorldTransform& transform, cObject3D* object3d) {
	// デバッグ用UIを表示
	ImGui::Begin(object3d->GetName().c_str());

	// Transform
	if (ImGui::BeginTabBar("Transform")) {
		if (ImGui::BeginTabItem("Transform")) {

			ImGui::DragFloat3("scale", &transform.scale.x, 0.01f);
			ImGui::DragFloat3("rotate", &transform.rotate.x, 0.003f);
			ImGui::DragFloat3("translate", &transform.translate.x, 0.01f);
			object3d->SetTransform(transform);

			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}

	// Material
	std::vector<sMaterial3D> materials = object3d->GetModel()->GetMaterials();
	// UvTransform　Matrixがマテリアルの中に含まれているが、行列の計算をModelクラス内で行うため別途送る
	std::vector<sUVTransform> uvTransform = object3d->GetModel()->GetUVTransforms();

	if (ImGui::BeginTabBar("Material")) {
		for (size_t i = 0; i < materials.size(); ++i) {
			std::string label = "Material " + std::to_string(i + 1);

			if (ImGui::BeginTabItem(label.c_str())) {
				label = "color " + std::to_string(i + 1);
				ImGui::ColorEdit4(label.c_str(), &materials[i].color.x);

				label = "enableLighting " + std::to_string(i + 1);
				ImGui::Checkbox(label.c_str(), reinterpret_cast<bool*>(&materials[i].enbleLighting));

				label = "UVScale " + std::to_string(i + 1);
				ImGui::DragFloat2(label.c_str(), &uvTransform[i].scale.x, 0.01f);

				label = "UVRotateZ " + std::to_string(i + 1);
				ImGui::DragFloat(label.c_str(), &uvTransform[i].rotateZ, 0.01f);

				label = "UVTranslate " + std::to_string(i + 1);
				ImGui::DragFloat2(label.c_str(), &uvTransform[i].translate.x, 0.01f);

				label = "shininess " + std::to_string(i + 1);
				ImGui::DragFloat(label.c_str(), &materials[i].shininess, 1.0f);


				ImGui::EndTabItem();
			}
		}
		ImGui::EndTabBar();

	}

	object3d->GetModel()->SetMaterials(materials);
	object3d->GetModel()->SetUVTransform(uvTransform);

	ImGui::End();
}

void cLazieal::ImGuiDebug2dSprite(sTransform2D& transform, sUVTransform& uvTransform, cSprite* sprite) {
	// Transform
	ImGui::Begin(sprite->GetTextureFilePath().c_str());
	ImGui::DragFloat2("Size", &transform.size.x, 1.0f);
	ImGui::DragFloat("Rotate", &transform.rotate, 0.01f);
	ImGui::DragFloat2("Position", &transform.position.x, 1.0f);

	// UvTransform
	ImGui::DragFloat2("uvScale", &uvTransform.scale.x, 0.01f);
	ImGui::DragFloat("uvRotate", &uvTransform.rotateZ, 0.01f);
	ImGui::DragFloat2("uvTranslate", &uvTransform.translate.x, 0.01f);

	sprite->SetTransform(transform);

	sprite->SetUVTransform(uvTransform);
	ImGui::End();

}
