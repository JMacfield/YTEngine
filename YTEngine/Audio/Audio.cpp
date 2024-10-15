/// 音関連のクラス

#include "Audio.h"

#include <imgui.h>

static uint32_t audioIndex;

//コンストラクタ
Audio::Audio() {

}

Audio* Audio::GetInstance() {
	static Audio instance;
	return &instance;
}

void Audio::CreateSubmixVoice(uint32_t channel) {
	uint32_t channels = channel;
	uint32_t sampleRate = 44100;



	HRESULT hr = {};
	hr = Audio::GetInstance()->xAudio2_->CreateSubmixVoice(&Audio::GetInstance()->submixVoice_[channel], channels, sampleRate);
	assert(SUCCEEDED(hr));

}

//初期化

void Audio::Initialize() {

	
	MFStartup(MF_VERSION, MFSTARTUP_NOSOCKET);

	
	HRESULT hr;
	hr = XAudio2Create(&xAudio2_, 0, XAUDIO2_DEFAULT_PROCESSOR);
	assert(SUCCEEDED(hr));

	//マスターボイスを生成
	hr = xAudio2_->CreateMasteringVoice(&masterVoice_);
	assert(SUCCEEDED(hr));

	//スピーカ構成を取得
	masterVoice_->GetChannelMask(&dwChannelMask_);

	
	

	//一度全部0に初期化
	for (int i = 0; i < 8; i++) {
		outputMatrix_[i] = 0;
	}

	for (int i = 1; i < SUBMIXVOICE_AMOUNT_; ++i) {

		CreateSubmixVoice(i);
	}
	



}



#pragma region 実際に使う関数

#pragma region 基本セット
//読み込み
uint32_t Audio::LoadWave(const char* fileName) {


	for (int i = 0; i < SOUND_DATE_MAX_; i++) {
		if (Audio::GetInstance()->audioInformation_[i].name_ == fileName) {
			return Audio::GetInstance()->audioInformation_[i].audioHandle_;
		}
	}
	//audioHandle_++;
	audioIndex++;

	//記録
	Audio::GetInstance()->audioInformation_[audioIndex].name_ = fileName;
	Audio::GetInstance()->audioInformation_[audioIndex].audioHandle_ = audioIndex;


#pragma region １,ファイルオープン
	//ファイル入力ストリームのインスタンス
	std::ifstream file;
	//.wavファイルをバイナリモードで開く
	file.open(fileName, std::ios_base::binary);
	//ファイルオープン失敗を検出する
	assert(file.is_open());

#pragma endregion

#pragma region ２,wavデータ読み込み

	//RIFFヘッダーの読み込み
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	//ファイルがRIFFかチェック
	if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
		assert(0);
	}
	//タイプがWAVEかチェック
	if (strncmp(riff.type, "WAVE", 4) != 0) {
		assert(0);
	}

	//Formatチャンクの読み込み
	FormatChunk format = {};
	//チャンクヘッダーの確認
	file.read((char*)&format, sizeof(ChunkHeader));
	//何かここ空白入れないとダメらしい
	//後ろが4だからかな・・
	if (strncmp(format.chunk.id, "fmt ", 4) != 0) {
		assert(0);
	}

	//チャンク本体の読み込み
	assert(format.chunk.size <= sizeof(format.fmt));
	file.read((char*)&format.fmt, format.chunk.size);


	//Dataチャンクの読み込み
	ChunkHeader data;
	file.read((char*)&data, sizeof(data));
	//JUNKチャンクを検出した場合
	if (strncmp(data.id, "JUNK", 4) == 0) {
		//読み込み位置をJUNKチャンクの終わりまで進める
		file.seekg(data.size, std::ios_base::cur);
		//再読み込み
		file.read((char*)&data, sizeof(data));

	}

	//メインのデータチャンク
	if (strncmp(data.id, "data", 4) != 0) {
		assert(0);
	}

	//Dataチャンクのデータ部(波形データ)の読み込み
	char* pBuffer = new char[data.size];
	file.read(pBuffer, data.size);
#pragma endregion

#pragma region ３,Waveファイルを閉じる
	file.close();


#pragma endregion




