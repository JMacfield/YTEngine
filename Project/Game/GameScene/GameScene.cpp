#include "GameScene/GameScene.h"
#include "GameScene/ClearScene.h"
#include "GameScene/TitleScene.h"
#include "GameScene/GameScene1.h"

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

	/*surfaceBackHandle_ = ModelManager::GetInstance()->LoadModelFile("Resources/Plane", "Plane.gltf");
	surfaceBack_.reset(Model::Create(surfaceBackHandle_));

	surfaceBackTransform_.Initialize();
	surfaceBackTransform_.translate_ = { 0.0f,0.0f,0.8f };
	surfaceBackTransform_.rotate_ = { -1.44f,0.0f,0.0f };
	surfaceBackTransform_.scale_ = { 10.260f,6.140f,7.630f };
	surfaceBack_->SetColor({ 1.0f,1.0f,0.0f,1.0f });*/
}

void GameScene::Update(GameManager* gameManager) 
{
	gameManager;

	camera_.Update();

	player_->Update();

	stage_->Update();

	//surfaceBackTransform_.Update();

	if (player_->GetWorldTransform().translate_.x > 3.3f) 
	{
		gameManager->ChangeScene(new GameScene1);
	}

#ifdef _DEBUG
	/*ImGui::Begin("Camera");
	ImGui::DragFloat3("Translate", &camera_.translate_.x, 0.01f);
	ImGui::DragFloat3("Rotate", &camera_.rotate_.x, 0.01f);
	ImGui::End();*/
#endif
}

void GameScene::Draw() 
{
	player_->Draw(camera_);

	stage_->Draw(camera_);

	//surfaceBack_->Draw(surfaceBackTransform_, camera_);
}