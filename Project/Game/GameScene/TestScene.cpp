/// テストシーン

#include "TestScene.h"

#include <imgui.h>
#include <Input.h>
#include "GlobalVariables.h"

#include "ModelManager.h"
#include "AnimationManager.h"

void TestScene::Initialize()
{
	camera_.Initialize();
	camera_.translate_.y = 4.0f;
	camera_.translate_.z = -14.0f;
	camera_.rotate_.x = 0.1f;

	whiteHandle_ = TextureManager::LoadTexture("Resources/white.png");
	whiteTransform_ = { 0.0f,0.0f };

	white_.reset(Sprite::Create(whiteHandle_, whiteTransform_));
}

void TestScene::Update(GameManager* gameManager)
{
	gameManager;

	camera_.Update();

#ifdef _DEBUG


#endif
}

void TestScene::Draw()
{
	//white_->Draw();
}