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

	//jsonLoader_ = new JsonLoader();
	//jsonLoader_->Load("Resources/Editor", "aaaa.json");

	/*line_ = std::make_unique<DrawSystem>();
	line_->Initialize();*/
}

void GameScene::Update(GameManager* gameManager) 
{
	gameManager;

	camera_.Update();

	player_->Update();

	stage_->Update();

	//jsonLoader_->Update();

	if (player_->GetWorldTransform().translate_.x > 3.3f) 
	{
		gameManager->ChangeScene(new GameScene1);
	}

	if (IsCollision(player_->GetCollision(), stage_->GetCollision()))
	{
		return;
	}

#ifdef _DEBUG
	

#endif
}

void GameScene::Draw() 
{
	player_->Draw(camera_);

	stage_->Draw(camera_);

	//jsonLoader_->Draw(camera_);

	//line_->Draw({ -1.0f,0.0f,0.0f }, { 1.0f,0.0f,0.0f }, camera_);
}