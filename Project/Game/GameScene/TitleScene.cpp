#include "GameScene.h"
#include "TitleScene.h"
#include "SelectScene.h"

void TitleScene::Initialize()
{
	titleSpriteHandle_ = TextureManager::LoadTexture("Resources/Title/Title.png");
	titleSprite_.reset(Sprite::Create(titleSpriteHandle_, titleSpriteTransform_));
}

void TitleScene::Update(GameManager* gameManager)
{
	XINPUT_STATE joyState{};

	if (Input::GetInstance()->GetJoystickState(joyState))
	{
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			gameManager->ChangeScene(new SelectScene);
		}
	}
}

void TitleScene::Draw()
{
	titleSprite_->Draw();
}