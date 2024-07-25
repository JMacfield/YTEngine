#include "GameScene.h"
#include "TitleScene.h"

void TitleScene::Initialize()
{
	titleSpriteHandle_ = TextureManager::LoadTexture("Resources/Title/Title.png");
	titleSprite_.reset(Sprite::Create(titleSpriteHandle_, titleSpriteTransform_));

	selectSpriteHandle_ = TextureManager::LoadTexture("Resources/Title/StageSelect.png");
	selectSprite_.reset(Sprite::Create(selectSpriteHandle_, selectSpriteTransform_));
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

	if (Input::GetInstance()->IsTriggerKey(DIK_1))
	{
		isTrue = true;
	}
}

void TitleScene::Draw()
{
	if (isTrue == false)
	{
		titleSprite_->Draw();
	}

	if (isTrue == true)
	{
		selectSprite_->Draw();
	}
}