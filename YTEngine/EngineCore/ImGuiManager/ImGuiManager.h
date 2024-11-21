/// ImGui管理クラス

#pragma once

namespace YTEngine
{
	class ImGuiManager final
	{
	private:

		ImGuiManager();

		~ImGuiManager();

	public:

		ImGuiManager(const ImGuiManager& imGui) = delete;

		ImGuiManager& operator=(const ImGuiManager& imGui) = delete;

		static ImGuiManager* GetInstance();

	public:

		// 初期化
		void Initialize();

		// フレームの開始
		void BeginFrame();

		// 更新
		void Update();

		// 前描画
		void PreDraw();

		// 描画
		void Draw();

		// フレームの終了
		void EndFrame();

		// 解放
		void Release();

	private:

	};
}