#pragma region 読み込んだ音声データを返す

	Audio::GetInstance()->audioInformation_[audioIndex].soundData_.wfex = format.fmt;
	Audio::GetInstance()->audioInformation_[audioIndex].soundData_.pBuffer = reinterpret_cast<BYTE*>(pBuffer);
	Audio::GetInstance()->audioInformation_[audioIndex].soundData_.bufferSize = data.size;


	//波形フォーマットを基にSourceVoiceの生成
	HRESULT hr{};
	hr = Audio::GetInstance()->xAudio2_->CreateSourceVoice(
		&Audio::GetInstance()->audioInformation_[audioIndex].pSourceVoice_,
		&Audio::GetInstance()->audioInformation_[audioIndex].soundData_.wfex);
	assert(SUCCEEDED(hr));


	//フィルターを使う場合
	//後でFilterを使う場合のロードを作りたい
	hr = Audio::GetInstance()->xAudio2_->CreateSourceVoice(
		&Audio::GetInstance()->audioInformation_[audioIndex].pSourceVoice_,
		&Audio::GetInstance()->audioInformation_[audioIndex].soundData_.wfex, XAUDIO2_VOICE_USEFILTER, 16.0f);

	assert(SUCCEEDED(hr));

	return audioIndex;

#pragma endregion



}

uint32_t Audio::LoadWave(const char* fileName, uint32_t effectType) {
	effectType;
	
	for (int i = 0; i < SOUND_DATE_MAX_; i++) {
		if (Audio::GetInstance()->audioInformation_[i].name_ == fileName) {
			return Audio::GetInstance()->audioInformation_[i].audioHandle_;
		}
	}
	//audioHandle_++;
	audioIndex++;

	//記録
	Audio::GetInstance()->audioInformation_[audioIndex].name_ = fileName;
	Audio::GetInstance()->audioInformation_[audioIndex].audioHandle_ = audioIndex;


#pragma region １,ファイルオープン
	//ファイル入力ストリームのインスタンス
	std::ifstream file;
	//.wavファイルをバイナリモードで開く
	file.open(fileName, std::ios_base::binary);
	//ファイルオープン失敗を検出する
	assert(file.is_open());

#pragma endregion

#pragma region ２,wavデータ読み込み

	//RIFFヘッダーの読み込み
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	//ファイルがRIFFかチェック
	if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
		assert(0);
	}
	//タイプがWAVEかチェック
	if (strncmp(riff.type, "WAVE", 4) != 0) {
		assert(0);
	}

	//Formatチャンクの読み込み
	FormatChunk format = {};
	//チャンクヘッダーの確認
	file.read((char*)&format, sizeof(ChunkHeader));
	//何かここ空白入れないとダメらしい
	//後ろが4だからかな・・
	if (strncmp(format.chunk.id, "fmt ", 4) != 0) {
		assert(0);
	}

	//チャンク本体の読み込み
	assert(format.chunk.size <= sizeof(format.fmt));
	file.read((char*)&format.fmt, format.chunk.size);


	//Dataチャンクの読み込み
	ChunkHeader data;
	file.read((char*)&data, sizeof(data));
	//JUNKチャンクを検出した場合
	if (strncmp(data.id, "JUNK", 4) == 0) {
		//読み込み位置をJUNKチャンクの終わりまで進める
		file.seekg(data.size, std::ios_base::cur);
		//再読み込み
		file.read((char*)&data, sizeof(data));

	}

	//メインのデータチャンク
	if (strncmp(data.id, "data", 4) != 0) {
		assert(0);
	}

	//Dataチャンクのデータ部(波形データ)の読み込み
	char* pBuffer = new char[data.size];
	file.read(pBuffer, data.size);
#pragma endregion

#pragma region ３,Waveファイルを閉じる
	file.close();


#pragma endregion




#pragma region 読み込んだ音声データを返す

	Audio::GetInstance()->audioInformation_[audioIndex].soundData_.wfex = format.fmt;
	Audio::GetInstance()->audioInformation_[audioIndex].soundData_.pBuffer = reinterpret_cast<BYTE*>(pBuffer);
	Audio::GetInstance()->audioInformation_[audioIndex].soundData_.bufferSize = data.size;


	//波形フォーマットを基にSourceVoiceの生成
	HRESULT hr{};

	hr = Audio::GetInstance()->xAudio2_->CreateSourceVoice(
		&Audio::GetInstance()->audioInformation_[audioIndex].pSourceVoice_,
		&Audio::GetInstance()->audioInformation_[audioIndex].soundData_.wfex, XAUDIO2_VOICE_USEFILTER, 16.0f);

	assert(SUCCEEDED(hr));

	return audioIndex;

