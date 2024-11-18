#include "PlayerTest.h"

void NewPlayer::Initialize()
{
	characterModelHandle_ = ModelManager::GetInstance()->LoadModelFile("Resources/Box", "Box.gltf");
	character_.reset(Model::Create(characterModelHandle_));

	characterTransform_.Initialize();
	characterTransform_.scale_ = { 1.0f,1.0f,1.0f };
	characterTransform_.rotate_ = { 0.0f,0.0f,0.0f };
	characterTransform_.translate_ = { 0.0f,0.0f,0.0f };
}

void NewPlayer::Update()
{

}

void NewPlayer::Draw(Camera& camera)
{
	character_->Draw(characterTransform_, camera);
}