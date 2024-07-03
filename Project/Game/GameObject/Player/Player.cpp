#include "GameObject/Player/Player.h"

void Player::Initialize()
{
	playerModelHandle_ = ModelManager::GetInstance()->LoadModelFile("Resources/AssignmentModel/human", "walk.gltf");
	
	playerIdleAnimationHandle_ = AnimationManager::GetInstance()->LoadFile("Resources/Player/PlayerIdle", "PlayerIdle.gltf");
	playerWalkAnimationHandle_ = AnimationManager::GetInstance()->LoadFile("Resources/Player/PlayerWalk", "PlayerWalk.gltf");
	playerSprintAnimationHandle_ = AnimationManager::GetInstance()->LoadFile("Resources/Player/PlayerSprint", "PlayerSprint.gltf");
	playerGrabAnimationHandle_ = AnimationManager::GetInstance()->LoadFile("Resources/Player/PlayerGrab", "PlayerGrab.gltf");
	playerPunchAnimationHandle_ = AnimationManager::GetInstance()->LoadFile("Resources/Player/PlayerPunch", "PlayerPunch.gltf");
	playerJumpAnimationHandle_ = AnimationManager::GetInstance()->LoadFile("Resources/Player/PlayerJump", "PlayerJump.gltf");

	player_.reset(AnimationModel::Create(playerModelHandle_));
	
	playerWorldTransform_.Initialize();
	playerWorldTransform_.translate_.x = 0.0f;
	playerWorldTransform_.translate_.y = -0.3f;
	playerWorldTransform_.rotate_.y = 1.4f;
	
	playerAnimationTime_ = 0;

	playerSkeleton.Create(ModelManager::GetInstance()->GetModelData(playerModelHandle_).rootNode);

	playerSkinCluster_.Create(playerSkeleton, ModelManager::GetInstance()->GetModelData(playerModelHandle_));
}

void Player::Update()
{
	ImGui::Begin("Player");
	ImGui::DragFloat3("Rotate", &playerWorldTransform_.rotate_.x, 0.01f);
	ImGui::DragFloat3("Translate", &playerWorldTransform_.translate_.x, 0.01f);
	ImGui::End();

	ImGui::Begin("Controller");
	ImGui::DragFloat("Left X", &Input::GetInstance()->GetJoyLStickPos().x);
	ImGui::End();
	
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
}

void Player::Control()
{
	XINPUT_STATE joyState;

	Vector3 move{};

	playerWorldTransform_.translate_.x = 0.0f;

	// 移動処理
	if (Input::GetInstance()->GetJoystickState(joyState))
	{
		const float kCharacterSpeed = 0.03f;

		if ((float)joyState.Gamepad.sThumbLX / SHRT_MAX > 0.5f)
		{
			playerWorldTransform_.rotate_.y = 1.4f;
			move = { (float)joyState.Gamepad.sThumbLX / SHRT_MAX,0.0f,0.0f };
			behaviorRequest_ = Behavior::kSprint;
		}
		else if ((float)joyState.Gamepad.sThumbLX / SHRT_MAX < -0.5f)
		{
			playerWorldTransform_.rotate_.y = -1.4f;
			move = { (float)joyState.Gamepad.sThumbLX / SHRT_MAX ,0.0f,0.0f };
			behaviorRequest_ = Behavior::kSprint;
		}

		move = Multiply(kCharacterSpeed, Normalize(move));

		if (playerWorldTransform_.translate_.x > 4.0f)
		{
			playerWorldTransform_.translate_.x = 3.9f;
		}
		else if (playerWorldTransform_.translate_.x < -4.0f)
		{
			playerWorldTransform_.translate_.x = -3.9f;
		}

		playerWorldTransform_.translate_ = Add(move, playerWorldTransform_.translate_);
	}

	// ジャンプ
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
	{
		BehaviorJumpInitialize();
		behaviorRequest_ = Behavior::kJump;
	}

	// パンチ
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
	{
		behaviorRequest_ = Behavior::kPunch;
	}

	// 掴む
	if (joyState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
	{
		behaviorRequest_ = Behavior::kGrab;
	}
}

void Player::AnimationUpdate()
{
	playerAnimationTime_ += 1.0f / 60.0f;

	playerWorldTransform_.Update();

	playerSkeleton.Update();

	playerSkinCluster_.Update(playerSkeleton);
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
	AnimationManager::GetInstance()->ApplyAnimation(playerSkeleton, playerSprintAnimationHandle_, playerModelHandle_, playerAnimationTime_);
}

void Player::BehaviorGrabInitialize()
{

}

void Player::BehaviorGrabUpdate()
{
	AnimationManager::GetInstance()->ApplyAnimation(playerSkeleton, playerGrabAnimationHandle_, playerModelHandle_, playerAnimationTime_);
}

void Player::BehaviorPunchInitialize()
{

}

void Player::BehaviorPunchUpdate()
{
	AnimationManager::GetInstance()->ApplyAnimation(playerSkeleton, playerPunchAnimationHandle_, playerModelHandle_, playerAnimationTime_);
}

void Player::BehaviorJumpInitialize()
{
	playerAnimationTime_ = 22.5;
	//playerAnimationTime_ = 60;
}

void Player::BehaviorJumpUpdate()
{
	AnimationManager::GetInstance()->ApplyAnimation(playerSkeleton, playerJumpAnimationHandle_, playerModelHandle_, playerAnimationTime_);
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