#pragma endregion


}

uint32_t Audio::LoadMP3(const WCHAR* fileName){
	
	


	
	for (int i = 0; i < SOUND_DATE_MAX_; i++) {
		if (Audio::GetInstance()->audioInformation_[i].mp3FileName_ == fileName) {
			return Audio::GetInstance()->audioInformation_[i].audioHandle_;
		}
	}

	audioIndex++;

	//記録
	Audio::GetInstance()->audioInformation_[audioIndex].mp3FileName_ = fileName;
	Audio::GetInstance()->audioInformation_[audioIndex].audioHandle_ = audioIndex;

	HRESULT hr = {};

	//ソースリーダーの作成
	hr = MFCreateSourceReaderFromURL(fileName, nullptr, &Audio::GetInstance()->audioInformation_[audioIndex].pSourceReader_);
	assert(SUCCEEDED(hr));



	//メディアタイプの取得
	IMFMediaType* pMFMediaType{ nullptr };
	MFCreateMediaType(&pMFMediaType);
	pMFMediaType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
	pMFMediaType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
	Audio::GetInstance()->audioInformation_[audioIndex].pSourceReader_->SetCurrentMediaType(DWORD(MF_SOURCE_READER_FIRST_AUDIO_STREAM), nullptr, pMFMediaType);

	pMFMediaType->Release();
	pMFMediaType = nullptr;
	Audio::GetInstance()->audioInformation_[audioIndex].pSourceReader_->GetCurrentMediaType(DWORD(MF_SOURCE_READER_FIRST_AUDIO_STREAM), &pMFMediaType);

	//オーディオデータ形式の作成
	WAVEFORMATEX* waveFormat{};
	MFCreateWaveFormatExFromMFMediaType(pMFMediaType, &waveFormat, nullptr);


	
	while (true)
	{
		IMFSample* pMFSample{ nullptr };
		DWORD dwStreamFlags{ 0 };
		Audio::GetInstance()->audioInformation_[audioIndex].pSourceReader_->ReadSample(DWORD(MF_SOURCE_READER_FIRST_AUDIO_STREAM), 0, nullptr, &dwStreamFlags, nullptr, &pMFSample);

		if (dwStreamFlags & MF_SOURCE_READERF_ENDOFSTREAM)
		{
			break;
		}

		IMFMediaBuffer* pMFMediaBuffer{ nullptr };
		pMFSample->ConvertToContiguousBuffer(&pMFMediaBuffer);

		BYTE* pBuffer{ nullptr };
		DWORD cbCurrentLength{ 0 };
		pMFMediaBuffer->Lock(&pBuffer, nullptr, &cbCurrentLength);

		Audio::GetInstance()->audioInformation_[audioIndex].mediaData.resize(Audio::GetInstance()->audioInformation_[audioIndex].mediaData.size() + cbCurrentLength);
		memcpy(Audio::GetInstance()->audioInformation_[audioIndex].mediaData.data() + Audio::GetInstance()->audioInformation_[audioIndex].mediaData.size() - cbCurrentLength, pBuffer, cbCurrentLength);

		pMFMediaBuffer->Unlock();

		pMFMediaBuffer->Release();
		pMFSample->Release();
	}

	Audio::GetInstance()->xAudio2_->CreateSourceVoice(&Audio::GetInstance()->audioInformation_[audioIndex].pSourceVoice_, waveFormat);


	return audioIndex;
}

//音声再生
void Audio::PlayWave(uint32_t audioHandle, bool isLoop) {

	//再生する波形データの設定
	XAUDIO2_BUFFER buffer{};
	buffer.pAudioData = audioInformation_[audioHandle].soundData_.pBuffer;
	buffer.AudioBytes = audioInformation_[audioHandle].soundData_.bufferSize;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	if (isLoop == true) {
		
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	}
	else{
		buffer.LoopCount = XAUDIO2_NO_LOOP_REGION;
	}

	HRESULT hr{};
	//Buffer登録
	hr = audioInformation_[audioHandle].pSourceVoice_->SubmitSourceBuffer(&buffer);
	//波形データの再生
	hr = audioInformation_[audioHandle].pSourceVoice_->Start(0);



	assert(SUCCEEDED(hr));
}

