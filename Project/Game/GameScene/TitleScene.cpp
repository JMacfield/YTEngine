/// タイトルシーン

#include "GameScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "TestScene.h"
#include "ClearScene.h"

TitleScene::~TitleScene()
{

}

void TitleScene::Initialize()
{
	pauseSpriteHandle_ = TextureManager::LoadTexture("Resources/pause.png");
	pauseSprite_.reset(Sprite::Create(pauseSpriteHandle_, pauseSpriteTransform_));

	pauseSpriteTransform_ = { 0.0f,0.0f };

	titleSpriteHandle_ = TextureManager::LoadTexture("Resources/Title/Title.png");
	titleSprite_.reset(Sprite::Create(titleSpriteHandle_, titleSpriteTransform_));

	adSpriteTransform_ = { 24.0f,480.0f };
	//adSprite_->SetScale({ 0.5f,0.5f });

	adSpriteHandle_ = TextureManager::LoadTexture("Resources/tutorial_ad.png");
	adSprite_.reset(Sprite::Create(adSpriteHandle_, adSpriteTransform_));

	fSpriteHandle_ = TextureManager::LoadTexture("Resources/f.png");

	fSprite_.reset(Sprite::Create(fSpriteHandle_, fSpriteTransform_));

	fSpriteTransform_ = { 600.0f,360.0f };

	camera_.Initialize();
	camera_.translate_.y = 2.0f;
	camera_.translate_.z = -10.0f;

	AnimationInitialize();

	SurfaceInitialize();

	testPlayer_ = std::make_unique<Player>();
	testPlayer_->Initialize();

	testStage_ = std::make_unique<Stage>();
	testStage_->Initialize();

	//followCamera_ = std::make_unique<FollowCamera>();
	//followCamera_->SetTarget(&testPlayer_->GetWorldTransform());
	//followCamera_->Initialize();
	//followCamera_->Update();

	//testPlayer_->SetViewProjection(&followCamera_->GetViewProjection());
}

