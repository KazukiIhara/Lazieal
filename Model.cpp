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
	for (auto& mesh : modelData.meshes) {
		sMaterial3D material;
		material.color = mesh.material.color;
		material.enbleLighting = true;
		material.shininess = 40.0f;
		material.uvTransformMatrix = MakeIdentityMatrix4x4();
		materials_.push_back(material);
		sUVTransform identity = { {1.0f,1.0f,1.0f},0.0f,{0.0f,0.0f,0.0f} };
		uvTransforms_.push_back(identity);
	}

#pragma region 頂点データ
	/*頂点リソースの作成*/
	CreateVertexResource();
	/*頂点バッファビューの作成*/
	CreateVertexBufferView();
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
	for (size_t i = 0; i < materials_.size(); ++i) {
		materialData_[i]->color = materials_[i].color;
		materialData_[i]->enbleLighting = materials_[i].enbleLighting;
		materialData_[i]->shininess = materials_[i].shininess;
		materials_[i].uvTransformMatrix = MakeAffineMatrix(uvTransforms_[i].scale, Vector3(0.0f, 0.0f, uvTransforms_[i].rotateZ), uvTransforms_[i].translate);
		materialData_[i]->uvTransformMatrix = materials_[i].uvTransformMatrix;
	}
}

void cModel::Draw() {
	for (size_t i = 0; i < modelData.meshes.size(); ++i) {
		// VBVを設定
		cLazieal::GetDirectXCommandList()->IASetVertexBuffers(0, 1, &vertexBufferViews_[i]);
		// マテリアルCBufferの場所を設定
		cLazieal::GetDirectXCommandList()->SetGraphicsRootConstantBufferView(0, materialResources_[i]->GetGPUVirtualAddress());
		if (modelData.meshes[i].material.haveUV_) {
			// SRVセット
			cLazieal::SetGraphicsRootDescriptorTable(3, cLazieal::GetTexture()[modelData.meshes[i].material.textureFilePath].srvIndex);
			// 描画！(DrawCall/ドローコール)。3頂点で1つのインスタンス。インスタンスについては今後
			cLazieal::GetDirectXCommandList()->DrawInstanced(UINT(modelData.meshes[i].vertices.size()), 1, 0, 0);
		} else {
			cLazieal::GetDirectXCommandList()->DrawInstanced(UINT(modelData.meshes[i].verticesUnUV.size()), 1, 0, 0);
		}
	}
}

void cModel::LoadModel(const std::string& filename, const std::string& directoryPath) {
	std::string fileDirectoryPath = directoryPath + "/" + filename;

	Assimp::Importer importer;
	std::string filePath = fileDirectoryPath + "/" + filename + ".obj";
	const aiScene* scene = importer.ReadFile(filePath.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs | aiProcess_Triangulate);
	assert(scene->HasMeshes());

	std::vector<sMaterialData> materials(scene->mNumMaterials);

	for (uint32_t materialIndex = 0; materialIndex < scene->mNumMaterials; ++materialIndex) {
		aiMaterial* material = scene->mMaterials[materialIndex];
		sMaterialData materialData;
		if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0) {
			aiString textureFilePath;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFilePath);
			materialData.textureFilePath = fileDirectoryPath + "/" + textureFilePath.C_Str();
			cLazieal::LoadTexture(materialData.textureFilePath);
			materialData.haveUV_ = true;
		} else {
			materialData.haveUV_ = false;
		}
		materialData.color = { 1.0f, 1.0f, 1.0f, 1.0f };
		materials[materialIndex] = materialData;
	}

	for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex) {
		aiMesh* mesh = scene->mMeshes[meshIndex];
		assert(mesh->HasNormals());

		sMeshData meshData;
		meshData.material = materials[mesh->mMaterialIndex];

		if (mesh->HasTextureCoords(0)) {
			for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex) {
				aiFace& face = mesh->mFaces[faceIndex];
				assert(face.mNumIndices == 3);

				for (uint32_t element = 0; element < face.mNumIndices; ++element) {
					uint32_t vertexIndex = face.mIndices[element];
					aiVector3D& position = mesh->mVertices[vertexIndex];
					aiVector3D& normal = mesh->mNormals[vertexIndex];
					aiVector3D& texcoord = mesh->mTextureCoords[0][vertexIndex];
					sVertexData3D vertex;
					vertex.position = { position.x, position.y, position.z, 1.0f };
					vertex.normal = { normal.x, normal.y, normal.z };
					vertex.texcoord = { texcoord.x, texcoord.y };
					vertex.position.x *= -1.0f;
					vertex.normal.x *= -1.0f;
					meshData.vertices.push_back(vertex);
				}
			}
		} else {
			for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex) {
				aiFace& face = mesh->mFaces[faceIndex];
				assert(face.mNumIndices == 3);

				for (uint32_t element = 0; element < face.mNumIndices; ++element) {
					uint32_t vertexIndex = face.mIndices[element];
					aiVector3D& position = mesh->mVertices[vertexIndex];
					aiVector3D& normal = mesh->mNormals[vertexIndex];
					sVertexData3DUnUV vertex;
					vertex.position = { position.x, position.y, position.z, 1.0f };
					vertex.normal = { normal.x, normal.y, normal.z };
					vertex.position.x *= -1.0f;
					vertex.normal.x *= -1.0f;
					meshData.verticesUnUV.push_back(vertex);
				}
			}
		}

		modelData.meshes.push_back(meshData);
	}
}

