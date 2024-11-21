#include "YTEngine.h"

using namespace YTEngine;

static D3DResourceLeakChecker checker;

//Winodwsアプリでもエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	MyEngine* myEngine = MyEngine::GetInstance();
	
	myEngine->Execute();

	return 0;
}