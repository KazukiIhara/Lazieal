#pragma once

// C++
#include <string>

// 前方宣言
class cLevelData;

class cLevelDataManager {
public:
	// レベルデータファイルの読み込み
	void LoadLevelData(const std::string& fileName);

private:
	cLevelData *levelData_;
};

