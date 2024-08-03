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
	teapotTransform_.translate = { 1.0f,0.0f,10.0f };

	// ティーポット初期化
	teapot_ = new cObject3D();
	teapot_->Initialize();
	teapot_->SetModel("teapot");
	teapot_->SetTranslate(teapotTransform_.translate);

#pragma endregion


#pragma region suzanne
	// モデル読み込み
	cLazieal::LoadModel("suzanne");

	// スザンヌのトランスフォーム
	suzanneTransform_.Initialize();
	suzanneTransform_.translate = { -1.0f,0.0f,10.0f };
	suzanneTransform_.rotate = { 0.0f,1.0f,0.0f };

	// スザンヌ初期化
	suzanne_ = new cObject3D();
	suzanne_->Initialize();
	suzanne_->SetModel("suzanne");
	suzanne_->SetTranslate(suzanneTransform_.translate);
	suzanne_->SetRotate(suzanneTransform_.rotate);

#pragma endregion

}

void cTitleScene::Finalize() {
	// デバッグ用文字
	cLogger::Log("TitleScene,Finalized\n");

	delete teapot_;
	delete suzanne_;
}

void cTitleScene::Update() {
	// デモウィンドウを描画
	ImGui::ShowDemoWindow();

	// ティーポット更新
	teapot_->Update();
	// suzanne更新
	suzanne_->Update();
}

void cTitleScene::Draw() {

	// 3Dオブジェクト描画前処理
	cLazieal::PreDrawObject3D();

	// ティーポット描画
	teapot_->Draw();

	// UVなし3Dオブジェクト描画前処理
	cLazieal::PreDrawObject3DUnUV();
	// suzanne描画
	suzanne_->DrawUnUV();
}
