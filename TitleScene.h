#pragma once

// C++
#include <cstdint>

// MyHedder
#include "BaseScene.h"

class cTitleScene :public cBaseScene {
public: // 公開メンバ関数
	// コンストラクタ
	cTitleScene();
	// デストラクタ
	~cTitleScene();
	// 初期化
	void Initialize()override;
	// 終了
	void Finalize()override;
	// 更新
	void Update()override;
	// 描画
	void Draw()override;

private:

};