//ループ回数設定版
void Audio::PlayWave(uint32_t audioHandle, int32_t loopCount) {


	//再生する波形データの設定
	XAUDIO2_BUFFER buffer{};
	buffer.pAudioData = audioInformation_[audioHandle].soundData_.pBuffer;
	buffer.AudioBytes = audioInformation_[audioHandle].soundData_.bufferSize;
	buffer.Flags = XAUDIO2_END_OF_STREAM;

	buffer.LoopCount = loopCount - 1;


	HRESULT hr{};
	//Buffer登録
	hr = audioInformation_[audioHandle].pSourceVoice_->SubmitSourceBuffer(&buffer);
	//波形データの再生
	hr = audioInformation_[audioHandle].pSourceVoice_->Start(0);



	assert(SUCCEEDED(hr));
}

void Audio::PlayMP3(uint32_t audioHandle,bool isLoop){
	


	XAUDIO2_BUFFER buffer{};
	buffer.pAudioData = Audio::GetInstance()->audioInformation_[audioHandle].mediaData.data();
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.AudioBytes = sizeof(BYTE) * static_cast<UINT32>(Audio::GetInstance()->audioInformation_[audioHandle].mediaData.size());
	if (isLoop == true) {
		
		buffer.LoopCount = XAUDIO2_LOOP_INFINITE;
	}
	else{
		buffer.LoopCount = XAUDIO2_NO_LOOP_REGION;
	}


	HRESULT hr{};

	hr = Audio::GetInstance()->audioInformation_[audioHandle].pSourceVoice_->SubmitSourceBuffer(&buffer);

	//波形データの再生
	hr = audioInformation_[audioHandle].pSourceVoice_->Start(0);
	assert(SUCCEEDED(hr));
}

void Audio::PlayMP3(uint32_t audioHandle, uint32_t loopCount){
	

	XAUDIO2_BUFFER buffer{};
	buffer.pAudioData = Audio::GetInstance()->audioInformation_[audioHandle].mediaData.data();
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.AudioBytes = sizeof(BYTE) * static_cast<UINT32>(Audio::GetInstance()->audioInformation_[audioHandle].mediaData.size());
	
	buffer.LoopCount = loopCount - 1;


	HRESULT hr{};

	hr = Audio::GetInstance()->audioInformation_[audioHandle].pSourceVoice_->SubmitSourceBuffer(&buffer);

	//波形データの再生
	hr = audioInformation_[audioHandle].pSourceVoice_->Start(0);
	assert(SUCCEEDED(hr));
}

void Audio::PauseWave(uint32_t audioHandle) {
	HRESULT hr{};
	
	hr = audioInformation_[audioHandle].pSourceVoice_->Stop(XAUDIO2_PLAY_TAILS);
	assert(SUCCEEDED(hr));
}

void Audio::ResumeWave(uint32_t audioHandle) {
	

	HRESULT hr{};
	//波形データの再生
	hr = audioInformation_[audioHandle].pSourceVoice_->Start(0);
	assert(SUCCEEDED(hr));
}

//音声停止
void Audio::StopWave(uint32_t audioHandle) {
	HRESULT hr{};
	hr = audioInformation_[audioHandle].pSourceVoice_->Stop();
	assert(SUCCEEDED(hr));
}

#pragma endregion


#pragma region ループ
void Audio::ExitLoop(uint32_t audioHandle) {
	HRESULT hr{};
	//ExitLoop関数でループを抜ける
	hr = audioInformation_[audioHandle].pSourceVoice_->ExitLoop();
	assert(SUCCEEDED(hr));
}


