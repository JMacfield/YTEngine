#include "GameScene.h"
#include "TitleScene.h"

void TitleScene::Initialize()
{
	camera_.Initialize();
	camera_.translate_.y = 4.0f;
	camera_.translate_.z = -14.0f;
	camera_.rotate_.x = 0.1f;

	testModelHandle_ = ModelManager::GetInstance()->LoadModelFile("Resources/Editor/Test", "Test.obj");
	testModel_.reset(Model::Create(testModelHandle_));

	testModelTransform_.Initialize();
	testModelTransform_.translate_ = { 0.0f,0.0f,0.0f };
	testModelTransform_.scale_ = { 1.0f,1.0f,1.0f };

	jsonLoader_ = new JsonLoader();
	jsonLoader_->Load("Resources/Editor", "aaaa.json");
}

void TitleScene::Update(GameManager* gameManager)
{
	gameManager;

	camera_.Update();

	testModelTransform_.Update();

	jsonLoader_->Update();
}

void TitleScene::Draw()
{
	//testModel_->Draw(testModelTransform_, camera_);

	jsonLoader_->Draw(camera_);
}