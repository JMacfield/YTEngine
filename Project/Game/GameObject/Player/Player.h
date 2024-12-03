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

constexpr float kDefaultFallSpeed = 0.01f;
constexpr float kDefaultCharacterSpeed = 0.03f;
constexpr uint32_t kInvalidHandle = UINT32_MAX;

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
	uint32_t playerModelHandle_ = kInvalidHandle;
	WorldTransform playerWorldTransform_ = {};

	uint32_t playerIdleAnimationHandle_ = kInvalidHandle;
	uint32_t playerWalkAnimationHandle_ = kInvalidHandle;
	uint32_t playerSprintAnimationHandle_ = kInvalidHandle;
	uint32_t playerPunchAnimationHandle_ = kInvalidHandle;
	uint32_t playerJumpAnimationHandle_ = kInvalidHandle;

	uint32_t playerGrabAnimationHandle_ = kInvalidHandle;
	uint32_t playerGrabStartAnimationHandle_ = kInvalidHandle;
	uint32_t playerGrabStopAnimationHandle_ = kInvalidHandle;
	
	Skeleton playerSkeleton = {};
	float playerAnimationTime_;
	SkinCluster playerSkinCluster_ = {};

	OBB playerCollision_;

	float fallSpeed_ = kDefaultFallSpeed;
	const float kCharacterSpeed = kDefaultCharacterSpeed;

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
};