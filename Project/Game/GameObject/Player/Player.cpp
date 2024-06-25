#include "GameObject/Player/Player.h"

void Player::Initialize()
{
	playerModelHandle_ = ModelManager::GetInstance()->LoadModelFile("Resources/Player", "PlayerPunch.gltf");
	playerAnimationHandle_ = AnimationManager::GetInstance()->LoadFile("Resources/Player", "PlayerPunch.gltf");

	player_.reset(AnimationModel::Create(playerModelHandle_));
	
	playerWorldTransform_.Initialize();
	playerWorldTransform_.translate_.x = 2.0f;
	playerWorldTransform_.translate_.y = 0.5f;

	playerAnimationTime_ = 0;

	playerSkeleton.Create(ModelManager::GetInstance()->GetModelData(playerModelHandle_).rootNode);

	playerSkinCluster_.Create(playerSkeleton, ModelManager::GetInstance()->GetModelData(playerModelHandle_));
}

void Player::Update()
{
	AnimationUpdate();

	BehaviorUpdate();
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

}

void Player::BehaviorWalkInitialize()
{

}

void Player::BehaviorWalkUpdate()
{
	AnimationManager::GetInstance()->ApplyAnimation(playerSkeleton, playerAnimationHandle_, playerModelHandle_, playerAnimationTime_);
}

void Player::BehaviorSprintInitialize()
{

}

void Player::BehaviorSprintUpdate()
{

}

void Player::BehaviorGrabInitialize()
{

}

void Player::BehaviorGrabUpdate()
{

}

void Player::BehaviorPunchInitialize()
{

}

void Player::BehaviorPunchUpdate()
{

}

void Player::BehaviorJumpInitialize()
{

}

void Player::BehaviorJumpUpdate()
{

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