void cModel::CreateVertexResource() {
	for (auto& mesh : modelData.meshes) {
		Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource;
		if (mesh.material.haveUV_) {
			vertexResource = CreateBufferResource(cLazieal::GetDirectXDevice(), sizeof(sVertexData3D) * mesh.vertices.size());
		} else {
			vertexResource = CreateBufferResource(cLazieal::GetDirectXDevice(), sizeof(sVertexData3DUnUV) * mesh.verticesUnUV.size());
		}
		vertexResources_.push_back(vertexResource);
	}
}

void cModel::CreateVertexBufferView() {
	for (size_t i = 0; i < modelData.meshes.size(); ++i) {
		D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
		vertexBufferView.BufferLocation = vertexResources_[i]->GetGPUVirtualAddress();
		if (modelData.meshes[i].material.haveUV_) {
			vertexBufferView.SizeInBytes = UINT(sizeof(sVertexData3D) * modelData.meshes[i].vertices.size());
			vertexBufferView.StrideInBytes = sizeof(sVertexData3D);
		} else {
			vertexBufferView.SizeInBytes = UINT(sizeof(sVertexData3DUnUV) * modelData.meshes[i].verticesUnUV.size());
			vertexBufferView.StrideInBytes = sizeof(sVertexData3DUnUV);
		}
		vertexBufferViews_.push_back(vertexBufferView);
	}
}

void cModel::MapVertexData() {
	for (size_t i = 0; i < modelData.meshes.size(); ++i) {
		if (modelData.meshes[i].material.haveUV_) {
			sVertexData3D* vertexData = nullptr;
			vertexResources_[i]->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
			std::memcpy(vertexData, modelData.meshes[i].vertices.data(), sizeof(sVertexData3D) * modelData.meshes[i].vertices.size());
			vertexData_.push_back(vertexData);
		} else {
			sVertexData3DUnUV* vertexDataUnUV = nullptr;
			vertexResources_[i]->Map(0, nullptr, reinterpret_cast<void**>(&vertexDataUnUV));
			std::memcpy(vertexDataUnUV, modelData.meshes[i].verticesUnUV.data(), sizeof(sVertexData3DUnUV) * modelData.meshes[i].verticesUnUV.size());
			vertexDataUnUV_.push_back(vertexDataUnUV);
		}
	}
}

void cModel::CreateMaterialResource() {
	for (size_t i = 0; i < materials_.size(); ++i) {
		Microsoft::WRL::ComPtr<ID3D12Resource> materialResource = CreateBufferResource(cLazieal::GetDirectXDevice(), sizeof(sMaterial3D));
		materialResources_.push_back(materialResource);
	}
}

void cModel::MapMaterialData() {
	for (size_t i = 0; i < materials_.size(); ++i) {
		sMaterial3D* materialData = nullptr;
		materialResources_[i]->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
		materialData->color = materials_[i].color;
		materialData->enbleLighting = materials_[i].enbleLighting;
		materialData->shininess = materials_[i].shininess;
		materialData->uvTransformMatrix = materials_[i].uvTransformMatrix;
		materialData_.push_back(materialData);
	}
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
