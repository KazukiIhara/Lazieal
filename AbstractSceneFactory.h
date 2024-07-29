#pragma once

// C++
#include <string>

// MyHedder
#include "BaseScene.h"

// シーン作成の抽象クラス
class cAbstractSceneFactory {
public:// 仮想関数
	// 仮想デストラクタ
	virtual ~cAbstractSceneFactory() = default;
	// シーン生成関数
	virtual cBaseScene* CreateScene(const std::string& sceneName) = 0;
};