void TitleScene::Update(GameManager* gameManager)
{
	gameManager;
 
	/*ImGui::Begin("Debug");
	ImGui::DragFloat3("CameraT", &camera_.translate_.x, 1.0f);
	ImGui::DragFloat3("CameraR", &camera_.rotate_.x, 1.0f);
	ImGui::End();*/

	fSprite_->SetPosition(fSpriteTransform_);

	adSprite_->SetPosition(adSpriteTransform_);
	adSprite_->SetScale({ 0.5f,0.5f });

	camera_.Update();

	/*ImGui::Begin("Frame");
	float frame = ImGui::GetIO().Framerate;
	ImGui::DragFloat("Frame", &frame);
	ImGui::DragFloat3("Camera", &camera_.translate_.y, 0.01f);
	ImGui::End();*/

	/*ImGui::Begin("Debug");
	ImGui::DragFloat2("BTS", &blackTransform_.x, 1.0f);
	ImGui::DragFloat2("Scale", &blackSize_.x, 1.0f);
	ImGui::End();*/
	black_->SetPosition(blackTransform_);

	/*XINPUT_STATE joyState{};

	if (Input::GetInstance()->GetJoystickState(joyState))
	{
		if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			gameManager->ChangeScene(new SelectScene);
		}
	}*/



	if (Input::GetInstance()->IsTriggerKey(DIK_SPACE) && isScreenDown_ == false && isTestStart_ == false)
	{
		isScreenDown_ = true;
	}

	if (isScreenDown_ == true)
	{
		whiteTransform_.y += 5.0f;
	}

	if (whiteTransform_.y == 0.0f)
	{
		isScreenDown_ = false;
		AnimationInitialize();
		isTitleStart_ = false;
		isTitleReset_ = true;

		TestInitialize();

		if (isTestStart_ == false)
		{
			isTestStart_ = true;
		}
		else if (isTestStart_ == true)
		{
			isTestStart_ = false;
			camera_.translate_.y = 2.0f;
			camera_.translate_.z = -10.0f;
			camera_.rotate_.x = 0.0f;
		}

		//gameManager->ChangeScene(new GameScene);
	}

	if (isTitleReset_ == true)
	{
		whiteTransform_.y -= 5.0f;
	}

	if (whiteTransform_.y == -720.0f && isTitleReset_ == true)
	{
		
	/*	isTitleReset_ = false;
		isTitleStart_ = true;*/
	}

	if (isZoom_ == true)
	{
		black_->SetScale(blackSize_);
		blackSize_.x += 2.0f;
		blackSize_.y += 1.5f;
	
	}

	if (isTitleStart_ == true)
	{
		//if (isPauseMenuShown_ == false) {
			AnimationUpdate();
		//}
	}

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

	if (isTestStart_ == true)
	{
		if (Input::GetInstance()->IsTriggerKey(DIK_ESCAPE) && isPauseMenuShown_ == false) {
			isPauseMenuShown_ = true;
		}
		else if (Input::GetInstance()->IsTriggerKey(DIK_ESCAPE) && isPauseMenuShown_ == true) {
			isPauseMenuShown_ = false;
		}

		if (isPauseMenuShown_ == true && Input::GetInstance()->IsTriggerKey(DIK_SPACE)) {
			AnimationInitialize();
			//TestInitialize();
				isTestStart_ = false;
				//isTitleReset_ = true;
				isScreenDown_ = false;
				isTitleStart_ = true;

				camera_.translate_.y = 2.0f;
				camera_.translate_.z = -10.0f;
				camera_.rotate_.x = 0.0f;

				Initialize();
		}

		if (isPauseMenuShown_ == false) {
			testPlayer_->Update();
		}

		testStage_->Update();

		if (wallTimer_ < 120)
		{
			if (testPlayer_->GetWorldTransform().translate_.x > 1.46f)
			{
				testPlayer_->SetPosition({ 1.46f,-0.2f,0.0f });
			}
		}

		if (wallTimer_ > 130)
		{
			wallTimerStart_ = false;
		}

		if (wallTimerStart_ == true)
		{
			wallTimer_ += 1;
		}

		if (testPlayer_->GetWorldTransform().translate_.x > -0.1f && testPlayer_->GetWorldTransform().translate_.x < 0.8f)
		{
			if (Input::GetInstance()->IsTriggerKey(DIK_F))
			{
				wallTimerStart_ = true;
				testStage_->SetMoveWallFlag(true);
			}
		}

		if (camera_.translate_.x < -2.5f) {
			isCanCameraMove_ = false;
		}
		if (camera_.translate_.x > -2.5f) {
			isCanCameraMove_ = true;
		}

		if (camera_.translate_.x > 3.0f) {
			isCanCameraMove_ = false;
		}

		/*if (isCanCameraMove_ == true) {
			if (Input::GetInstance()->IsPushKey(DIK_A)) {
				camera_.translate_.x -= 0.05f;
			}
		}
		if (Input::GetInstance()->IsPushKey(DIK_D)) {
			camera_.translate_.x += 0.05f;
		}*/

		//followCamera_->Update();
		//camera_.viewMatrix_ = followCamera_->GetViewProjection().viewMatrix_;
		//camera_.projectionMatrix_ = followCamera_->GetViewProjection().projectionMatrix_;
		//camera_.Transfer();

		/*if (Input::GetInstance()->IsPushKey(DIK_A) || Input::GetInstance()->IsPushKey(DIK_D))
		{
			if (cameraShakeVelo_ == false)
			{
				camera_.translate_.y += 0.007f;
			}
			else
			{
				camera_.translate_.y -= 0.007f;
			}

			if (camera_.translate_.y > 4.1f)
			{
				cameraShakeVelo_ = true;
			}
			if (camera_.translate_.y < 3.9f)
			{
				cameraShakeVelo_ = false;
			}
		}
		else
		{
			camera_.translate_.y = 4.0f;
		}*/

		if (testPlayer_->GetWorldTransform().translate_.x > 4.8f)
		{
			//isScreenDown_ = true;
			isZoom_ = true;
			isGameOver_ = true;

			testPlayer_->SetPosition({ -2.2f,-0.2f,0.0f });
			testPlayer_->SetRotate({ 0.0f,1.4f,0.0f });
		}
	}

	if (blackSize_.x > 240.0f)
	{
		isZoom_ = false;
		isGameOverDraw_ = true;
	}

	if (isGameOverDraw_ == true)
	{
		color_ += 0.01f;
		gameOverSprite_->SetColor({ 1.0f,1.0f,1.0f,color_ });
	}

	if (isGameOverDraw_ == true && Input::GetInstance()->IsTriggerKey(DIK_SPACE))
	{
		AnimationInitialize();
		//TestInitialize();
		isTestStart_ = false;
		//isTitleReset_ = true;
		isScreenDown_ = false;
		isTitleStart_ = true;

		camera_.translate_.y = 2.0f;
		camera_.translate_.z = -10.0f;
		camera_.rotate_.x = 0.0f;

		Initialize();
	}
}

