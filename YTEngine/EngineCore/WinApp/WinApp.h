/// Windowsアプリケーションクラス

#pragma once

#include <Windows.h>
#include <WinUser.h>
#include <cstdint>

#include <imgui.h>
#include <imgui_impl_dx12.h>
#include <imgui_impl_win32.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd,UINT msg,WPARAM wParam,LPARAM lParam);

class WinApp final
{
private:

	WinApp();

	~WinApp();

public:

	WinApp(const WinApp& winApp) = delete;

	WinApp& operator=(const WinApp& winApp) = delete;

	static WinApp* GetInstance();

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	// ウィンドウクラスの登録
	void RegisterWindowsClass();

	// ウィンドウを表示
	void DisplayWindow();

public:

	// 初期化
	void Initialize(const wchar_t* title, int32_t clientWidth,int32_t clientHeight);

	// ウィンドウメッセージ
	void WindowsMSG(MSG& msg);

	// ウィンドウを閉じる
	void Close();

#pragma region Getter
	int GetClientWidth() { return clientWidth_; }
	int GetClientHeight() { return clientHeight_; }

	HWND GetHwnd() { return hwnd_; }

	HINSTANCE GetHInstance() { return wc_.hInstance; }

	wchar_t* SetClassName(wchar_t* name) { title_ = name; }
#pragma endregion

private:

	const wchar_t* title_ = L"YTEngine";
	
	int32_t clientWidth_=0;
	int32_t clientHeight_=0;

	HWND hwnd_=0;

	WNDCLASS wc_{};
};