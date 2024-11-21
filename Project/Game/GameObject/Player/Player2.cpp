#include "GameObject/Player/Player2.h"
#include "GameObject/Stage/Stage.h"

using namespace YTEngine;

void Player2::Initialize()
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
	playerWorldTransform_.translate_.x = -1.7f;
	playerWorldTransform_.translate_.y = -0.2f;
	playerWorldTransform_.rotate_.y = 1.4f;

	playerAnimationTime_ = 20;

	playerSkeleton.Create(ModelManager::GetInstance()->GetModelData(playerModelHandle_).rootNode);

	playerSkinCluster_.Create(playerSkeleton, ModelManager::GetInstance()->GetModelData(playerModelHandle_));

	controlSpriteTransform_ = { 680.0f,480.0f };
	controlSpriteHandle_ = TextureManager::LoadTexture("Resources/Title/Control.png");
	controlSprite_.reset(Sprite::Create(controlSpriteHandle_, controlSpriteTransform_));
}

void Player2::Update()
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

	/*if (Input::GetInstance()->IsPushKey(DIK_1)) { behaviorRequest_ = Behavior::kIdle; }
	if (Input::GetInstance()->IsPushKey(DIK_2)) { behaviorRequest_ = Behavior::kWalk; }
	if (Input::GetInstance()->IsPushKey(DIK_3)) { behaviorRequest_ = Behavior::kSprint; }
	if (Input::GetInstance()->IsPushKey(DIK_4)) { behaviorRequest_ = Behavior::kGrab; }
	if (Input::GetInstance()->IsPushKey(DIK_5)) { behaviorRequest_ = Behavior::kPunch; }
	if (Input::GetInstance()->IsPushKey(DIK_6)) { behaviorRequest_ = Behavior::kJump; }*/
}

void Player2::Draw(Camera& camera)
{
	player_->Draw(playerWorldTransform_, camera, playerSkinCluster_);
	//controlSprite_->Draw();
}

void Player2::Control()
{
	//XINPUT_STATE joyState;

	Vector3 move{};

	if (Input::GetInstance()->IsPushKey(DIK_RIGHTARROW))
	{
		playerWorldTransform_.rotate_.y = 1.4f;
		move = { 0.4f / SHRT_MAX,0.0f,0.0f };
		behaviorRequest_ = Behavior2::kWalk;
	}
	else if (Input::GetInstance()->IsPushKey(DIK_LEFTARROW))
	{
		playerWorldTransform_.rotate_.y = -1.4f;
		move = { -0.4f / SHRT_MAX ,0.0f,0.0f };
		behaviorRequest_ = Behavior2::kWalk;
	}
	else
	{
		behaviorRequest_ = Behavior2::kIdle;
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

	// 移動処理
	/*if (Input::GetInstance()->GetJoystickState(joyState))
	{
		const float kCharacterSpeed = 0.03f;

		if ((float)joyState.Gamepad.sThumbLX / SHRT_MAX > 0.5f)
		{
			playerWorldTransform_.rotate_.y = 1.4f;
			move = { (float)joyState.Gamepad.sThumbLX / SHRT_MAX,0.0f,0.0f };
			behaviorRequest_ = Behavior::kWalk;
		}
		else if ((float)joyState.Gamepad.sThumbLX / SHRT_MAX < -0.5f)
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
	//	//playerWorldTransform_.rotate_.y = -1.4f;
	//	behaviorRequest_ = Behavior::kGrab;
	//}
}

void Player2::AnimationUpdate()
{
	playerAnimationTime_ += 1.0f / 60.0f;

	playerWorldTransform_.Update();

	playerSkeleton.Update();

	playerSkinCluster_.Update(playerSkeleton);
}

void Player2::SetCollision()
{
	playerCollision_.center = playerWorldTransform_.GetWorldPosition();
	GetOrientations(MakeRotateXYZMatrix(playerWorldTransform_.rotate_.x, playerWorldTransform_.rotate_.y, playerWorldTransform_.rotate_.z), playerCollision_.orientation);
	playerCollision_.size = { 2.0f,2.0f,2.0f };
}

void Player2::BehaviorIdleInitialize()
{

}

void Player2::BehaviorIdleUpdate()
{
	AnimationManager::GetInstance()->ApplyAnimation(playerSkeleton, playerIdleAnimationHandle_, playerModelHandle_, playerAnimationTime_);
}

void Player2::BehaviorWalkInitialize()
{

}

void Player2::BehaviorWalkUpdate()
{
	AnimationManager::GetInstance()->ApplyAnimation(playerSkeleton, playerWalkAnimationHandle_, playerModelHandle_, playerAnimationTime_);
}

void Player2::BehaviorSprintInitialize()
{

}

void Player2::BehaviorSprintUpdate()
{
	/*AnimationManager::GetInstance()->ApplyAnimation(playerSkeleton, playerSprintAnimationHandle_, playerModelHandle_, playerAnimationTime_);*/
}

void Player2::BehaviorGrabInitialize()
{

}

void Player2::BehaviorGrabUpdate()
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

void Player2::BehaviorPunchInitialize()
{

}

void Player2::BehaviorPunchUpdate()
{
	/*AnimationManager::GetInstance()->ApplyAnimation(playerSkeleton, playerPunchAnimationHandle_, playerModelHandle_, playerAnimationTime_);*/
}

void Player2::BehaviorJumpInitialize()
{
	playerAnimationTime_ = 0;
}

void Player2::BehaviorJumpUpdate()
{
	/*AnimationManager::GetInstance()->ApplyAnimation(playerSkeleton, playerJumpAnimationHandle_, playerModelHandle_, playerAnimationTime_);*/
}

void Player2::BehaviorUpdate()
{
	if (behaviorRequest_)
	{
		behavior_ = behaviorRequest_.value();

		switch (behavior_)
		{
		case Behavior2::kIdle:
		default:
			BehaviorIdleInitialize();
			break;

		case Behavior2::kWalk:
			BehaviorWalkInitialize();
			break;

		case Behavior2::kSprint:
			BehaviorSprintInitialize();
			break;

		case Behavior2::kGrab:
			BehaviorGrabInitialize();
			break;

		case Behavior2::kPunch:
			BehaviorPunchInitialize();
			break;

		case Behavior2::kJump:
			BehaviorJumpInitialize();
			break;
		}

		behaviorRequest_ = std::nullopt;
	}

	switch (behavior_)
	{
	case Behavior2::kIdle:
	default:
		BehaviorIdleUpdate();
		break;

	case Behavior2::kWalk:
		BehaviorWalkUpdate();
		break;

	case Behavior2::kSprint:
		BehaviorSprintUpdate();
		break;

	case Behavior2::kGrab:
		BehaviorGrabUpdate();
		break;

	case Behavior2::kPunch:
		BehaviorPunchUpdate();
		break;

	case Behavior2::kJump:
		BehaviorJumpUpdate();
		break;
	}
}