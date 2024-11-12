#include "GameObject/Player/Player.h"
#include "GameObject/Stage/Stage.h"

void Player::Initialize()
{
	playerModelHandle_ = ModelManager::GetInstance()->LoadModelFile("Resources/AssignmentModel/human", "walk.gltf");
	
	playerIdleAnimationHandle_ = AnimationManager::GetInstance()->LoadFile("Resources/Player/PlayerIdle", "PlayerIdle.gltf");
	playerWalkAnimationHandle_ = AnimationManager::GetInstance()->LoadFile("Resources/Player/PlayerWalk", "PlayerWalk.gltf");
	playerSprintAnimationHandle_ = AnimationManager::GetInstance()->LoadFile("Resources/Player/PlayerSprint", "PlayerSprint.gltf");
	playerPunchAnimationHandle_ = AnimationManager::GetInstance()->LoadFile("Resources/Player/PlayerPunch", "PlayerPunch.gltf");
	playerJumpAnimationHandle_ = AnimationManager::GetInstance()->LoadFile("Resources/Player/PlayerJump", "PlayerJump.gltf");

	playerGrabAnimationHandle_ = AnimationManager::GetInstance()->LoadFile("Resources/Player/PlayerGrab", "PlayerGrab.gltf");
	playerGrabStartAnimationHandle_ = AnimationManager::GetInstance()->LoadFile("Resources/Player/PlayerGrabStart", "PlayerGrabStart.gltf");
	playerGrabStopAnimationHandle_ = AnimationManager::GetInstance()->LoadFile("Resources/Player/PlayerGrabStop", "PlayerGrabStop.gltf");

	player_.reset(AnimationModel::Create(playerModelHandle_));
	
	playerWorldTransform_.Initialize();
	playerWorldTransform_.translate_.x = -2.2f;
	playerWorldTransform_.translate_.y = -0.2f;
	playerWorldTransform_.rotate_.y = 1.4f;
	
	playerAnimationTime_ = 0;
	
	playerSkeleton.Create(ModelManager::GetInstance()->GetModelData(playerModelHandle_).rootNode);

	playerSkinCluster_.Create(playerSkeleton, ModelManager::GetInstance()->GetModelData(playerModelHandle_));

	controlSpriteTransform_ = { 680.0f,480.0f };
	controlSpriteHandle_ = TextureManager::LoadTexture("Resources/Title/Control.png");
	controlSprite_.reset(Sprite::Create(controlSpriteHandle_, controlSpriteTransform_));
}

void Player::Update()
{
	/*ImGui::Begin("Player");
	ImGui::DragFloat3("Rotate", &playerWorldTransform_.rotate_.x, 0.01f);
	ImGui::DragFloat3("Translate", &playerWorldTransform_.translate_.x, 0.01f);
	ImGui::End();

	ImGui::Begin("Controller");
	ImGui::DragFloat("Left X", &Input::GetInstance()->GetJoyLStickPos().x);
	ImGui::End();

	ImGui::Begin("AnimationTimer");
	ImGui::DragFloat("Timer", &playerAnimationTime_, 0.01f);
	ImGui::End();*/
	
	Control();

	AnimationUpdate();

	BehaviorUpdate();

	if (Input::GetInstance()->IsPushKey(DIK_1)) { behaviorRequest_ = Behavior::kIdle; }
	if (Input::GetInstance()->IsPushKey(DIK_2)) { behaviorRequest_ = Behavior::kWalk; }
	if (Input::GetInstance()->IsPushKey(DIK_3)) { behaviorRequest_ = Behavior::kSprint; }
	if (Input::GetInstance()->IsPushKey(DIK_4)) { behaviorRequest_ = Behavior::kGrab; }
	if (Input::GetInstance()->IsPushKey(DIK_5)) { behaviorRequest_ = Behavior::kPunch; }
	if (Input::GetInstance()->IsPushKey(DIK_6)) { behaviorRequest_ = Behavior::kJump; }
}

void Player::Draw(Camera& camera)
{
	player_->Draw(playerWorldTransform_, camera, playerSkinCluster_);
	//controlSprite_->Draw();
}

