#include "GameObject/Player/Player.h"

void Player::Initialize()
{
	playerModelHandle_ = ModelManager::GetInstance()->LoadModelFile("Resources/AssignmentModel/human", "walk.gltf");
	
	playerIdleAnimationHandle_ = AnimationManager::GetInstance()->LoadFile("Resources/Player", "PlayerIdle.gltf");
	playerWalkAnimationHandle_ = AnimationManager::GetInstance()->LoadFile("Resources/Player", "PlayerWalk.gltf");
	playerSprintAnimationHandle_ = AnimationManager::GetInstance()->LoadFile("Resources/Player", "PlayerSprint.gltf");
	playerGrabAnimationHandle_ = AnimationManager::GetInstance()->LoadFile("Resources/Player", "PlayerGrab.gltf");
	playerPunchAnimationHandle_ = AnimationManager::GetInstance()->LoadFile("Resources/Player", "PlayerPunch.gltf");
	playerJumpAnimationHandle_ = AnimationManager::GetInstance()->LoadFile("Resources/Player", "PlayerJump.gltf");

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
	ImGui::End();
	
	AnimationUpdate();

	BehaviorUpdate();

	if (Input::GetInstance()->IsPushKey(DIK_1)) behaviorRequest_ = Behavior::kIdle;
	if (Input::GetInstance()->IsPushKey(DIK_2)) behaviorRequest_ = Behavior::kWalk;
	if (Input::GetInstance()->IsPushKey(DIK_3)) behaviorRequest_ = Behavior::kSprint;
	if (Input::GetInstance()->IsPushKey(DIK_4)) behaviorRequest_ = Behavior::kGrab;
	if (Input::GetInstance()->IsPushKey(DIK_5)) behaviorRequest_ = Behavior::kPunch;
	if (Input::GetInstance()->IsPushKey(DIK_6)) behaviorRequest_ = Behavior::kJump;
}

void Player::Draw(Camera& camera)
{
	player_->Draw(playerWorldTransform_, camera, playerSkinCluster_);
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
			BehaviorIdleInitialize();
			break;

		case Behavior::kWalk:
		default:
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
		BehaviorIdleUpdate();
		break;

	case Behavior::kWalk:
	default:
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