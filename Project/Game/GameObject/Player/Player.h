#pragma once

#include "GameManager/GameManager.h"
#include "GameManager/IGameScene.h"

#include "AnimationManager.h"
#include "AnimationModel.h"
#include "Camera.h"
#include "Collision.h"
#include "Input.h"
#include "Model.h"
#include "Particle3D.h"
#include "SkinCluster.h"
#include "Sprite.h"
#include "TextureManager.h"

#include "GameObject/Stage/Stage.h"

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

	// ゲッタ
	WorldTransform GetWorldTransform() { return playerWorldTransform_; }
	OBB GetCollision() { return playerCollision_; }

	// セッタ
	void SetCollision();
	void SetFallSpeed(float fallSpeed) { fallSpeed_ = fallSpeed; }

	Vector3 SetPosition(Vector3 setPosition) { return playerWorldTransform_.translate_ = setPosition; }
	Vector3 SetRotate(Vector3 setRotate) { return playerWorldTransform_.rotate_ = setRotate; }

private: 
	
	// プレイヤーに関する基本
	std::unique_ptr<AnimationModel> player_ = nullptr;
	uint32_t playerModelHandle_;
	WorldTransform playerWorldTransform_ = {};

	uint32_t playerIdleAnimationHandle_;
	uint32_t playerWalkAnimationHandle_;
	uint32_t playerSprintAnimationHandle_;
	uint32_t playerPunchAnimationHandle_;
	uint32_t playerJumpAnimationHandle_;

	uint32_t playerGrabAnimationHandle_;
	uint32_t playerGrabStartAnimationHandle_;
	uint32_t playerGrabStopAnimationHandle_;
	
	Skeleton playerSkeleton = {};
	float playerAnimationTime_;
	SkinCluster playerSkinCluster_ = {};

	OBB playerCollision_;
	float fallSpeed_ = 0.01f;

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

	std::unique_ptr<Sprite> controlSprite_;
	uint32_t controlSpriteHandle_;

	Vector2 controlSpriteTransform_;

	const float kCharacterSpeed = 0.03f;
};