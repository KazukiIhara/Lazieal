// This
#include "TitleScene.h"

// MyHedder
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
	// デバッグ用文字
	cLogger::Log("TitleScene,Update\n");
}

void cTitleScene::Draw() {
	// デバッグ用文字
	cLogger::Log("TitleScene,Draw\n");
}
