/// ゲームシーンの管理クラス

#pragma once

#include <memory>

#include "IGameScene.h"

class GameManager {
public:
	
	//コンストラクタ
	GameManager();

	//初期化
	void Initialize();

	//シーンチェンジ
	void ChangeScene(std::unique_ptr<IGameScene> newGameScene);

	//更新
	void Update();

	//描画
	void Draw();

	//デストラクタ
	~GameManager();

private:

	//StatePatternに必要な変数
	std::unique_ptr<IGameScene> currentGamaScene_ = nullptr;
	
};