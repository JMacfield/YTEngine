#include "GameScene.h"
#include "TitleScene.h"
#include "SelectScene.h"

void TitleScene::Initialize()
{
	titleSpriteHandle_ = TextureManager::LoadTexture("Resources/Title/Title.png");
	titleSprite_.reset(Sprite::Create(titleSpriteHandle_, titleSpriteTransform_));

	camera_.Initialize();
	camera_.translate_.y = 2.0f;
	camera_.translate_.z = -10.0f;

	AnimationInitialize();

	SurfaceInitialize();
}

void TitleScene::Update(GameManager* gameManager)
{
	gameManager;

	//XINPUT_STATE joyState{};

	/*if (Input::GetInstance()->GetJoystickState(joyState))
	{
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			gameManager->ChangeScene(new SelectScene);
		}
	}*/

	camera_.Update();

	AnimationUpdate();

	SurfaceUpdate();

	/*ImGui::Begin("Debug");
	ImGui::DragFloat3("Camera Translate", &camera_.translate_.x, 0.01f);
	ImGui::DragFloat3("Ground Translate", &surfaceGroundTransform_.translate_.x, 0.01f);
	ImGui::Text("");
	ImGui::DragFloat3("Back Translate", &surfaceBackTransform_.translate_.x, 0.01f);
	ImGui::DragFloat3("Back Rotate", &surfaceBackTransform_.rotate_.x, 0.01f);
	ImGui::DragFloat3("Back Scale", &surfaceBackTransform_.scale_.x, 0.01f);
	ImGui::Text("");
	ImGui::DragFloat3("Player", &playerTransform_[0].translate_.x, 0.01f);
	ImGui::DragFloat2("1 P", &titleIconTransform_.x, 0.01f);
	ImGui::End();*/
}

void TitleScene::Draw()
{
	//titleSprite_->Draw();

	AnimationDraw();

	SurfaceDraw();
}

void TitleScene::AnimationInitialize()
{
	playerGrabWalkingAnimation_ = AnimationManager::LoadFile("Resources/Player/TitleSprint", "TitleSprint.gltf");
	playerModelHandle_ = ModelManager::GetInstance()->LoadModelFile("Resources/AssignmentModel/human", "walk.gltf");

	for (int i = 0; i < 4; i++)
	{
		playerTransform_[i].Initialize();

		player_[i].reset(AnimationModel::Create(playerGrabWalkingAnimation_));

		playerSkeleton_[i].Create(ModelManager::GetInstance()->GetModelData(playerModelHandle_).rootNode);

		playerSkinCluster_[i].Create(playerSkeleton_[i], ModelManager::GetInstance()->GetModelData(playerModelHandle_));

		playerTransform_[i].rotate_.y = 1.4f;
	}

	playerAnimationTime_[0] = 0;

	playerTransform_[0].translate_ = { -6.0f,0.0f,0.0f };
	playerTransform_[1].translate_ = { 6.0f,0.0f,0.0f };
	playerTransform_[2].translate_ = { -6.0f,0.0f,0.0f };
	playerTransform_[3].translate_ = { 6.0f,0.0f,0.0f };
}

