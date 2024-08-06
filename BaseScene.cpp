// This
#include "BaseScene.h"

// MyHedder
#include "Lazieal.h"

void cBaseScene::Initialize() {
	// サウンドマネージャの初期化
	cLazieal::InitializeSoundManager();
}

void cBaseScene::Finalize() {
	// サウンドマネージャの終了
	cLazieal::FinalizeSoundManager();
}
