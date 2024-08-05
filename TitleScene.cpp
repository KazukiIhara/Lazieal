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

#pragma region PunctualLight
	punctualLight_ = new cPunctualLight();
	punctualLight_->Initialize();
	punctualLightSetting_ = punctualLight_->GetPunctualLight();
	punctualLight_->SetCameraPosition(*cLazieal::GetDefaultCamera()->GetWorldPos());

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
	uvCheckerPosition_ = { 0.0f,0.0f };
	uvCheckerRotate_ = 0.0f;
	uvCheckerUVTransform_ = { { 1.0f,1.0f }, 0.0f, { 0.0f,0.0f } };
	uvChecker_ = new cSprite();
	uvChecker_->Initialize("Resources/uvChecker.png");
	uvChecker_->SetPosition(uvCheckerPosition_);
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
}

void cTitleScene::Update() {

#pragma region ImGuiDebug

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
	ImGui::DragFloat2("Position", &uvCheckerPosition_.x, 1.0f);
	ImGui::DragFloat("Rotate", &uvCheckerRotate_, 0.01f);
	ImGui::DragFloat2("uvScale", &uvCheckerUVTransform_.scale.x, 0.01f);
	ImGui::DragFloat("uvRotate", &uvCheckerUVTransform_.rotateZ, 0.01f);
	ImGui::DragFloat2("uvTranslate", &uvCheckerUVTransform_.translate.x, 0.01f);

	uvChecker_->SetPosition(uvCheckerPosition_);
	uvChecker_->SetRotation(uvCheckerRotate_);
	uvChecker_->SetUVTransform(uvCheckerUVTransform_);
	ImGui::End();

#pragma endregion

#pragma region PunctualLight
	// ライトの更新
	punctualLight_->SetCameraPosition(*cLazieal::GetDefaultCamera()->GetWorldPos());
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
