// This
#include "ModelManager.h"

void cModelManager::Initialize() {
	// 配列をクリア
	models_.clear();
}

void cModelManager::Load(const std::string& filePath) {
	// 読み込み済みモデルを検索
	if (models_.contains(filePath)) {
		// 読み込み済みなら早期リターン
		return;
	}
	// モデルの生成とファイルの読み込み、初期化
	std::unique_ptr<cModel> model = std::make_unique<cModel>();
	model->Initialize(filePath);

	// モデルをmapコンテナに格納する
	models_.insert(std::make_pair(filePath, std::move(model)));
}

cModel* cModelManager::Find(const std::string& filePath) {
	// 読み込み済みモデルを検索
	if (models_.contains(filePath)) {
		// 読み込みモデルを戻り値としてreturn
		return models_.at(filePath).get();
	}
	// ファイル名一致なし
	return nullptr;
}

void cModelManager::Finalize() {
	// 配列をクリア
	models_.clear();
}
