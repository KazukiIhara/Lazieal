// This
#include "TitleScene.h"

// ImGui
#include "externals/imgui/imgui.h"

// MyHedder
#include "Lazieal.h"
#include "Logger.h"

cTitleScene::cTitleScene() {
}

cTitleScene::~cTitleScene() {
}

void cTitleScene::Initialize() {
	// デバッグ用文字
	cLogger::Log("TitleScene,Initialized\n");

	// 各シーンの先頭でサウンドマネージャを初期化
	cLazieal::InitializeSoundManager();

#pragma region PunctualLight
	// ライト初期化
	punctualLightSetting_.Initialize();

	punctualLight_ = new cPunctualLight();
	punctualLight_->SetCameraPosition(*cLazieal::GetDefaultCamera()->GetWorldPos());
	punctualLight_->SetPunctualLightSetting(punctualLightSetting_.punctualLight);
	punctualLight_->Initialize();

#pragma endregion

#pragma region Teapot
	// モデル読み込み
	cLazieal::LoadModel("teapot");

	// ティーポットのトランスフォーム
	teapotTransform_.Initialize();
	teapotTransform_.translate = { 0.0f,0.0f,10.0f };
	teapotTransform_.rotate = { 0.0f,1.0f,0.0f };

	// ティーポット初期化
	teapot_ = new cObject3D();
	teapot_->Initialize();
	teapot_->SetPunctualLight(punctualLight_);
	teapot_->SetModel("teapot");
	teapot_->SetTranslate(teapotTransform_.translate);
	teapot_->SetRotate(teapotTransform_.rotate);

#pragma endregion

#pragma region suzanne
	// モデル読み込み
	cLazieal::LoadModel("suzanne");

	// スザンヌのトランスフォーム
	suzanneTransform_.Initialize();
	suzanneTransform_.translate = { 0.0f,0.0f,10.0f };
	suzanneTransform_.rotate = { 0.0f,1.0f,0.0f };

	// スザンヌ初期化
	suzanne_ = new cObject3D();
	suzanne_->Initialize();
	suzanne_->SetModel("suzanne");
	suzanne_->SetPunctualLight(punctualLight_);
	suzanne_->SetTranslate(suzanneTransform_.translate);
	suzanne_->SetRotate(suzanneTransform_.rotate);

#pragma endregion

#pragma region MultiMesh
	// モデル読み込み
	cLazieal::LoadModel("multiMesh");

	// マルチマテリアルのトランスフォーム
	multiMeshTransform_.Initialize();
	multiMeshTransform_.translate = { 0.0f,0.0f,10.0f };
	multiMeshTransform_.rotate = { 0.0f,1.0f,0.0f };

	// マルチマテリアル初期化
	multiMesh_ = new cObject3D();
	multiMesh_->Initialize();
	multiMesh_->SetPunctualLight(punctualLight_);
	multiMesh_->SetModel("multiMesh");
	multiMesh_->SetTransform(multiMeshTransform_);

#pragma endregion

#pragma region MultiMaterial
	// モデル読み込み
	cLazieal::LoadModel("multiMaterial");

	// マルチマテリアルのトランスフォーム
	multiMaterialTransform_.Initialize();
	multiMaterialTransform_.translate = { 0.0f,0.0f,10.0f };
	multiMaterialTransform_.rotate = { 0.0f,1.0f,0.0f };

	// マルチマテリアル初期化
	multiMaterial_ = new cObject3D();
	multiMaterial_->Initialize();
	multiMaterial_->SetPunctualLight(punctualLight_);
	multiMaterial_->SetModel("multiMaterial");
	multiMaterial_->SetTransform(multiMaterialTransform_);

#pragma endregion

#pragma region Bunny
	cLazieal::LoadModel("bunny");

	// バニーのトランスフォーム
	bunnyTransform_.Initialize();
	bunnyTransform_.translate = { 0.0f,0.0f,10.0f };
	bunnyTransform_.rotate = { 0.0f, 1.0f, 0.0f };

	bunny_ = new cObject3D();
	bunny_->Initialize();
	bunny_->SetPunctualLight(punctualLight_);
	bunny_->SetModel("bunny");
	bunny_->SetTransform(bunnyTransform_);

#pragma endregion

#pragma region Sphere
	cLazieal::CreateSphere("uvChecker.png");

	// スフィアのトランスフォーム
	sphereTransform_.Initialize();
	sphereTransform_.translate = { 0.0f,0.0f,10.0f };

	sphere_ = new cObject3D();
	sphere_->Initialize();
	sphere_->SetPunctualLight(punctualLight_);
	sphere_->SetModel("Sphere_uvChecker.png");
	sphere_->SetTransform(sphereTransform_);

#pragma endregion

#pragma region uvChecker
	uvCheckerUVTransform_ = { { 1.0f,1.0f }, 0.0f, { 0.0f,0.0f } };
	uvChecker_ = new cSprite();
	uvChecker_->Initialize("Resources/uvChecker.png");
	uvCheckerTransform_ = uvChecker_->GetTransform();
#pragma endregion

#pragma region SoundData
	// 音声読み込み
	soundData = cLazieal::LoadSoundWave("Resources/Alarm01.wav");
#pragma endregion

}

