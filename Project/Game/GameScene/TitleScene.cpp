#include "GameScene.h"
#include "TitleScene.h"

void TitleScene::Initialize()
{
	titleSprite_ = std::make_unique<Sprite>();

	titleSpriteHandle_ = TextureManager::LoadTexture("Resources/Title/Title.png");
	titleSprite_->Create(titleSpriteHandle_, titleSpriteTransform_);

	titleSprite_->SetInvisible(true);
	titleSprite_->SetColor({ 0.0f,0.0f,0.0f,1.0f });

	//titleSprite_->SetTextureSize({ 1280.0f,720.0f });
	//titleSprite_->SetAnchorPoint({ 0.5f,0.5f });
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