#include "YTEngine.h"

static D3DResourceLeakChecker checker;

//Winodwsアプリでもエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	YTEngine* ytEngine = YTEngine::GetInstance();

	ytEngine->Execute();

	return 0;
}