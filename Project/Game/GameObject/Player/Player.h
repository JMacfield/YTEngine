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
	kMove,
	kGrab,
	kPunch,
	kJump,
};

class Player 
{
public: // 基本関数

	void Initialize();
	void Update();
	void Draw();

private: 
	
	// プレイヤーに関する基本
	std::unique_ptr<AnimationModel> player_ = nullptr;
	uint32_t playerModelHandle_;
	uint32_t playerAnimationHandle_;
	WorldTransform playerWorldTransform_ = {};

	Skeleton playerSkeleton = {};
	float playerAnimationTime_;
	SkinCluster playerSkinCluster_ = {};

private: 

	// プレイヤービヘイビア
	void BehaviorMoveInitialize();
	void BehaviorMoveUpdate();

	void BehaviorGrabInitialize();
	void BehaviorGrabUpdate();

	void BehaviorPunchInitialize();
	void BehaviorPunchUpdate();

	void BehaviorJumpInitialize();
	void BehaviorJumpUpdate();


};