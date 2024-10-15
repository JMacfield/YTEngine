/// セレクトシーン

#include "GameScene.h"
#include "SelectScene.h"

void SelectScene::Initialize()
{
	// ステージの画像
	selectSpriteHandle_[0] = TextureManager::LoadTexture("Resources/Title/StageSelect.png");
	selectSpriteHandle_[1] = TextureManager::LoadTexture("Resources/Title/StageSelect1.png");
	selectSpriteHandle_[2] = TextureManager::LoadTexture("Resources/Title/StageSelect2.png");
	selectSpriteHandle_[3] = TextureManager::LoadTexture("Resources/Title/StageSelect3.png");

	for (int i = 0; i < 3; i++)
	{
		selectSpriteTransform_[i] = { i * 1280.0f, 0.0f };

		selectSprite_[i].reset(Sprite::Create(selectSpriteHandle_[i], selectSpriteTransform_[i]));
	}
}

void SelectScene::Update(GameManager* gameManager)
{
	XINPUT_STATE joyState{};
	
	// ステージ選択操作
	if (Input::GetInstance()->GetJoystickState(joyState))
	{
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			gameManager->ChangeScene(new GameScene);
		}

		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT && isCanControl_ == true)
		{
			isSpriteMovingLeft_ = true;
		}

		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT && isCanControl_ == true)
		{
			isSpriteMovingRight_ = true;
		}
	}

	// ステージ画像左送り
	if (isSpriteMovingLeft_ == true)
	{
		isCanControl_ = false;
		moveNumLeft_ -= 10.0f;

		for (int i = 0; i < 3; i++)
		{
			selectSpriteTransform_[i].x += 10.0f;
		}

		if (moveNumLeft_ == 0.0f)
		{
			isCanControl_ = true;
			isSpriteMovingLeft_ = false;
			moveNumLeft_ = 1280.0f;
		}
	}

	// ステージ画像右送り
	if (isSpriteMovingRight_ == true)
	{
		isCanControl_ = false;
		moveNumRight_ += 10.0f;

		for (int i = 0; i < 3; i++)
		{
			selectSpriteTransform_[i].x -= 10.0f;
		}

		if (moveNumRight_ == 1280.0f)
		{
			isCanControl_ = true;
			isSpriteMovingRight_ = false;
			moveNumRight_ = 0.0f;
		}
	}
}

void SelectScene::Draw()
{
	for (int i = 0; i < 3; i++)
	{
		selectSprite_[i]->Draw();
	}
}