void TitleScene::AnimationUpdate()
{
	playerAnimationTime_[0] += 1.0f / 60.0f;

	for (int i = 0; i < 4; i++)
	{
		playerTransform_[i].Update();

		playerSkeleton_[i].Update();

		playerSkinCluster_[i].Update(playerSkeleton_[i]);

		AnimationManager::GetInstance()->ApplyAnimation(playerSkeleton_[i], playerGrabWalkingAnimation_, playerModelHandle_, playerAnimationTime_[i]);
	}

	if (repeatCount_ == 0)
	{
		playerTransform_[0].translate_.x += 0.04f;

		playerIconTransform_[0].x += 6.1f;

		if (playerTransform_[0].translate_.x > 9.0f)
		{
			repeatCount_ = 1;
			playerTransform_[0].translate_.x = 6.0f;
			playerTransform_[1].translate_.x = 7.0f;
			playerTransform_[0].rotate_.y = -1.4f;
			playerTransform_[1].rotate_.y = -1.4f;

			playerIconTransform_[0].x = 1360.0f;
		}
	}
		
	if (repeatCount_ == 1)
	{
		playerTransform_[0].translate_.x -= 0.04f;
		playerTransform_[1].translate_.x -= 0.04f;

		playerIconTransform_[0].x -= 6.1f;
		playerIconTransform_[1].x -= 6.1f;

		if (playerTransform_[0].translate_.x < -9.0f)
		{
			repeatCount_ = 2;
			playerTransform_[0].translate_.x = -6.0f;
			playerTransform_[1].translate_.x = -7.0f;
			playerTransform_[2].translate_.x = -8.0f;
			playerTransform_[0].rotate_.y = 1.4f;
			playerTransform_[1].rotate_.y = 1.4f;
			playerTransform_[2].rotate_.y = 1.4f;

			playerIconTransform_[0].x = -440.0f;
			playerIconTransform_[1].x = -610.0f;
		}
	}

	if (repeatCount_ == 2)
	{
		playerTransform_[0].translate_.x += 0.04f;
		playerTransform_[1].translate_.x += 0.04f;
		playerTransform_[2].translate_.x += 0.04f;

		playerIconTransform_[0].x += 6.1f;
		playerIconTransform_[1].x += 6.1f;
		playerIconTransform_[2].x += 6.1f;

		if (playerTransform_[0].translate_.x > 9.0f)
		{
			repeatCount_ = 3;
			playerTransform_[0].translate_.x = 6.0f;
			playerTransform_[1].translate_.x = 7.0f;
			playerTransform_[2].translate_.x = 8.0f;
			playerTransform_[3].translate_.x = 9.0f;
			playerTransform_[0].rotate_.y = -1.4f;
			playerTransform_[1].rotate_.y = -1.4f;
			playerTransform_[2].rotate_.y = -1.4f;
			playerTransform_[3].rotate_.y = -1.4f;

			playerIconTransform_[0].x = 1360.0f;
			playerIconTransform_[1].x = 1520.0f;
			playerIconTransform_[2].x = 1680.0f;
		}
	}

	if (repeatCount_ == 3)
	{
		playerTransform_[0].translate_.x -= 0.04f;
		playerTransform_[1].translate_.x -= 0.04f;
		playerTransform_[2].translate_.x -= 0.04f;
		playerTransform_[3].translate_.x -= 0.04f;

		playerIconTransform_[0].x -= 6.1f;
		playerIconTransform_[1].x -= 6.1f;
		playerIconTransform_[2].x -= 6.1f;
		playerIconTransform_[3].x -= 6.1f;

		if (playerTransform_[0].translate_.x < -9.0f)
		{
			repeatCount_ = 0;
			playerTransform_[0].translate_.x = -6.0f;
			playerTransform_[0].rotate_.y = 1.4f;

			playerIconTransform_[0].x = -440.0f;
			playerIconTransform_[1].x = 1520.0f;
			playerIconTransform_[2].x = -740.0f;
			playerIconTransform_[3].x = 1820.0f;
		}
	}

	if (repeatCount_ == 3 || repeatCount_ == 2 || repeatCount_ == 1)
	{
		playerAnimationTime_[1] += 1.0f / 60.0f;
	}

	if (repeatCount_ == 3 || repeatCount_ == 2)
	{
		playerAnimationTime_[2] += 1.0f / 60.0f;
	}

	if (repeatCount_ == 3)
	{
		playerAnimationTime_[3] += 1.0f / 60.0f;
	}
}

void TitleScene::AnimationDraw()
{
	for (int i = 0; i < 4; i++)
	{
		player_[i]->Draw(playerTransform_[i], camera_, playerSkinCluster_[i]);
	}
}

