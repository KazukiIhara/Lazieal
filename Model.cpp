// This
#include "Model.h"

// C++ 
#include <cassert>

// Assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// MyHedder
#include "Lazieal.h"

void cModel::Initialize(const std::string& filename) {
	// モデルデータ読み込み
	LoadModel(filename);

	// マテリアル初期化
	material_.color = modelData.material.color;
	material_.enbleLighting = true;
	material_.shininess = 40.0f;
	material_.uvTransformMatrix = MakeIdentityMatrix4x4();

#pragma region 頂点データ
	/*頂点リソースの作成*/
	CreateVertexResource();
	/*頂点バッファビューの作成*/
	CreateVretexBufferView();
	/*頂点データの書き込み*/
	MapVertexData();
#pragma endregion

#pragma region マテリアルデータ
	/*マテリアル用のリソース作成*/
	CreateMaterialResource();
	/*マテリアルにデータを書き込む*/
	MapMaterialData();
#pragma endregion

}

void cModel::Update() {
	// マテリアルの更新
	materialData_->color = material_.color;
	materialData_->enbleLighting = material_.enbleLighting;
	materialData_->shininess = material_.shininess;
	materialData_->uvTransformMatrix = material_.uvTransformMatrix;
}

void cModel::Draw() {
	// VBVを設定
	cLazieal::GetDirectXCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView_);
	// マテリアルCBufferの場所を設定
	cLazieal::GetDirectXCommandList()->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());
	if (modelData.material.haveUV_) {
		// SRVセット
		cLazieal::SetGraphicsRootDescriptorTable(3, cLazieal::GetTexture()[modelData.material.textureFilePath].srvIndex);
		// 描画！(DrawCall/ドローコール)。3頂点で1つのインスタンス。インスタンスについては今後
		cLazieal::GetDirectXCommandList()->DrawInstanced(UINT(modelData.vertices.size()), 1, 0, 0);
	} else {
		cLazieal::GetDirectXCommandList()->DrawInstanced(UINT(modelData.verticesUnUV.size()), 1, 0, 0);
	}
}

void cModel::LoadModel(const std::string& filename, const std::string& directoryPath) {

	std::string fileDirectoryPath = directoryPath + "/" + filename;

	Assimp::Importer importer;
	std::string filePath = fileDirectoryPath + "/" + filename + ".obj";
	const aiScene* scene = importer.ReadFile(filePath.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs | aiProcess_Triangulate);
	assert(scene->HasMeshes());

	for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex) {
		aiMesh* mesh = scene->mMeshes[meshIndex];
		assert(mesh->HasNormals()); // 法線がないmeshは今回は非対応

		if (mesh->HasTextureCoords(0)) { // uvあり
			modelData.material.haveUV_ = true;
			for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex) {
				aiFace& face = mesh->mFaces[faceIndex];
				assert(face.mNumIndices == 3);

				for (uint32_t element = 0; element < face.mNumIndices; ++element) {
					uint32_t vertexIndex = face.mIndices[element];
					aiVector3D& position = mesh->mVertices[vertexIndex];
					aiVector3D& normal = mesh->mNormals[vertexIndex];
					aiVector3D& texcoord = mesh->mTextureCoords[0][vertexIndex];
					sVertexData3D vertex;
					vertex.position = { position.x,position.y,position.z,1.0f };
					vertex.normal = { normal.x,normal.y,normal.z };
					vertex.texcoord = { texcoord.x,texcoord.y };
					// aiProcess_makeLeftHandedはz+=-1で、右手->左手に変換するので手動で対処
					vertex.position.x *= -1.0f;
					vertex.normal.x *= -1.0f;
					modelData.vertices.push_back(vertex);
				}
			}

		} else { // uvなし
			modelData.material.haveUV_ = false;
			for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex) {
				aiFace& face = mesh->mFaces[faceIndex];
				assert(face.mNumIndices == 3);

				for (uint32_t element = 0; element < face.mNumIndices; ++element) {
					uint32_t vertexIndex = face.mIndices[element];
					aiVector3D& position = mesh->mVertices[vertexIndex];
					aiVector3D& normal = mesh->mNormals[vertexIndex];
					sVertexData3DUnUV vertex;
					vertex.position = { position.x,position.y,position.z,1.0f };
					vertex.normal = { normal.x,normal.y,normal.z };
					// aiProcess_makeLeftHandedはz+=-1で、右手->左手に変換するので手動で対処
					vertex.position.x *= -1.0f;
					vertex.normal.x *= -1.0f;
					modelData.verticesUnUV.push_back(vertex);
				}
			}

		}

	}


	for (uint32_t materialIndex = 0; materialIndex < scene->mNumMaterials; ++materialIndex) {
		aiMaterial* material = scene->mMaterials[materialIndex];
		if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0) {
			aiString textureFilePath;

			material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFilePath);
			modelData.material.textureFilePath = fileDirectoryPath + "/" + textureFilePath.C_Str();
			cLazieal::LoadTexture(modelData.material.textureFilePath);
		}
	}

	modelData.material.color = { 1.0f, 1.0f, 1.0f, 1.0f };
}

