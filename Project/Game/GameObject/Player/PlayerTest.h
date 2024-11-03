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
	Idle,
	Walk,
	Grab,
	Punch,
	Jump,
};

class PlayerTest
{
public: // 基本の関数

	void Initialize();
	void Update();
	void Draw(Camera& camera);

	void AnimationInitialize();
	void AnimationUpdate();

	void Control();
	
	void CollisionUpdate();

public: // ゲッタ　セッタ

	WorldTransform GetWorldTransform() { return transform_; }
	OBB GetCollision() { return collision_; }

	Vector3 SetPosition(Vector3 setPosition) { return transform_.translate_ = setPosition; }
	Vector3 SetRotate(Vector3 setRotate) { return transform_.rotate_ = setRotate; }
	
private: // プレイヤーの基本変数

	std::unique_ptr<AnimationModel> character_ = nullptr;
	uint32_t modelHandle_;
	WorldTransform transform_ = {};

	uint32_t idleAnimationHandle_;
	uint32_t sprintAnimationHandle_;
	uint32_t punchAnimationHandle_;
	uint32_t jumpAnimationHandle_;
	
	uint32_t grabAnimationHandle_;

	Skeleton skeleton_ = {};
	float animationTime_;
	SkinCluster skinCluster = {};

	OBB collision_;
	float fallSpeed_ = 0.01f;

private: // プレイヤーの行動

	void BehaviorIdleInitialize();
	void BehaviorIdleUpdate();

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

private: // プレイヤーの行動

	Behavior behavior_ = Behavior::Idle;
	std::optional<Behavior> behaviorRequest_ = std::nullopt;

	const float kCharacterSpeed = 0.03f;
};