void TitleScene::SurfaceInitialize()
{
	// 地面 //
	surfaceGroundHandle_ = ModelManager::GetInstance()->LoadModelFile("Resources/StageObject", "TestObject.obj");
	surfaceGround_.reset(Model::Create(surfaceGroundHandle_));

	surfaceGroundTransform_.Initialize();
	surfaceGroundTransform_.translate_ = { 0.0f,-2.4f,0.0f };
	surfaceGroundTransform_.scale_ = { 8.0f,3.0f,3.0f };

	// 背景 //
	surfaceBackHandle_ = ModelManager::GetInstance()->LoadModelFile("Resources/Plane", "Plane.gltf");
	surfaceBack_.reset(Model::Create(surfaceBackHandle_));

	surfaceBackTransform_.Initialize();
	surfaceBackTransform_.translate_ = { 0.0f,0.0f,0.8f };
	surfaceBackTransform_.rotate_ = { -1.44f,0.0f,0.0f };
	surfaceBackTransform_.scale_ = { 10.260f,6.140f,7.630f };
	surfaceBack_->SetColor({ 1.0f,1.0f,0.0f,1.0f });

	playerIconHandle_[0] = TextureManager::LoadTexture("Resources/Player/PlayerIcon/1p.png");
	playerIconHandle_[1] = TextureManager::LoadTexture("Resources/Player/PlayerIcon/2p.png");
	playerIconHandle_[2] = TextureManager::LoadTexture("Resources/Player/PlayerIcon/3p.png");
	playerIconHandle_[3] = TextureManager::LoadTexture("Resources/Player/PlayerIcon/4p.png");

	playerIconTransform_[0].x = -440.0f;
	playerIconTransform_[1].x = 1520.0f;
	playerIconTransform_[2].x = -740.0f;
	playerIconTransform_[3].x = 1820.0f;

	playerIcon_[0].reset(Sprite::Create(playerIconHandle_[0], playerIconTransform_[0]));
	playerIcon_[1].reset(Sprite::Create(playerIconHandle_[1], playerIconTransform_[1]));
	playerIcon_[2].reset(Sprite::Create(playerIconHandle_[2], playerIconTransform_[2]));
	playerIcon_[3].reset(Sprite::Create(playerIconHandle_[3], playerIconTransform_[3]));

	titleIconHandle_ = TextureManager::LoadTexture("Resources/Title/UnravelIcon.png");

	titleIcon_.reset(Sprite::Create(titleIconHandle_, titleIconTransform_));

	titleIconTransform_.x = 270.0f;

	titleBGMHandle_ = Audio::GetInstance()->LoadMP3(L"Resources/Title/title.mp3");

	Audio::GetInstance()->ChangeVolume(titleBGMHandle_, 0.05f);
}

void TitleScene::SurfaceUpdate()
{
	surfaceGroundTransform_.Update();
	surfaceBackTransform_.Update();

	playerIcon_[0]->SetPosition({ playerIconTransform_[0].x, 270 });
	playerIcon_[1]->SetPosition({ playerIconTransform_[1].x, 270 });
	playerIcon_[2]->SetPosition({ playerIconTransform_[2].x, 270 });
	playerIcon_[3]->SetPosition({ playerIconTransform_[3].x, 270 });

	titleIcon_->SetPosition({ titleIconTransform_.x,titleIconTransform_.y });

	Audio::GetInstance()->PlayMP3(titleBGMHandle_, true);
}

void TitleScene::SurfaceDraw()
{
	surfaceGround_->Draw(surfaceGroundTransform_, camera_);
	surfaceBack_->Draw(surfaceBackTransform_,camera_);

	playerIcon_[0]->Draw();
	playerIcon_[1]->Draw();
	playerIcon_[2]->Draw();
	playerIcon_[3]->Draw();

	titleIcon_->Draw();
}