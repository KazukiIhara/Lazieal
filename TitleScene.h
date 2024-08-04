#pragma once

// C++
#include <cstdint>

// MyHedder
#include "BaseScene.h"
#include "Object3d.h"

class cTitleScene:public cBaseScene {
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

	// ティーポット
	cWorldTransform teapotTransform_{};
	cObject3D* teapot_ = nullptr;

	// スザンヌ
	cWorldTransform suzanneTransform_{};
	cObject3D* suzanne_ = nullptr;

	// マルチマテリアル
	cWorldTransform multiMaterialTransform_{};
	cObject3D* multiMaterial_ = nullptr;

	// バニー
	cWorldTransform bunnyTransform_{};
	cObject3D* bunny_ = nullptr;

	// スフィア
	cWorldTransform sphereTransform_{};
	cObject3D* sphere_ = nullptr;
};

