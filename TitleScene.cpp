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

	// モデル読み込み
	cLazieal::LoadModel("teapot.obj");

	// ティーポット初期化
	teapot_ = new cObject3D();
	teapot_->Initialize();
	teapot_->SetModel("teapot.obj");
	teapot_->SetTranslate({ 0.0f,0.0f,10.0f });
}

void cTitleScene::Finalize() {
	// デバッグ用文字
	cLogger::Log("TitleScene,Finalized\n");

	delete teapot_;
}

void cTitleScene::Update() {
	// デモウィンドウを描画
	ImGui::ShowDemoWindow();

	// ティーポット更新
	teapot_->Update();
}

void cTitleScene::Draw() {

	// 3Dオブジェクト描画前処理
	cLazieal::PreDrawObject3D();

	// ティーポット描画
	teapot_->Draw();
}
