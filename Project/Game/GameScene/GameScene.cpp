#include "GameScene/GameScene.h"
#include <imgui.h>
#include <Input.h>
#include "GlobalVariables.h"

#include "ModelManager.h"
#include "AnimationManager.h"

GameScene::GameScene() 
{

}

void GameScene::Initialize() 
{
	camera_.Initialize();
	
	player_ = std::make_unique<Player>();
	player_->Initialize();
}

void GameScene::Update(GameManager* gameManager) 
{
	gameManager;

	camera_.Update();

	player_->Update();

#ifdef _DEBUG


#endif
}

void GameScene::Draw() 
{
	player_->Draw(camera_);
}

GameScene::~GameScene() 
{
	
}