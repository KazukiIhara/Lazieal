#pragma once
// Include
#define DIRECTINPUT_VERSION	0x0800 // DirectInputのバージョン設定
#include <dinput.h>
#include <wrl.h> // Comptr

// pragma comment
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

class cWinAPI;

// DirectInputクラス
class cDirectInput {
public: // テンプレート
	// エイリアステンプレート
	// Microsoft::WRL省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:
	// 初期化
	void Initialize(cWinAPI* win);
	// 更新
	void Update();

	// キーの押下をチェック
	// 押しているとき
	bool PushKey(BYTE keyNumber);
	// 押されたとき
	bool TriggerKey(BYTE keyNumber);
	// 離したとき
	bool ReleaseKey(BYTE keyNumber);

private:

	cWinAPI* win_ = nullptr;

	// インスタンス
	ComPtr <IDirectInput8> directInput = nullptr;

	// キーボード
	ComPtr <IDirectInputDevice8> keybord = nullptr;

	// 現在フレームのキー入力
	BYTE key[256];
	// 1フレーム前のキー入力
	BYTE preKey[256];
};

