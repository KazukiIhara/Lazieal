#pragma once
#include "MathFunction.h"

// C++
#include <wrl.h>

// DirectX
#include <d3d12.h>

class cPunctualLightSetting {
public:
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

	// PunctualLight
	struct sPunctualLight {
		sDirectionalLight directionalLight;
		sPointLight pointLight;
		sSpotLight spotLight;
	};

public:
	cPunctualLightSetting();
	~cPunctualLightSetting();

	void Initialize();

public:
	sPunctualLight punctualLight{};
};