void Player::Control()
{
	//XINPUT_STATE joyState;

	Vector3 move{};

	// 移動処理
	/*if (Input::GetInstance()->GetJoystickState(joyState))
	{
		const float kCharacterSpeed = 0.03f;

		if ((float)joyState.Gamepad.sThumbLX / SHRT_MAX > 0.5f || Input::GetInstance()->IsTriggerKey(DIK_D))
		{
			playerWorldTransform_.rotate_.y = 1.4f;
			move = { (float)joyState.Gamepad.sThumbLX / SHRT_MAX,0.0f,0.0f };
			behaviorRequest_ = Behavior::kWalk;
		}
		else if ((float)joyState.Gamepad.sThumbLX / SHRT_MAX < -0.5f || Input::GetInstance()->IsTriggerKey(DIK_A))
		{
			playerWorldTransform_.rotate_.y = -1.4f;
			move = { (float)joyState.Gamepad.sThumbLX / SHRT_MAX ,0.0f,0.0f };
			behaviorRequest_ = Behavior::kWalk;
		}
		else
		{
			behaviorRequest_ = Behavior::kIdle;
		}

		move = Multiply(kCharacterSpeed, Normalize(move));

		if (playerWorldTransform_.translate_.x > 5.0f)
		{
			playerWorldTransform_.translate_.x = 5.0;
		}
		else if (playerWorldTransform_.translate_.x < -5.0f)
		{
			playerWorldTransform_.translate_.x = -5.0f;
		}

		playerWorldTransform_.translate_ = Add(move, playerWorldTransform_.translate_);
	}*/

	if (Input::GetInstance()->IsPushKey(DIK_D))
	{
		playerWorldTransform_.rotate_.y = 1.4f;
		move = { 0.4f / SHRT_MAX,0.0f,0.0f };
		behaviorRequest_ = Behavior::kWalk;
	}
	else if (Input::GetInstance()->IsPushKey(DIK_A))
	{
		playerWorldTransform_.rotate_.y = -1.4f;
		move = { -0.4f / SHRT_MAX ,0.0f,0.0f };
		behaviorRequest_ = Behavior::kWalk;
	}
	else
	{
		behaviorRequest_ = Behavior::kIdle;
	}

	move = Multiply(kCharacterSpeed, Normalize(move));

	if (playerWorldTransform_.translate_.x > 5.0f)
	{
		playerWorldTransform_.translate_.x = 5.0;
	}
	else if (playerWorldTransform_.translate_.x < -5.0f)
	{
		playerWorldTransform_.translate_.x = -5.0f;
	}

	playerWorldTransform_.translate_ = Add(move, playerWorldTransform_.translate_);


	// ジャンプ
	/*if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
	{
		BehaviorJumpInitialize();
		behaviorRequest_ = Behavior::kJump;
	}*/

	// パンチ
	//if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
	//{
	//	behaviorRequest_ = Behavior::kPunch;
	//}

	//// 掴む
	//if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
	//{
	//	playerWorldTransform_.rotate_.y = -1.4f;
	//	behaviorRequest_ = Behavior::kGrab;
	//}
}

void Player::AnimationUpdate()
{
	playerAnimationTime_ += 1.0f / 60.0f;

	playerWorldTransform_.Update();

	playerSkeleton.Update();

	playerSkinCluster_.Update(playerSkeleton);
}

void Player::SetCollision()
{
	playerCollision_.center = playerWorldTransform_.GetWorldPosition();
	GetOrientations(MakeRotateXYZMatrix(playerWorldTransform_.rotate_.x, playerWorldTransform_.rotate_.y, playerWorldTransform_.rotate_.z), playerCollision_.orientation);
	playerCollision_.size = { 2.0f,2.0f,2.0f };
}

void Player::BehaviorIdleInitialize()
{

}

void Player::BehaviorIdleUpdate()
{
	AnimationManager::GetInstance()->ApplyAnimation(playerSkeleton, playerIdleAnimationHandle_, playerModelHandle_, playerAnimationTime_);
}

