#pragma once

// 前方宣言
class cWinAPI;
class cDirectXCommon;
class cAbstractSceneFactory;

// フレームワーク
class cLaziealFramework {
public: // 仮想関数
	// 仮想デストラクタ
	virtual ~cLaziealFramework() = default;
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

private: // メンバ変数
	// 終了リクエスト
	bool endRequest_ = false;

private: // 汎用クラスのポインタ
	// WinAPI
	cWinAPI* win_ = nullptr;
	// DirectXCommon
	cDirectXCommon* directX_ = nullptr;
	// シーンファクトリー
	cAbstractSceneFactory* sceneFactory_ = nullptr;
};