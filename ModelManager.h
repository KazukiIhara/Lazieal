#pragma once

// C++
#include <map>
#include <string>
#include <memory>

// MyHedder
#include "Model.h"

class cModelManager {
public:
	// 初期化
	void Initialize();
	// モデル読み込み
	void Load(const std::string& filePath);
	// モデルの検索
	cModel* Find(const std::string& filePath);
	// 終了
	void Finalize();

private: // メンバ変数
	// モデルデータコンテナ
	std::map<std::string, std::unique_ptr<cModel>> models_;
};

