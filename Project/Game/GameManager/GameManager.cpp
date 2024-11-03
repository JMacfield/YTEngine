/// ゲームシーンの管理クラス

#include "GameManager.h"
#include "GameScene/GameScene.h"
#include "GameScene/TitleScene.h"
#include "GameScene/TestScene.h"

//コンストラクタ
GameManager::GameManager() {
	
}
	
void GameManager::Initialize() {
	
	currentGamaScene_ = new TestScene();
	currentGamaScene_->Initialize();

}


void GameManager::Update() {
	currentGamaScene_->Update(this);
}

void GameManager::Draw() {
	currentGamaScene_->Draw();
}



void GameManager::ChangeScene(IGameScene* newGameScene) {
	
	delete currentGamaScene_;
	currentGamaScene_ = newGameScene;
	
	currentGamaScene_->Initialize();
}


//デストラクタ
GameManager::~GameManager() {
	delete currentGamaScene_;

}
