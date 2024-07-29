#pragma once

// MyHedder
#include "AbstractSceneFactory.h"

// 今回のゲーム用のシーン作成クラス
class cSceneFactory :public cAbstractSceneFactory {
public:
	// シーン生成
	cBaseScene* CreateScene(const std::string& sceneName)override;
};