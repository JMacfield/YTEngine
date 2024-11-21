/// エンジン基底クラス

#pragma once

#include "GameManager/GameManager.h"
#include "WinApp.h"
#include "DirectXCommon.h"

namespace YTEngine
{
	class MyEngine final
	{
	private:

		//コンストラクタ
		MyEngine() = default;

		//デストラクタ
		~MyEngine();

	public:

		//インスタンス
		static MyEngine* GetInstance();

		MyEngine(const MyEngine& YTEngine) = delete;

		MyEngine& operator=(const MyEngine& YTEngine) = delete;

	public:

		/// <summary>
		/// 実行
		/// </summary>
		void Execute();

	private:

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();

		/// <summary>
		/// フレームの開始
		/// </summary>
		void BeginFrame();

		/// <summary>
		/// フレーム更新
		/// </summary>
		void Update();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

		/// <summary>
		/// フレームの終了
		/// </summary>
		void EndFrame();

		/// <summary>
		/// 解放
		/// </summary>
		void Release();

	private:

		GameManager* gameManager_ = nullptr;
	};
}