void cTitleScene::Finalize() {
	// デバッグ用文字
	cLogger::Log("TitleScene,Finalized\n");

	delete punctualLight_;

	delete teapot_;
	delete suzanne_;
	delete multiMesh_;
	delete multiMaterial_;
	delete bunny_;
	delete sphere_;

	delete uvChecker_;

	// 音声データを解放する前にサウンドマネージャの終了処理
	cLazieal::FinalizeSoundManager();
	cLazieal::UnloadSound(&soundData);
}

void cTitleScene::Update() {

#pragma region ImGuiDebug

	ImGui::Begin("Sound");
	if (ImGui::Button("PlaySound")) {
		cLazieal::PlaySoundWave(soundData);
	}
	ImGui::End();

	// オブジェクトの表示切替
	SwitchShowObjects();

	if (isShow[teapot]) {
		cLazieal::ImGuiDebug3dObject(teapotTransform_, teapot_);
	}
	if (isShow[multiMesh]) {
		cLazieal::ImGuiDebug3dObject(multiMeshTransform_, multiMesh_);
	}
	if (isShow[multiMaterial]) {
		cLazieal::ImGuiDebug3dObject(multiMaterialTransform_, multiMaterial_);
	}
	if (isShow[suzanne]) {
		cLazieal::ImGuiDebug3dObject(suzanneTransform_, suzanne_);
	}
	if (isShow[bunny]) {
		cLazieal::ImGuiDebug3dObject(bunnyTransform_, bunny_);
	}
	if (isShow[sphere]) {
		cLazieal::ImGuiDebug3dObject(sphereTransform_, sphere_);
	}

	ImGui::Begin("Sprite");
	ImGui::DragFloat2("Size", &uvCheckerTransform_.size.x, 0.01f);
	ImGui::DragFloat("Rotate", &uvCheckerTransform_.rotate, 0.01f);
	ImGui::DragFloat2("Position", &uvCheckerTransform_.position.x, 1.0f);

	ImGui::DragFloat2("uvScale", &uvCheckerUVTransform_.scale.x, 0.01f);
	ImGui::DragFloat("uvRotate", &uvCheckerUVTransform_.rotateZ, 0.01f);
	ImGui::DragFloat2("uvTranslate", &uvCheckerUVTransform_.translate.x, 0.01f);

	uvChecker_->SetSize(uvCheckerTransform_.size);
	uvChecker_->SetRotation(uvCheckerTransform_.rotate);
	uvChecker_->SetPosition(uvCheckerTransform_.position);
	uvChecker_->SetUVTransform(uvCheckerUVTransform_);
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

	ImGui::Begin("framelate");
	ImGui::Text("%f", ImGui::GetIO().Framerate);
	ImGui::End();

#pragma endregion

#pragma region PunctualLight
	// ライトの更新
	punctualLight_->SetCameraPosition(*cLazieal::GetDefaultCamera()->GetWorldPos());
	punctualLight_->SetPunctualLightSetting(punctualLightSetting_.punctualLight);
	punctualLight_->Update();
#pragma endregion

#pragma region 3dObject
	// ティーポット更新
	teapot_->Update();
	// MultiMesh
	multiMesh_->Update();
	// MultiMaterial
	multiMaterial_->Update();
	// suzanne更新
	suzanne_->Update();
	// bunny
	bunny_->Update();
	// Sphere更新
	sphere_->Update();
#pragma endregion

#pragma region 2dObject
	// uvChecker更新
	uvChecker_->Update();
#pragma endregion
}

void cTitleScene::Draw() {
	// 3Dオブジェクト描画前処理
	cLazieal::PreDrawObject3D();

	// ティーポット描画
	if (isShow[teapot]) {
		teapot_->Draw();
	}
	// MultiMesh
	if (isShow[multiMesh]) {
		multiMesh_->Draw();
	}
	// MultiMaterial描画
	if (isShow[multiMaterial]) {
		multiMaterial_->Draw();
	}
	// bunny描画
	if (isShow[bunny]) {
		bunny_->Draw();
	}
	// Sphere描画
	if (isShow[sphere]) {
		sphere_->Draw();
	}

	// UVなし3Dオブジェクト描画前処理
	cLazieal::PreDrawObject3DUnUV();

	// suzanne描画
	if (isShow[suzanne]) {
		suzanne_->DrawUnUV();
	}

	// 2Dオブジェクト描画前処理
	cLazieal::PreDrawObject2D();

	// uvChecker描画
	uvChecker_->Draw();
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
