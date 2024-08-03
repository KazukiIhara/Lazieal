#pragma once

// C++
#include <string>
#include <unordered_map>

// MyHedder
#include "WorldTransform.h"
#include "TextureManager.h"
#include "PipelineManager.h"

// 前方宣言
class cWinAPI;
class cDirectXCommon;
class cCamera;
class cSrvManager;
class cImGuiManager;
class cTextureManager;
class cPipelineManager;
class cModelManager;
class cModel;
class cObject3dSystem;
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
#pragma region DirectXCommon
	// デバイス取得
	static ID3D12Device* GetDirectXDevice();
	// コマンドリスト取得関数
	static ID3D12GraphicsCommandList* GetDirectXCommandList();
#pragma endregion

#pragma region SrvManager
	// ディスクリプターテーブルのセット
	static void SetGraphicsRootDescriptorTable(UINT rootParameterIndex, uint32_t srvIndex);
#pragma endregion

#pragma region TextureManager
	// 画像読み込み関数
	static void LoadTexture(const std::string& filePath);
	// 画像取得関数
	static std::unordered_map<std::string, cTextureManager::Texture>& GetTexture();
#pragma endregion
#pragma region PipelineManager
	// パイプライン取得関数
	static ID3D12PipelineState* GetPipelineState(cPipelineManager::ePipelineState pipelineState, cPipelineManager::eBlendMode blendMode);
#pragma endregion

#pragma region ModelManager
	// モデルの検索
	static cModel* FindModel(const std::string& filePath);
#pragma endregion

#pragma region Object3d
	// 3dオブジェクト描画前処理
	static void PreDrawObject3D();
	// 3dオブジェクトのデフォルトカメラ取得
	static cCamera* GetDefaultCamera();
#pragma endregion

private: // メンバ変数
	// 終了リクエスト
	bool endRequest_ = false;
private: // 汎用クラスのポインタ
	// WinAPI
	cWinAPI* win_ = nullptr;
	// DirectXCommon
	static cDirectXCommon* directX_;
	// SrvManager
	static cSrvManager* srvManager_;
	// ImGuiManager
	cImGuiManager* imguiManager_ = nullptr;
	// TextureManager
	static cTextureManager* textureManager_;
	// ModelManager
	static cModelManager* modelManager_;
	// グラフィックパイプライン
	static cPipelineManager* pipelineManager_;
	// デバッグカメラのトランスフォーム
	cWorldTransform debugCameraTransform_{};
	// デバッグカメラ
	cCamera* debugCamera_ = nullptr;
	// Object3dSystem
	static cObject3dSystem* object3dSystem_;
	// シーンファクトリー
	cAbstractSceneFactory* sceneFactory_ = nullptr;
};