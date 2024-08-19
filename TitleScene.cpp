// This
#include "TitleScene.h"

// ImGui
#include "externals/imgui/imgui.h"

// MyHedder
#include "Lazieal.h"
#include "Logger.h"
#include "SceneManager.h"

cTitleScene::cTitleScene() {
}

cTitleScene::~cTitleScene() {
}

void cTitleScene::Initialize() {
	// デバッグ用文字
	cLogger::Log("TitleScene,Initialized\n");

	// 共通初期化処理
	cBaseScene::Initialize();

#pragma region PunctualLight
	// ライト初期化
	punctualLightSetting_.Initialize();

	punctualLight_ = new cPunctualLight();
	punctualLight_->SetCameraPosition(*cLazieal::GetDefaultCamera()->GetWorldPos());
	punctualLight_->SetPunctualLightSetting(punctualLightSetting_.punctualLight);
	punctualLight_->Initialize();

#pragma endregion


#pragma region SoundData
	// 音声読み込み
	soundData = cLazieal::LoadSoundWave("Resources/Alarm01.wav");
#pragma endregion

}

void cTitleScene::Finalize() {
	// 共通終了処理
	cBaseScene::Finalize();

	// ライト開放
	delete punctualLight_;

	// サウンドのアンロード
	cLazieal::UnloadSound(&soundData);

	// デバッグ用文字
	cLogger::Log("TitleScene,Finalized\n");
}

void cTitleScene::Update() {

#pragma region ImGuiDebug

	ImGui::Begin("Sound");
	if (ImGui::Button("PlaySound")) {
		cLazieal::PlaySoundWave(soundData);
	}
	ImGui::End();


	ImGui::Begin("PunctualLightSetting");

	if (ImGui::BeginTabBar("DirectionalLight")) {
		if (ImGui::BeginTabItem("DirectionalLight")) {

			ImGui::ColorEdit4("Color", &punctualLightSetting_.punctualLight.directionalLight.color.x);
			ImGui::DragFloat3("Direction", &punctualLightSetting_.punctualLight.directionalLight.direction.x, 0.01f);
			punctualLightSetting_.punctualLight.directionalLight.direction = Normalize(punctualLightSetting_.punctualLight.directionalLight.direction);
			ImGui::DragFloat("intensity", &punctualLightSetting_.punctualLight.directionalLight.intensity, 0.01f);
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}

	if (ImGui::BeginTabBar("PointLight")) {
		if (ImGui::BeginTabItem("PointLight")) {

			ImGui::ColorEdit4("Color", &punctualLightSetting_.punctualLight.pointLight.color.x);
			ImGui::DragFloat3("Position", &punctualLightSetting_.punctualLight.pointLight.position.x, 0.01f);
			ImGui::DragFloat("intensity", &punctualLightSetting_.punctualLight.pointLight.intensity, 0.01f);
			ImGui::DragFloat("radius", &punctualLightSetting_.punctualLight.pointLight.radius, 0.01f);
			ImGui::DragFloat("decay", &punctualLightSetting_.punctualLight.pointLight.decay, 0.01f);
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}

	if (ImGui::BeginTabBar("SpotLight")) {
		if (ImGui::BeginTabItem("SpotLight")) {

			ImGui::ColorEdit4("Color", &punctualLightSetting_.punctualLight.spotLight.color.x);
			ImGui::DragFloat3("Position", &punctualLightSetting_.punctualLight.spotLight.position.x, 0.01f);
			ImGui::DragFloat("intensity", &punctualLightSetting_.punctualLight.spotLight.intensity, 0.01f);
			ImGui::DragFloat3("Direction", &punctualLightSetting_.punctualLight.spotLight.direction.x, 0.01f);
			punctualLightSetting_.punctualLight.spotLight.direction = Normalize(punctualLightSetting_.punctualLight.spotLight.direction);
			ImGui::DragFloat("distance", &punctualLightSetting_.punctualLight.spotLight.decay, 0.01f);
			ImGui::DragFloat("decay", &punctualLightSetting_.punctualLight.spotLight.distance, 0.01f);
			ImGui::DragFloat("cosFalloffStart", &punctualLightSetting_.punctualLight.spotLight.cosFalloffStart, 0.01f);
			ImGui::DragFloat("cosAngle", &punctualLightSetting_.punctualLight.spotLight.cosAngle, 0.01f);
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}


	ImGui::End();

#pragma endregion

#pragma region PunctualLight
	// ライトの更新
	punctualLight_->SetCameraPosition(*cLazieal::GetDefaultCamera()->GetWorldPos());
	punctualLight_->SetPunctualLightSetting(punctualLightSetting_.punctualLight);
	punctualLight_->Update();
#pragma endregion

#pragma region 3dObject
	
	

#pragma endregion

#pragma region 2dObject
	


#pragma endregion
}

void cTitleScene::Draw() {
	// 3Dオブジェクト描画前処理
	cLazieal::PreDrawObject3D();


	// UVなし3Dオブジェクト描画前処理
	cLazieal::PreDrawObject3DUnUV();

	


	// 2Dオブジェクト描画前処理
	cLazieal::PreDrawObject2D();

}

void cTitleScene::SwitchShowObjects() {
	ImGui::Begin("Objects");
	ImGui::Checkbox("teapot", &isShow[teapot]);
	ImGui::Checkbox("suzanne", &isShow[suzanne]);
	ImGui::Checkbox("multiMesh", &isShow[multiMesh]);
	ImGui::Checkbox("multiMaterial", &isShow[multiMaterial]);
	ImGui::Checkbox("bunny", &isShow[bunny]);
	ImGui::Checkbox("sphere", &isShow[sphere]);
	ImGui::End();
}
