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

	stage_ = std::make_unique<Stage>();
	stage_->Initialize();
}

void GameScene::Update(GameManager* gameManager) 
{
	gameManager;

	//camera_.translate_.x = player_->GetWorldTransform().translate_.x;
	camera_.Update();

	player_->Update();

	stage_->Update();

#ifdef _DEBUG
	ImGui::Begin("Camera");
	ImGui::DragFloat3("Translate", &camera_.translate_.x, 0.01f);
	ImGui::DragFloat3("Rotate", &camera_.rotate_.x, 0.01f);
	ImGui::End();
#endif
}

void GameScene::Draw() 
{
	player_->Draw(camera_);

	stage_->Draw(camera_);
}

GameScene::~GameScene() 
{
	
}