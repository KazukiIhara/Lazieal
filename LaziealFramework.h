#pragma once

// 前方宣言
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
private: // メンバ変数
	// 終了リクエスト
	bool endRequest_ = true;
	// シーンファクトリー
	cAbstractSceneFactory* sceneFactory_ = nullptr;
};