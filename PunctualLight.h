#pragma once
#include "MathFunction.h"

// C++
#include <wrl.h>

// DirectX
#include <d3d12.h>

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
	void Update();
	void TransferLight();

private: // 非公開メンバ関数
#pragma region Light
	void CreatePunctualLightResource();
	void MapPunctualLightData();
#pragma endregion	
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(ID3D12Device* device, size_t sizeInBytes);

private: // メンバ変数

	// PunctualLight用のリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> punctualLightResource_ = nullptr;
	// シェーダーに送るライトのデータ
	sPunctualLight* punctualLightData_ = nullptr;
	// PunctualLight
	sPunctualLight punctualLight;

};
