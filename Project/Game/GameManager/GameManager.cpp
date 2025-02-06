/// ゲームシーンの管理クラス

#include "GameManager.h"
#include "GameScene/GameScene.h"
#include "GameScene/TitleScene.h"

//コンストラクタ
GameManager::GameManager() {
	
}
	
void GameManager::Initialize() {
	
	currentGamaScene_ = std::make_unique<TitleScene>();
	currentGamaScene_->Initialize();
}


void GameManager::Update() {
	currentGamaScene_->Update(this);
}

void GameManager::Draw() {
	currentGamaScene_->Draw();
}



void GameManager::ChangeScene(std::unique_ptr<IGameScene> newGameScene) {
	
	currentGamaScene_ = std::move(newGameScene);

	currentGamaScene_->Initialize();
	currentGamaScene_->Update(this);
}


//デストラクタ
GameManager::~GameManager() {

}