void Player::BehaviorWalkInitialize()
{

}

void Player::BehaviorWalkUpdate()
{
	AnimationManager::GetInstance()->ApplyAnimation(playerSkeleton, playerWalkAnimationHandle_, playerModelHandle_, playerAnimationTime_);
}

void Player::BehaviorSprintInitialize()
{

}

void Player::BehaviorSprintUpdate()
{
	/*AnimationManager::GetInstance()->ApplyAnimation(playerSkeleton, playerSprintAnimationHandle_, playerModelHandle_, playerAnimationTime_);*/
}

void Player::BehaviorGrabInitialize()
{

}

void Player::BehaviorGrabUpdate()
{
	AnimationManager::GetInstance()->ApplyAnimation(playerSkeleton, playerGrabAnimationHandle_, playerModelHandle_, playerAnimationTime_);

	/*if (playerAnimationTime_ < 2.42 && num == 0) 
	{
		AnimationManager::GetInstance()->ApplyAnimation(playerSkeleton, playerGrabAnimationHandle_, playerModelHandle_, playerAnimationTime_);
	}
	if (playerAnimationTime_ < 1.9 && num == 1)
	{
		AnimationManager::GetInstance()->ApplyAnimation(playerSkeleton, playerGrabStopAnimationHandle_, playerModelHandle_, playerAnimationTime_);
	}*/
	/*if (playerAnimationTime_ < 1.9 && num == 2)
	{
		AnimationManager::GetInstance()->ApplyAnimation(playerSkeleton, playerGrabStopAnimationHandle_, playerModelHandle_, playerAnimationTime_);
	}*/

	/*if (playerAnimationTime_ > 2.5 && num == 0)
	{
		playerAnimationTime_ = 0.0;
		num = 1;
	}*/
	//if (playerAnimationTime_ > 2.0 && num == 1)
	//{
	//	playerAnimationTime_ = 0.0;
	//	num = 0;
	//	//playerWorldTransform_.translate_.x = 2.1f;
	//}
	/*if (playerAnimationTime_ > 2.0 && num == 2)
	{
		behaviorRequest_ = Behavior::kIdle;
	}*/
}

void Player::BehaviorPunchInitialize()
{

}

void Player::BehaviorPunchUpdate()
{
	/*AnimationManager::GetInstance()->ApplyAnimation(playerSkeleton, playerPunchAnimationHandle_, playerModelHandle_, playerAnimationTime_);*/
}

void Player::BehaviorJumpInitialize()
{
	playerAnimationTime_ = 0;
}

void Player::BehaviorJumpUpdate()
{
	/*AnimationManager::GetInstance()->ApplyAnimation(playerSkeleton, playerJumpAnimationHandle_, playerModelHandle_, playerAnimationTime_);*/
}

void Player::BehaviorUpdate()
{
	if (behaviorRequest_)
	{
		behavior_ = behaviorRequest_.value();

		switch (behavior_)
		{
		case Behavior::kIdle:
		default:
			BehaviorIdleInitialize();
			break;

		case Behavior::kWalk:
			BehaviorWalkInitialize();
			break;

		case Behavior::kSprint:
			BehaviorSprintInitialize();
			break;

		case Behavior::kGrab:
			BehaviorGrabInitialize();
			break;

		case Behavior::kPunch:
			BehaviorPunchInitialize();
			break;

		case Behavior::kJump:
			BehaviorJumpInitialize();
			break;
		}

		behaviorRequest_ = std::nullopt;
	}

	switch (behavior_)
	{
	case Behavior::kIdle:
	default:
		BehaviorIdleUpdate();
		break;

	case Behavior::kWalk:
		BehaviorWalkUpdate();
		break;

	case Behavior::kSprint:
		BehaviorSprintUpdate();
		break;

	case Behavior::kGrab:
		BehaviorGrabUpdate();
		break;

	case Behavior::kPunch:
		BehaviorPunchUpdate();
		break;

	case Behavior::kJump:
		BehaviorJumpUpdate();
		break;
	}
}