void Audio::AfterLoopPlayWave(uint32_t audioHandle, float second) {
	
	XAUDIO2_BUFFER buffer{};
	buffer.pAudioData = audioInformation_[audioHandle].soundData_.pBuffer;
	buffer.AudioBytes = audioInformation_[audioHandle].soundData_.bufferSize;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	//ここでループ回数を設定
	buffer.LoopCount = XAUDIO2_LOOP_INFINITE;

	
	int samplingRate = Audio::GetInstance()->audioInformation_[audioIndex].soundData_.wfex.nSamplesPerSec;

	//ここでループしたい位置を設定してあげる
	buffer.LoopBegin = uint32_t(second * samplingRate);



	HRESULT hr{};
	//Buffer登録
	hr = audioInformation_[audioHandle].pSourceVoice_->SubmitSourceBuffer(&buffer);
	//波形データの再生
	hr = audioInformation_[audioHandle].pSourceVoice_->Start(0);



	assert(SUCCEEDED(hr));

}


void Audio::BeforeLoopPlayWave(uint32_t audioHandle, float lengthSecond) {
	
	XAUDIO2_BUFFER buffer{};
	buffer.pAudioData = audioInformation_[audioHandle].soundData_.pBuffer;
	buffer.AudioBytes = audioInformation_[audioHandle].soundData_.bufferSize;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	//ここでループ回数を設定
	buffer.LoopCount = XAUDIO2_LOOP_INFINITE;

	
	int samplingRate = Audio::GetInstance()->audioInformation_[audioIndex].soundData_.wfex.nSamplesPerSec;


	buffer.LoopBegin = 0;
	buffer.LoopLength = uint32_t(lengthSecond * samplingRate);



	HRESULT hr{};
	//Buffer登録
	hr = audioInformation_[audioHandle].pSourceVoice_->SubmitSourceBuffer(&buffer);
	assert(SUCCEEDED(hr));
	//波形データの再生
	hr = audioInformation_[audioHandle].pSourceVoice_->Start(0);



	assert(SUCCEEDED(hr));

}


void Audio::PartlyLoopPlayWave(uint32_t audioHandle, float start, float lengthSecond) {
	
	XAUDIO2_BUFFER buffer{};
	buffer.pAudioData = audioInformation_[audioHandle].soundData_.pBuffer;
	buffer.AudioBytes = audioInformation_[audioHandle].soundData_.bufferSize;
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	//ここでループ回数を設定
	buffer.LoopCount = XAUDIO2_LOOP_INFINITE;

	
	int samplingRate = Audio::GetInstance()->audioInformation_[audioIndex].soundData_.wfex.nSamplesPerSec;

	
	buffer.LoopBegin = uint32_t(start * samplingRate);;
	buffer.LoopLength = uint32_t(lengthSecond * samplingRate);



	HRESULT hr{};
	//Buffer登録
	hr = audioInformation_[audioHandle].pSourceVoice_->SubmitSourceBuffer(&buffer);
	//波形データの再生
	hr = audioInformation_[audioHandle].pSourceVoice_->Start(0);



	assert(SUCCEEDED(hr));
}

#pragma endregion


void Audio::ChangeVolume(uint32_t audioHandle, float volume) {

	HRESULT hr = {};
	hr = audioInformation_[audioHandle].pSourceVoice_->SetVolume(volume);
	assert(SUCCEEDED(hr));
}



#pragma endregion



void Audio::SoundUnload(uint32_t soundDataHandle) {
	//バッファのメモリを解放
	delete[] Audio::GetInstance()->audioInformation_[soundDataHandle].soundData_.pBuffer;
	Audio::GetInstance()->audioInformation_[soundDataHandle].soundData_.pBuffer = 0;
	Audio::GetInstance()->audioInformation_[soundDataHandle].soundData_.bufferSize = 0;
	Audio::GetInstance()->audioInformation_[soundDataHandle].soundData_.wfex = {};

}

//解放
void Audio::Release() {
	//解放
	for (int i = 0; i < SOUND_DATE_MAX_; i++) {
		//中身が入っていたらしっかり解放
		if (audioInformation_[i].pSourceReader_ != nullptr) {
			audioInformation_[i].pSourceReader_->Release();
		}
		if (audioInformation_[i].pSourceVoice_ != nullptr) {
			audioInformation_[i].pSourceVoice_->DestroyVoice();
		}
	}


	//XAudio2解放
	xAudio2_.Reset();

	for (int i = 0; i < SOUND_DATE_MAX_; i++) {
		SoundUnload(i);
	}


	MFShutdown();
}

//デストラクタ
Audio::~Audio() {

}