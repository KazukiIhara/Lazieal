#pragma once

// C++
#include <vector>
#include <string>

class cLevelData {
public: // 構造体
	// オブジェクトデータ型構造体
	struct sObjectData {
		std::string fileName;
	};
	
public: // 公開メンバ変数
	// オブジェクト
	std::vector<sObjectData> objects;
};

