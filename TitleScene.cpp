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
}

void cTitleScene::Finalize() {
	// デバッグ用文字
	cLogger::Log("TitleScene,Finalized\n");
}

void cTitleScene::Update() {
	// デモウィンドウを描画
	ImGui::ShowDemoWindow();
}

void cTitleScene::Draw() {

	// 3Dオブジェクト描画前処理
	cLazieal::PreDrawObject3D();

}
