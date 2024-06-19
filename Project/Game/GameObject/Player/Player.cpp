#include "GameObject/Player/Player.h"

void Player::Initialize()
{
	playerModelHandle_ = ModelManager::GetInstance()->LoadModelFile("Resoruces/AssignmentModel/human", "walk.gltf");
	playerAnimationHandle_ = AnimationManager::GetInstance()->LoadFile("Resources/AssignmentModel/human", "walk.gltf");

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
	playerAnimationTime_ += 1.0f / 60.0f;

	XINPUT_STATE joyState;
}

void Player::Draw()
{

}

void Player::BehaviorMoveInitialize()
{

}

void Player::BehaviorMoveUpdate()
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

void Player::BehaviorJumpUpdate()
{

}

void Player::BehaviorJumpUpdate()
{

}