// This
#include "LevelDataLoader.h"

// C++
#include <fstream>
#include <cassert>

// Json
#include <json.hpp>

void cLevelDataLoader::LoadLevelData(const std::string& fileName) {

	// 連結してフルパスを得る
	const std::string fullpath = "LevelData" + fileName + ".json";

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

	// "objects"の全オブジェクトを走査
	for (nlohmann::json& object : deserialized["objects"]) {
		assert(object.contains("type"));

		// 種別を取得
		std::string type = object["type"].get<std::string>();

		// MESHの読み込み
		if (type.compare("MESH") == 0) {
			// 要素追加

		}

	}

}
