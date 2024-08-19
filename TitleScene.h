#pragma once

// C++
#include <cstdint>

// MyHedder
#include "BaseScene.h"
#include "Object3d.h"
#include "Sprite.h"
#include "SoundManager.h"

class cTitleScene:public cBaseScene {
public:

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

private: // 非公開メンバ変数
#pragma region PunctualLight
	cPunctualLightSetting punctualLightSetting_{};
	cPunctualLight* punctualLight_ = nullptr;
#pragma endregion

#pragma region SoundData
	cSoundManager::SoundData soundData{};
#pragma endregion

};

