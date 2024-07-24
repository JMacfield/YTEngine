#include "GameScene.h"
#include "TitleScene.h"

void TitleScene::Initialize()
{
	titleSpriteHandle_ = TextureManager::GetInstance()->LoadTexture("Resources/Title/Title.png");

	titleSprite_.reset(Sprite::Create(titleSpriteHandle_, titleSpriteTransform_));
	titleSpriteTransform_ = { 0.0f,0.0f };
}

void TitleScene::Update(GameManager* gameManager)
{
	ImGui::Begin("Sprite");
	ImGui::DragFloat2("Transform", &titleSpriteTransform_.x, 0.01f);
	ImGui::End();

	if (Input::GetInstance()->IsTriggerKey(DIK_SPACE))
	{
		gameManager->ChangeScene(new GameScene);
	}
}

void TitleScene::Draw()
{
	titleSprite_->Draw();
}