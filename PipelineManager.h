#pragma once

// C++
#include <string>
#include <wrl.h>

// DirectX
#include <d3d12.h>
#include <dxcapi.h>

// 前方宣言
class cDirectXCommon;

class cPipelineManager {
public: // 列挙型
	// ブレンドモード
	enum eBlendMode {
		kBlendModeNone,
		kBlendModeNormal,
		kBlendModeAdd,
		kBlendModeSubtract,
		kBlendModeMultiply,
		kBlendModeScreen,
	};

	// パイプラインの種類
	enum ePipelineState {
		kObject3d,
		kObject3dUnUV,
		kObject2d,
	};

public: // インスタンスセット関数
	// DirectXCommon
	void SetDirectXCommon(cDirectXCommon* directX) {
		directX_ = directX;
	}

public: // 公開メンバ変数
	cPipelineManager();
	~cPipelineManager();

	// 初期化
	void Initialize();

	// ルートシグネイチャのゲッター
	ID3D12RootSignature* GetRootSignature(ePipelineState pipelineState) {
		return rootSignature_[pipelineState].Get();
	}

	// パイプラインステイトのゲッター
	ID3D12PipelineState* GetPipelineState(ePipelineState pipelineState, eBlendMode blendMode);

#pragma region Common
	// BlendStateの設定
	D3D12_BLEND_DESC BlendStateSetting(uint32_t blendModeNum);
#pragma endregion

#pragma region Shader
	// Dxコンパイラの初期化
	void InitializeDxCompiler();
	// シェーダーのコンパイルをまとめる関数
	void CompileShaders();

	// シェーダーをコンパイルする関数
	Microsoft::WRL::ComPtr<ID3DBlob> CompileShader(
		//CompileするShaderファイルへのパス
		const std::wstring& filePath,
		//Compileに使用するProfile
		const wchar_t* profile,
		//初期化で生成したものを3つ
		IDxcUtils* dxcUtils,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHandler);
#pragma endregion

#pragma region Object3D
	// ルートシグネイチャを作成する関数
	void CreateObject3DRootSignature();
	// パイプラインを生成する関数
	void CreateObject3DGrapchicsPipelineStateObject();
	// DepthStencilStateの設定
	D3D12_DEPTH_STENCIL_DESC Object3DDepthStecilDescSetting();
	// InputLayoutの設定
	D3D12_INPUT_LAYOUT_DESC Object3DInputLayoutSetting();
	// RasterizerStateの設定
	D3D12_RASTERIZER_DESC Object3DRasterizerStateSetting();
	// シェーダーたちをコンパイルする関数
	void CompileObject3DShaders();
#pragma endregion

#pragma region Object3DUnUV
	// ルートシグネイチャを作成する関数
	void CreateObject3DUnUVRootSignature();
	// パイプラインを生成する関数
	void CreateObject3DUnUVGrapchicsPipelineStateObject();
	// DepthStencilStateの設定
	D3D12_DEPTH_STENCIL_DESC Object3DUnUVDepthStecilDescSetting();
	// InputLayoutの設定
	D3D12_INPUT_LAYOUT_DESC Object3DUnUVInputLayoutSetting();
	// RasterizerStateの設定
	D3D12_RASTERIZER_DESC Object3DUnUVRasterizerStateSetting();
	// シェーダーたちをコンパイルする関数
	void CompileObject3DUnUVShaders();
#pragma endregion

#pragma region Object2D
	// ルートシグネイチャを作成する関数
	void CreateObject2DRootSignature();
	// パイプラインを生成する関数
	void CreateObject2DGrapchicsPipelineStateObject();
	// DepthStencilStateの設定
	D3D12_DEPTH_STENCIL_DESC Object2DDepthStecilDescSetting();
	// InputLayoutの設定
	D3D12_INPUT_LAYOUT_DESC Object2DInputLayoutSetting();
	// RasterizerStateの設定
	D3D12_RASTERIZER_DESC Object2DRasterizerStateSetting();
	// シェーダーたちをコンパイルする関数
	void CompileObject2DShaders();
#pragma endregion

private: // 静的メンバ変数
	// ブレンドモードの数
	static const uint32_t kBlendModeNum = 6;
	// パイプラインの種類の数
	static const uint32_t kPipelineStateNum = 3;

private: // メンバ変数

	// ルートシグネイチャ
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature_[kPipelineStateNum];
	// グラフィックスパイプライン
	Microsoft::WRL::ComPtr<ID3D12PipelineState> graphicsPipelineState_[kPipelineStateNum][kBlendModeNum];

	// シグネイチャの塊
	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	// シェーダー
	IDxcUtils* dxcUtils = nullptr;
	IDxcCompiler3* dxcCompiler = nullptr;
	IDxcIncludeHandler* includeHandler = nullptr;

#pragma region Object3d
	// Object3D用頂点シェーダー
	Microsoft::WRL::ComPtr<ID3DBlob> object3DVertexShaderBlob_;
	// Object3D用ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3DBlob> object3DPixelShaderBlob_;
#pragma endregion

#pragma region Object3dUnUV
	// Object3DUnUV用頂点シェーダー
	Microsoft::WRL::ComPtr<ID3DBlob> object3DUnUVVertexShaderBlob_;
	// Object3D用UnUvピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3DBlob> object3DUnUVPixelShaderBlob_;
#pragma endregion

#pragma region Object2d
	// Object2D用頂点シェーダー
	Microsoft::WRL::ComPtr<ID3DBlob> object2DVertexShaderBlob_;
	// Object2D用ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3DBlob> object2DPixelShaderBlob_;
#pragma endregion

private: // インスタンスを受け取るポインタ
	// DirectX
	cDirectXCommon* directX_ = nullptr;

};
