#pragma once

// C++
#include <vector>
#include <string>

// MyHedder
#include "MathFunction.h"

class cLevelData {
public: // 構造体
	// オブジェクトデータ型構造体
	struct sObjectData {
		std::string fileName;
		Vector3 translation;
		Vector3 rotation;
		Vector3 scaling;
	};
	
public: // 公開メンバ変数
	// オブジェクト
	std::vector<sObjectData> objects;
};

