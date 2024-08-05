#pragma once

// C++
#include <cstdint>

// MyHedder
#include "BaseScene.h"
#include "Object3d.h"
#include "Sprite.h"

class cTitleScene :public cBaseScene {
public:
	enum Object {
		teapot,
		suzanne,
		multiMesh,
		multiMaterial,
		bunny,
		sphere,
	};
	static const uint32_t kObjectNum = 6;

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

private: // 非公開メンバ関数
	void SwitchShowObjects();

private: // 非公開メンバ変数
#pragma region PunctualLight
	cPunctualLightSetting punctualLightSetting_{};
	cPunctualLight* punctualLight_ = nullptr;
#pragma endregion

#pragma region 3dModel
	// ティーポット
	cWorldTransform teapotTransform_{};
	cObject3D* teapot_ = nullptr;

	// スザンヌ
	cWorldTransform suzanneTransform_{};
	cObject3D* suzanne_ = nullptr;

	// マルチメッシュ
	cWorldTransform multiMeshTransform_{};
	cObject3D* multiMesh_ = nullptr;

	// マルチマテリアル
	cWorldTransform multiMaterialTransform_{};
	cObject3D* multiMaterial_ = nullptr;

	// バニー
	cWorldTransform bunnyTransform_{};
	cObject3D* bunny_ = nullptr;

	// スフィア
	cWorldTransform sphereTransform_{};
	cObject3D* sphere_ = nullptr;

	// 描画フラグ
	bool isShow[kObjectNum]{};
#pragma endregion

#pragma region Sprite
	// uvChecker
	Vector2 uvCheckerPosition_{};
	float uvCheckerRotate_{};
	sUVTransform uvCheckerUVTransform_{};
	cSprite* uvChecker_ = nullptr;
#pragma endregion

};

