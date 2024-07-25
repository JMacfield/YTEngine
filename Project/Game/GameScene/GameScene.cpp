#include "GameScene/GameScene.h"
#include "GameScene/ClearScene.h"
#include "GameScene/TitleScene.h"

#include <imgui.h>
#include <Input.h>

#include "GlobalVariables.h"

#include "ModelManager.h"
#include "AnimationManager.h"

void GameScene::Initialize() 
{
	camera_.Initialize();
	camera_.translate_.y = 4.0f;
	camera_.translate_.z = -14.0f;
	camera_.rotate_.x = 0.1f;
	
	player_ = std::make_unique<Player>();
	player_->Initialize();

	stage_ = std::make_unique<Stage>();
	stage_->Initialize();
}

void GameScene::Update(GameManager* gameManager) 
{
	gameManager;

	camera_.Update();

	player_->Update();

	stage_->Update();

	if (player_->GetWorldTransform().translate_.x > 3.3f)
	{
		gameManager->ChangeScene(new TitleScene);
	}

	if (player_->GetWorldTransform().translate_.y < -3.0f) 
	{
		gameManager->ChangeScene(new TitleScene);
	}

#ifdef _DEBUG
	ImGui::Begin("Camera");
	ImGui::DragFloat3("Translate", &camera_.translate_.x, 0.01f);
	ImGui::DragFloat3("Rotate", &camera_.rotate_.x, 0.01f);
	ImGui::End();
#endif

	if (IsCollision(player_->GetCollision(), stage_->GetCollision()))
	{
		stage_->SetGoalColor({ 0.0f,1.0f,0.0f,1.0f });
	}
	else
	{
		stage_->SetGoalColor({ 1.0f,0.0f,0.0f,1.0f });
	}
}

void GameScene::Draw() 
{
	player_->Draw(camera_);

	stage_->Draw(camera_);
}