void TitleScene::Draw()
{
	//titleSprite_->Draw();

	if (isTestStart_ == false) 
	{
		AnimationDraw();

		SurfaceDraw();
	}

	if (isTestStart_ == true)
	{
		testPlayer_->Draw(camera_);

		testStage_->Draw(camera_);

		adSprite_->Draw();

		if (testPlayer_->GetWorldTransform().translate_.x > -0.1f && testPlayer_->GetWorldTransform().translate_.x < 0.8f) 
		{
			fSprite_->Draw();
		}

		if (isPauseMenuShown_ == true) {
			pauseSprite_->Draw();
		}
	}

	white_->Draw();

	titleSign_->Draw(titleSignTransform_, camera_);

	if (isGameOver_ == true)
	{
		black_->Draw();
	}

	if (isGameOverDraw_ == true)
	{
		gameOverSprite_->Draw();
	}
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

	repeatCount_ = 0;
	isRepeat_ = true;
	repeatTimer_ = 0;

	playerIconTransform_[0].x = -440.0f;
	playerIconTransform_[1].x = 1520.0f;
	playerIconTransform_[2].x = -740.0f;
	playerIconTransform_[3].x = 1820.0f;

	titleSignHandle_ = ModelManager::GetInstance()->LoadModelFile("Resources/TitleSign", "TitleSign.gltf");

	titleSign_.reset(Model::Create(titleSignHandle_));

	titleSignTransform_.Initialize();
	titleSignTransform_.translate_ = { 0.0f,0.0f,0.0f };
	titleSignTransform_.scale_ = { 10.0f,10.0f,10.0f };

	blackHandle_ = TextureManager::GetInstance()->LoadTexture("Resources/black.png");
	blackTransform_ = { 1055.0f,628.0f };
	blackSize_ = { 1.0f,1.0f };
	black_.reset(Sprite::Create(blackHandle_, blackTransform_));
	black_->SetAnchorPoint({ 0.5f,0.5f });

	isGameOver_ = false;

	isZoom_ = false;
	isGameOverDraw_ = false;

	gameOverHandle_ = TextureManager::GetInstance()->LoadTexture("Resources/gameover.png");
	gameOverTransform_ = { 0.0f,0.0f };
	gameOverSprite_.reset(Sprite::Create(gameOverHandle_, gameOverTransform_));

	color_ = 0.0f;

	gameOverSprite_->SetColor({ 1.0f,1.0f,1.0f,color_ });
}

void TitleScene::AnimationUpdate()
{
	/*ImGui::Begin("Debug");
	ImGui::DragFloat3("SignTransform", &titleSignTransform_.translate_.x, 0.01f);
	ImGui::DragFloat3("Camera", &camera_.translate_.x, 0.01f);
	ImGui::End();*/

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

	//titleSign_->Draw(titleSignTransform_, camera_);
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

	playerIcon_[0].reset(Sprite::Create(playerIconHandle_[0], playerIconTransform_[0]));
	playerIcon_[1].reset(Sprite::Create(playerIconHandle_[1], playerIconTransform_[1]));
	playerIcon_[2].reset(Sprite::Create(playerIconHandle_[2], playerIconTransform_[2]));
	playerIcon_[3].reset(Sprite::Create(playerIconHandle_[3], playerIconTransform_[3]));

	titleIconHandle_ = TextureManager::LoadTexture("Resources/Title/UnravelIcon.png");

	titleIcon_.reset(Sprite::Create(titleIconHandle_, titleIconTransform_));

	titleIconTransform_.x = 270.0f;

	titleBGMHandle_ = Audio::GetInstance()->LoadMP3(L"Resources/Title/title.mp3");

	Audio::GetInstance()->ChangeVolume(titleBGMHandle_, 0.05f);

	whiteHandle_ = TextureManager::LoadTexture("Resources/white.png");
	whiteTransform_ = { 0.0f,-720.0f };

	white_.reset(Sprite::Create(whiteHandle_, whiteTransform_));

	isScreenDown_ = false;
	isTitleStart_ = true;
	isTitleReset_ = false;
}

void TitleScene::SurfaceUpdate()
{
	surfaceGroundTransform_.Update();
	surfaceBackTransform_.Update();

	playerIcon_[0]->SetPosition({ playerIconTransform_[0].x, 270 });
	playerIcon_[1]->SetPosition({ playerIconTransform_[1].x, 270 });
	playerIcon_[2]->SetPosition({ playerIconTransform_[2].x, 270 });
	playerIcon_[3]->SetPosition({ playerIconTransform_[3].x, 270 });

	white_->SetPosition({ whiteTransform_.x,whiteTransform_.y });

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

void TitleScene::TestInitialize()
{
	camera_.translate_.y = 4.0f;
	camera_.translate_.z = -14.0f;
	camera_.rotate_.x = 0.1f;
}

void TitleScene::TestUpdate()
{
	
}

void TitleScene::TestDraw()
{

}