void cModel::CreateVertexResource() {
	if (modelData.material.haveUV_) {
		vertexResource_ = CreateBufferResource(cLazieal::GetDirectXDevice(), sizeof(sVertexData3D) * modelData.vertices.size());
	} else {
		vertexResource_ = CreateBufferResource(cLazieal::GetDirectXDevice(), sizeof(sVertexData3DUnUV) * modelData.verticesUnUV.size());
	}
}

void cModel::CreateVretexBufferView() {
	//リソースの先頭アドレスから使う
	vertexBufferView_.BufferLocation = vertexResource_->GetGPUVirtualAddress();
	if (modelData.material.haveUV_) {
		//使用するリソースのサイズ
		vertexBufferView_.SizeInBytes = UINT(sizeof(sVertexData3D) * modelData.vertices.size());
		//1頂点あたりのサイズ
		vertexBufferView_.StrideInBytes = sizeof(sVertexData3D);
	} else {
		//使用するリソースのサイズ
		vertexBufferView_.SizeInBytes = UINT(sizeof(sVertexData3DUnUV) * modelData.verticesUnUV.size());
		//1頂点あたりのサイズ
		vertexBufferView_.StrideInBytes = sizeof(sVertexData3DUnUV);
	}
}

void cModel::MapVertexData() {
	if (modelData.material.haveUV_) {
		vertexData_ = nullptr;
		vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));
		std::memcpy(vertexData_, modelData.vertices.data(), sizeof(sVertexData3D) * modelData.vertices.size());
	} else {
		vertexDataUnUV_ = nullptr;
		vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexDataUnUV_));
		std::memcpy(vertexDataUnUV_, modelData.verticesUnUV.data(), sizeof(sVertexData3DUnUV) * modelData.verticesUnUV.size());
	}
}

void cModel::CreateMaterialResource() {
	// マテリアル用のリソースを作る。
	materialResource_ = CreateBufferResource(cLazieal::GetDirectXDevice(), sizeof(sMaterial3D));
}

void cModel::MapMaterialData() {
	// マテリアルにデータを書き込む
	materialData_ = nullptr;
	// 書き込むためのアドレスを取得
	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialData_));
	// mtlのデータから色を書き込む
	materialData_->color = modelData.material.color;
	// Lightingを有効にする
	materialData_->enbleLighting = true;
	// uvTransformMatrix
	materialData_->uvTransformMatrix = MakeIdentityMatrix4x4();
}

Microsoft::WRL::ComPtr<ID3D12Resource> cModel::CreateBufferResource(ID3D12Device* device, size_t sizeInBytes) {
	HRESULT hr = S_FALSE;
	//頂点リソース用のヒープの設定
	D3D12_HEAP_PROPERTIES uplodeHeapProperties{};
	uplodeHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;//UploadHeapを使う

	//マテリアル用のリソースの設定
	D3D12_RESOURCE_DESC resourceDesc{};
	//バッファリソース。テクスチャの場合はまた別の設定をする
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resourceDesc.Width = sizeInBytes;
	//バッファの場合はこれらは1にする決まり
	resourceDesc.Height = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.MipLevels = 1;
	resourceDesc.SampleDesc.Count = 1;
	//バッファの場合はこれにする決まり
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	//バッファリソースを作る
	Microsoft::WRL::ComPtr<ID3D12Resource>resource = nullptr;
	hr = device->CreateCommittedResource(&uplodeHeapProperties, D3D12_HEAP_FLAG_NONE,
		&resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&resource));
	assert(SUCCEEDED(hr));
	return resource;
}
