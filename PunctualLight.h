#pragma once
#include "MathFunction.h"

// C++
#include <wrl.h>

// DirectX
#include <d3d12.h>

// MyHedder
#include "PunctualLightSetting.h"

class cPunctualLight {
public: // 構造体
	// シェーダーに送るカメラ座標
	struct sCameraForGPU {
		Vector3 worldPosition;
		float padding;
	};

public: // メンバ関数
	// 初期化
	void Initialize();
	void Update();
	void TransferLight();

	void SetPunctualLightSetting(const cPunctualLightSetting::sPunctualLight& punctualLightSetting);
	void SetCameraPosition(const Vector3& cameraPosition);

private: // 非公開メンバ関数
#pragma region Light
	void CreatePunctualLightResource();
	void MapPunctualLightData();
#pragma endregion	
#pragma region Camera
	void CreateCameraResource();
	void MapCameraData();
#pragma endregion

	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(ID3D12Device* device, size_t sizeInBytes);

private: // メンバ変数

	// PunctualLight用のリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> punctualLightResource_ = nullptr;
	// シェーダーに送るライトのデータ
	cPunctualLightSetting::sPunctualLight* punctualLightData_ = nullptr;
	// PunctualLight
	cPunctualLightSetting::sPunctualLight punctualLight{};

	// Camera用リソース
	Microsoft::WRL::ComPtr<ID3D12Resource> cameraResource_ = nullptr;
	// Camera用データ
	sCameraForGPU* cameraData_ = nullptr;
	// カメラを受け取る箱
	sCameraForGPU camera;

};
