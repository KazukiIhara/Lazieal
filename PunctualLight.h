#pragma once
#include "MathFunction.h"

class cPunctualLight {
public: // 構造体
	// ディレクショナルライト
	struct sDirectionalLight {
		Vector4 color; //ライトの色
		Vector3 direction; //ライトの向き
		float intensity; //輝度
	};

	// ポイントライト
	struct sPointLight {
		Vector4 color;
		Vector3 position;
		float intensity;
		float radius;
		float decay;
		float padding[2];
	};

	// スポットライト
	struct sSpotLight {
		Vector4 color;
		Vector3 position;
		float intensity;
		Vector3 direction;
		float distance;
		float decay;
		float cosFalloffStart;
		float cosAngle;
		float padding; 
	};

	// シェーダーに送るカメラ座標
	struct sCameraForGPU {
		Vector3 worldPosition;
		float padding; 
	};

	// PunctualLight
	struct sPunctualLight {
		sDirectionalLight directionalLight;
		sPointLight pointLight;
		sSpotLight spotLight;
		sCameraForGPU camera;
	};

public: // メンバ関数
	// 初期化
	void Initialize(Vector3* cameraPosition);

public: // メンバ変数
	sPunctualLight punctualLight;
};
