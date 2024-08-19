// This
#include "LevelDataManager.h"

// C++
#include <fstream>
#include <cassert>

// Json
#include <json.hpp>

// MyHedder
#include "LevelData.h"

void cLevelDataManager::LoadLevelData(const std::string& fileName) {

	// 連結してフルパスを得る
	const std::string fullpath = "LevelDatas/" + fileName + ".json";

	// ファイルストリーム
	std::ifstream file;

	// ファイルを開く
	file.open(fullpath);
	// ファイルオープン失敗をチェック
	if (file.fail()) {
		assert(0);
	}

	// JSON文字列から解凍したデータ
	nlohmann::json deserialized;

	// 解凍
	file >> deserialized;

	// 正しいレベルデータファイルかチェック
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());

	// "name"を文字列として登録
	std::string name =
		deserialized["name"].get<std::string>();
	// 正しいレベルデータファイルかチェック
	assert(name.compare("scene") == 0);

	// レベルデータ格納用インスタンスを生成
	cLevelData* levelData = new cLevelData();

	// "objects"の全オブジェクトを走査
	for (nlohmann::json& object : deserialized["objects"]) {
		assert(object.contains("type"));

		// 種別を取得
		std::string type = object["type"].get<std::string>();

		// MESHの読み込み
		if (type.compare("MESH") == 0) {
			// 要素追加
			levelData->objects.emplace_back(cLevelData::sObjectData{});
			// 今追加した要素の参照を得る
			cLevelData::sObjectData& objectData = levelData->objects.back();

			if (object.contains("file_name")) {
				// ファイル名
				objectData.fileName = object["file_name"];
			}

			// トランスフォームのパラメータ読み込み
			nlohmann::json& transform = object["transform"];
			// 平行移動
			objectData.translation.x = static_cast<float>(transform["translation"][0]);
			objectData.translation.y = static_cast<float>(transform["translation"][2]);
			objectData.translation.z = static_cast<float>(transform["translation"][1]);

			// 回転角
			objectData.rotation.x = static_cast<float>(transform["rotation"][0]);
			objectData.rotation.y = static_cast<float>(transform["rotation"][2]);
			objectData.rotation.z = static_cast<float>(transform["rotation"][1]);

			// スケーリング
			objectData.scaling.x = static_cast<float>(transform["scaling"][0]);
			objectData.scaling.y = static_cast<float>(transform["scaling"][2]);
			objectData.scaling.z = static_cast<float>(transform["scaling"][1]);

		}

		// TODO: 子の処理　エンジン側が未対応のため後ほど
		
	}

	// レベルデータをメンバ変数にコピー
	levelData_ = levelData;

}
