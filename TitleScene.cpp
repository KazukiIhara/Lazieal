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
	suzanne_->SetTranslate(suzanneTransform_.translate);
	suzanne_->SetRotate(suzanneTransform_.rotate);

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
	bunny_->SetModel("bunny");
	bunny_->SetTransform(bunnyTransform_);

#pragma endregion

}

void cTitleScene::Finalize() {
	// デバッグ用文字
	cLogger::Log("TitleScene,Finalized\n");

	delete teapot_;
	delete suzanne_;
	delete multiMaterial_;
	delete bunny_;
}

void cTitleScene::Update() {
	// デモウィンドウを描画
	ImGui::ShowDemoWindow();

	cLazieal::ImGuiDebug3dObject(multiMaterialTransform_, multiMaterial_);

	// ティーポット更新
	teapot_->Update();
	// MultiMaterial
	multiMaterial_->Update();
	// suzanne更新
	suzanne_->Update();
	// bunny
	bunny_->Update();
}

void cTitleScene::Draw() {

	// 3Dオブジェクト描画前処理
	cLazieal::PreDrawObject3D();

	// ティーポット描画
	//teapot_->Draw();

	// MultiMaterial描画
	multiMaterial_->Draw();

	// bunny描画
	//bunny_->Draw();

	// UVなし3Dオブジェクト描画前処理
	cLazieal::PreDrawObject3DUnUV();

	// suzanne描画
	//suzanne_->DrawUnUV();
}
