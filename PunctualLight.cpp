#include "PunctualLight.h"


#include "Lazieal.h"

void cPunctualLight::Initialize(Vector3* cameraPosition) {
	// DirectionalLightの初期化
	punctualLight.directionalLight.color = { 1.0f,1.0f,1.0f,1.0f };
	punctualLight.directionalLight.direction = { 0.0f,-1.0f,0.0f };
	punctualLight.directionalLight.intensity = 1.0f;

	// PointLightの初期化
	punctualLight.pointLight.color = { 1.0f,1.0f,1.0f,1.0f };
	punctualLight.pointLight.intensity = 0.0f;
	punctualLight.pointLight.position = { 0.0f,2.0f,0.0f };
	punctualLight.pointLight.radius = 10.0f;
	punctualLight.pointLight.decay = 5.0f;

	// SpotLightの初期化
	punctualLight.spotLight.color = { 1.0f,1.0f,1.0f,1.0f };
	punctualLight.spotLight.position = { 2.0f,1.25f,0.0f };
	punctualLight.spotLight.distance = 7.0f;
	punctualLight.spotLight.direction = Normalize({ -1.0f,-1.0f,0.0f });
	punctualLight.spotLight.intensity = 0.0f;
	punctualLight.spotLight.decay = 2.0f;
	punctualLight.spotLight.cosFalloffStart = 0.1f;
	punctualLight.spotLight.cosAngle = std::cos(std::numbers::pi_v<float> / 3.0f);

	// Cameraの初期化
	punctualLight.camera.worldPosition.x = cameraPosition->x;
	punctualLight.camera.worldPosition.y = cameraPosition->y;
	punctualLight.camera.worldPosition.z = cameraPosition->z;

	// リソース作成
	CreatePunctualLightResource();
	// データ書き込み
	MapPunctualLightData();
}

void cPunctualLight::Update() {
	// DirectionalLight
	punctualLightData_->directionalLight.color = punctualLight.directionalLight.color;
	punctualLightData_->directionalLight.direction = punctualLight.directionalLight.direction;
	punctualLightData_->directionalLight.intensity = punctualLight.directionalLight.intensity;

	// PointLight
	punctualLightData_->pointLight.color = punctualLight.pointLight.color;
	punctualLightData_->pointLight.decay = punctualLight.pointLight.decay;
	punctualLightData_->pointLight.intensity = punctualLight.pointLight.intensity;
	punctualLightData_->pointLight.position = punctualLight.pointLight.position;
	punctualLightData_->pointLight.radius = punctualLight.pointLight.radius;

	// SpotLight
	punctualLightData_->spotLight.color = punctualLight.spotLight.color;
	punctualLightData_->spotLight.cosAngle = punctualLight.spotLight.cosAngle;
	punctualLightData_->spotLight.cosFalloffStart = punctualLight.spotLight.cosFalloffStart;
	punctualLightData_->spotLight.decay = punctualLight.spotLight.decay;
	punctualLightData_->spotLight.direction = punctualLight.spotLight.direction;
	punctualLightData_->spotLight.distance = punctualLight.spotLight.distance;
	punctualLightData_->spotLight.intensity = punctualLight.spotLight.intensity;
	punctualLightData_->spotLight.position = punctualLight.spotLight.position;

	// カメラ
	punctualLightData_->camera.worldPosition.x = punctualLight.camera.worldPosition.x;
	punctualLightData_->camera.worldPosition.y = punctualLight.camera.worldPosition.y;
	punctualLightData_->camera.worldPosition.z = punctualLight.camera.worldPosition.z;

}

void cPunctualLight::TransferLight() {
	// 定数バッファを転送
	cLazieal::GetDirectXCommandList()->SetGraphicsRootConstantBufferView(2, punctualLightResource_->GetGPUVirtualAddress());
}

void cPunctualLight::CreatePunctualLightResource() {
	// WVP用のリソースを作る
	punctualLightResource_ = CreateBufferResource(cLazieal::GetDirectXDevice(), sizeof(cPunctualLight::sPunctualLight));
}

void cPunctualLight::MapPunctualLightData() {
	// データを書き込む
	punctualLightData_ = nullptr;
	// 書き込むためのアドレスを取得
	punctualLightResource_->Map(0, nullptr, reinterpret_cast<void**>(&punctualLightData_));

	// DirectionalLight
	punctualLightData_->directionalLight.color = punctualLight.directionalLight.color;
	punctualLightData_->directionalLight.direction = punctualLight.directionalLight.direction;
	punctualLightData_->directionalLight.intensity = punctualLight.directionalLight.intensity;

	// PointLight
	punctualLightData_->pointLight.color = punctualLight.pointLight.color;
	punctualLightData_->pointLight.decay = punctualLight.pointLight.decay;
	punctualLightData_->pointLight.intensity = punctualLight.pointLight.intensity;
	punctualLightData_->pointLight.position = punctualLight.pointLight.position;
	punctualLightData_->pointLight.radius = punctualLight.pointLight.radius;

	// SpotLight
	punctualLightData_->spotLight.color = punctualLight.spotLight.color;
	punctualLightData_->spotLight.cosAngle = punctualLight.spotLight.cosAngle;
	punctualLightData_->spotLight.cosFalloffStart = punctualLight.spotLight.cosFalloffStart;
	punctualLightData_->spotLight.decay = punctualLight.spotLight.decay;
	punctualLightData_->spotLight.direction = punctualLight.spotLight.direction;
	punctualLightData_->spotLight.distance = punctualLight.spotLight.distance;
	punctualLightData_->spotLight.intensity = punctualLight.spotLight.intensity;
	punctualLightData_->spotLight.position = punctualLight.spotLight.position;

	// カメラ
	punctualLightData_->camera.worldPosition.x = punctualLight.camera.worldPosition.x;
	punctualLightData_->camera.worldPosition.y = punctualLight.camera.worldPosition.y;
	punctualLightData_->camera.worldPosition.z = punctualLight.camera.worldPosition.z;

}

Microsoft::WRL::ComPtr<ID3D12Resource> cPunctualLight::CreateBufferResource(ID3D12Device* device, size_t sizeInBytes) {
	HRESULT hr = S_FALSE;
	// 頂点リソース用のヒープの設定
	D3D12_HEAP_PROPERTIES uplodeHeapProperties{};
	uplodeHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD; // UploadHeapを使う

	// マテリアル用のリソースの設定
	D3D12_RESOURCE_DESC resourceDesc{};
	// バッファリソース。テクスチャの場合はまた別の設定をする
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resourceDesc.Width = sizeInBytes;
	// バッファの場合はこれらは1にする決まり
	resourceDesc.Height = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.MipLevels = 1;
	resourceDesc.SampleDesc.Count = 1;
	// バッファの場合はこれにする決まり
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// バッファリソースを作る
	Microsoft::WRL::ComPtr<ID3D12Resource> resource = nullptr;
	hr = device->CreateCommittedResource(
		&uplodeHeapProperties, D3D12_HEAP_FLAG_NONE,
		&resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&resource));
	assert(SUCCEEDED(hr));
	return resource;
}
