#pragma once

#include "GameManager/GameManager.h"
#include "GameManager/IGameScene.h"

#include "AnimationManager.h"
#include "AnimationModel.h"
#include "Camera.h"
#include "Input.h"
#include "Model.h"
#include "Particle3D.h"
#include "SkinCluster.h"
#include "Sprite.h"
#include "TextureManager.h"

#include <memory>

enum class Behavior
{
	kIdle,
	kWalk,
	kSprint,
	kGrab,
	kPunch,
	kJump,
};

class Player 
{
public: 
	
	// 基本関数
	void Initialize();
	void Update();
	void Draw(Camera& camera);

	void Control();
	void AnimationUpdate();

	// ゲッター
	WorldTransform GetWorldTransform() { return playerWorldTransform_; }

private: 
	
	// プレイヤーに関する基本
	std::unique_ptr<AnimationModel> player_ = nullptr;
	uint32_t playerModelHandle_;
	WorldTransform playerWorldTransform_ = {};

	uint32_t playerIdleAnimationHandle_;
	uint32_t playerWalkAnimationHandle_;
	uint32_t playerSprintAnimationHandle_;
	uint32_t playerGrabAnimationHandle_;
	uint32_t playerPunchAnimationHandle_;
	uint32_t playerJumpAnimationHandle_;
	
	Skeleton playerSkeleton = {};
	float playerAnimationTime_;
	SkinCluster playerSkinCluster_ = {};

private: 

	// プレイヤービヘイビア
	void BehaviorIdleInitialize();
	void BehaviorIdleUpdate();

	void BehaviorWalkInitialize();
	void BehaviorWalkUpdate();

	void BehaviorSprintInitialize();
	void BehaviorSprintUpdate();

	void BehaviorGrabInitialize();
	void BehaviorGrabUpdate();

	void BehaviorPunchInitialize();
	void BehaviorPunchUpdate();

	void BehaviorJumpInitialize();
	void BehaviorJumpUpdate();

	void BehaviorUpdate();

	Behavior GetBehavior() { return behavior_; }

private:

	// ビヘイビア
	Behavior behavior_ = Behavior::kIdle;
	std::optional<Behavior> behaviorRequest_ = std::nullopt;
};