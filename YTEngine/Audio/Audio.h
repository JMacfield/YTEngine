/// 音関連のクラス

#pragma once


#define XAUDIO2_HELPER_FUNCTIONS
#include <xaudio2.h>
#include "xaudio2fx.h"
#include <fstream>
#include <x3daudio.h>
#include <mmsystem.h>
#include <cassert>
#include <array>
#include <XAPOFX.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib,"xaudio2.lib")




#include <mfapi.h>
#include <mfidl.h>


#pragma comment(lib, "Mf.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "Mfreadwrite.lib")
#pragma comment(lib, "mfuuid.lib")

#include <wrl.h>
using Microsoft::WRL::ComPtr;


#include <complex>
#include <vector>


#include "AudioStruct.h"

//LoadAudioの時に使う
enum EffectType {
	Filter,
	Reverb,
};


class Audio final {
private:
	//コンストラクタ
	Audio();

	//デストラクタ
	~Audio();
public:
	//インスタンスの取得
	static Audio* GetInstance();

	//コピーコンストラクタ禁止
	Audio(const Audio& obj) = delete;

	//代入演算子を無効にする
	Audio& operator=(const Audio& obj) = delete;

public:

	//初期化
	void Initialize();

#pragma region 基本セット

	//読み込み
	static uint32_t LoadWave(const char* fileName);

	//エフェクト版の読み込み
	static uint32_t LoadWave(const char* fileName, uint32_t effectType);

	static uint32_t LoadMP3(const WCHAR* fileName);


	//音声再生
	void PlayWave(uint32_t audioHandle, bool isLoop);
	//ループ回数あり
	void PlayWave(uint32_t audioHandle, int32_t loopCount);

	/// <summary>
	/// MP3再生
	/// </summary>
	/// <param name="audioHandle"></param>
	/// <param name="isLoop"></param>
	void PlayMP3(uint32_t audioHandle,bool isLoop);

	/// <summary>
	/// MP3再生(ループ回数設定版)
	/// </summary>
	/// <param name="audioHandle"></param>
	/// <param name="loopCount"></param>
	void PlayMP3(uint32_t audioHandle, uint32_t loopCount);


	/// <summary>
	/// 一時停止
	/// </summary>
	/// <param name="ハンドル名"></param>
	void PauseWave(uint32_t audioHandle);

	/// <summary>
	/// 再開
	/// </summary>
	/// <param name="ハンドル名"></param>
	void ResumeWave(uint32_t audioHandle);

	/// <summary>
	/// 停止
	/// </summary>
	/// <param name="ハンドル名"></param>
	void StopWave(uint32_t audioHandle);


#pragma endregion


#pragma region ループ


	/// <summary>
	/// ループから抜ける
	/// </summary>
	/// <param name="ハンドル名"></param>
	void ExitLoop(uint32_t audioHandle);


	/// <summary>
	/// 再生(後半ループ)
	/// </summary>
	/// <param name="ハンドル名"></param>
	/// <param name="始まる位置(秒)"></param>
	void AfterLoopPlayWave(uint32_t audioHandle, float second);

	/// <summary>
	/// 再生(前半ループ)
	/// </summary>
	/// <param name="ハンドル名"></param>
	/// <param name="ループ間の長さ(秒)"></param>
	void BeforeLoopPlayWave(uint32_t audioHandle, float lengthSecond);


	/// <summary>
	/// 部分ループ
	/// </summary>
	/// <param name="ハンドル名"></param>
	/// <param name="開始位置(秒)"></param>
	/// <param name="ループの長さ(秒)"></param>
	void PartlyLoopPlayWave(uint32_t audioHandle, float start, float lengthSecond);


#pragma endregion

	/// <summary>
	/// 音量調節
	/// </summary>
	/// <param name="ハンドル名"></param>
	/// <param name="音量"></param>
	void ChangeVolume(uint32_t audioHandle, float volume);

#pragma region ピッチ系


#pragma endregion


	static void CreateSubmixVoice(uint32_t channel);




	//解放
	void Release();

private:
	//音声データの開放
	void SoundUnload(uint32_t soundDataHandle);


private:
	//IXAudio2はCOMオブジェクトなのでComPtr管理
	ComPtr<IXAudio2> xAudio2_ = nullptr;
	//マスターボイス
	//最終的にここでまとめるよ(スピーカーみたいな感じだね)
	IXAudio2MasteringVoice* masterVoice_ = nullptr;
	

	//Panに必要な変数
	DWORD dwChannelMask_ = {};
	float outputMatrix_[8] = {};
	float left_ = 0.0f;
	float right_ = 0.0f;






	//構造体版
	//Texturemanagerとだいたい同じ感じにした
	//音声データの最大数
	static const int SOUND_DATE_MAX_ = 256;
	std::array<AudioInformation, SOUND_DATE_MAX_> audioInformation_{};

	//サブミックス(バス)
	static const int SUBMIXVOICE_AMOUNT_ = 64;
	std::array<IXAudio2SubmixVoice*, SUBMIXVOICE_AMOUNT_> submixVoice_{};


private:




	


};