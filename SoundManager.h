#pragma once

// Xaudio
#include <xaudio2.h>

#pragma comment(lib,"xaudio2.lib")

// C++
#include <fstream>
#include <wrl.h>

class cSoundManager {
public: // メンバ構造体
	// チャンクヘッダ
	struct ChunkHeader {
		char id[4]; // チャンク毎のID
		int32_t size; // チャンクサイズ
	};

	// RIFFヘッダチャンク
	struct RiffHeader {
		ChunkHeader chunk; // Riff
		char type[4]; // WAVE
	};

	// FMTチャンク
	struct FormatChunk {
		ChunkHeader chunk; // fmt
		WAVEFORMATEX fmt; // 波形フォーマット
	};

	// 音声データ
	struct SoundData {
		WAVEFORMATEX wfex;
		BYTE* pBuffer;
		unsigned int bufferSize;
	};

public: // 公開メンバ関数
	void Initialize();
	void Finalize();

	// 音声データ読み込み
	SoundData SoundLoadWave(const char* filename);

	// 音声データ解放
	void SoundUnload(SoundData* soundData);

	// 音声開放
	void SoundPlayWave(const SoundData& soundData);

private: // メンバ変数

	Microsoft::WRL::ComPtr<IXAudio2> xAudio2;
	IXAudio2MasteringVoice* masterVoice;
};