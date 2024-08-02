#pragma once

// C++
#include <string>

// 前方宣言
class cWinAPI;
class cDirectXCommon;
class cSrvManager;
class cImGuiManager;
class cTextureManager;
class cPipelineManager;
class cAbstractSceneFactory;

// フレームワーク
class cLazieal {
public: // 仮想関数
	// 仮想デストラクタ
	virtual ~cLazieal() = default;
	// 初期化
	virtual void Initialize();
	// 終了
	virtual void Finalize();
	// 更新
	virtual void Update();
	// 描画
	virtual void Draw() = 0;
	// 終了チェック
	virtual bool IsEndRequest() {
		return endRequest_;
	}
public: // 公開メンバ関数
	// 実行
	void Run();
	// 描画前処理
	void PreDraw();
	// 描画後処理
	void PostDraw();
public: // 静的メンバ関数
#pragma region Texture
	// 画像読み込み関数
	static void LoadTexture(const std::string& filePath);

#pragma endregion

private: // メンバ変数
	// 終了リクエスト
	bool endRequest_ = false;
private: // 汎用クラスのポインタ
	// WinAPI
	cWinAPI* win_ = nullptr;
	// DirectXCommon
	cDirectXCommon* directX_ = nullptr;
	// SrvManager
	cSrvManager* srvManager_ = nullptr;
	// ImGuiManager
	cImGuiManager* imguiManager_ = nullptr;
	// TextureManager
	static cTextureManager* textureManager_;
	// グラフィックパイプライン
	cPipelineManager* pipelineManager_ = nullptr;
	// シーンファクトリー
	cAbstractSceneFactory* sceneFactory_ = nullptr;
};