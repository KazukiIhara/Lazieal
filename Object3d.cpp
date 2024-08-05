// This
#include "Object3d.h"

// MyHedder
#include "Lazieal.h"

void cObject3D::Initialize() {

	// ViewProjection初期化
	viewProjection_ = cLazieal::GetDefaultCamera()->GetViewProjectionMatrix();

#pragma region 変換データ
	// wvp用のリソース作成
	CreateWVPResource();
	// データを書き込む
	MapWVPData();
#pragma endregion
}

void cObject3D::Update() {
	// モデル読み込み済みなら更新
	if (model) {
		model->Update();
	}

	// WVPマトリックスを作る
	transform_.Update();
	transformationData_->WVP = transform_.worldMatrix_ * *viewProjection_;
	transformationData_->World = transform_.worldMatrix_;
	transformationData_->WorldInverseTransepose = MakeInverseTransposeMatrix(transform_.worldMatrix_);

}

void cObject3D::Draw(cPipelineManager::eBlendMode blendMode) {
	// PSOを設定
	cLazieal::GetDirectXCommandList()->SetPipelineState(cLazieal::GetPipelineState(cPipelineManager::kObject3d, blendMode));
	// wvp用のCBufferの場所を設定
	cLazieal::GetDirectXCommandList()->SetGraphicsRootConstantBufferView(1, transformationResource_->GetGPUVirtualAddress());
	// PunctualLight
	punctualLight_->TransferLight();

	// 3Dモデルが割り当てられていれば描画する
	if (model) {
		model->Draw();
	}
}

void cObject3D::DrawUnUV(cPipelineManager::eBlendMode blendMode) {
	// PSOを設定
	cLazieal::GetDirectXCommandList()->SetPipelineState(cLazieal::GetPipelineState(cPipelineManager::kObject3dUnUV, blendMode));
	// wvp用のCBufferの場所を設定
	cLazieal::GetDirectXCommandList()->SetGraphicsRootConstantBufferView(1, transformationResource_->GetGPUVirtualAddress());
	// PunctualLight
	punctualLight_->TransferLight();
	// 3Dモデルが割り当てられていれば描画する
	if (model) {
		model->Draw();
	}
}

void cObject3D::CreateWVPResource() {
	// WVP用のリソースを作る
	transformationResource_ = CreateBufferResource(cLazieal::GetDirectXDevice(), sizeof(sTransformationMatrix));
}

void cObject3D::MapWVPData() {
	// データを書き込む
	transformationData_ = nullptr;
	// 書き込むためのアドレスを取得
	transformationResource_->Map(0, nullptr, reinterpret_cast<void**>(&transformationData_));
	// 単位行列を書き込んでおく
	transformationData_->WVP = MakeIdentityMatrix4x4();
	transformationData_->World = MakeIdentityMatrix4x4();
	transformationData_->WorldInverseTransepose = MakeIdentityMatrix4x4();
}

Microsoft::WRL::ComPtr<ID3D12Resource> cObject3D::CreateBufferResource(ID3D12Device* device, size_t sizeInBytes) {
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

void cObject3D::SetModel(const std::string& filePath) {
	objectname_ = filePath;
	model = cLazieal::FindModel(filePath);
}
