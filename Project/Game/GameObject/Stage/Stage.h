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

#include "Collision.h"

#include <memory>

class Stage
{
public:

	static Stage* GetInstance();

	void Initialize();
	void Update();
	void Draw(Camera& camera);

	void SetCollision();
	void SetParent(const WorldTransform* parent) { grabObjectTransform_.parent_ = parent; }

	void SetMoveWallFlag(bool isFlag) { isMoveWall_ = isFlag; }

	OBB GetCollision() { return testStageCollision_; }
	
private:

	std::unique_ptr<Model> testStage_;
	uint32_t testStageHandle_;
	WorldTransform testStageTransform_;

	std::unique_ptr<Model> goalObject_;
	uint32_t goalObjectHandle_;
	WorldTransform goalObjectTransform_;

	std::unique_ptr<Model> grabObejct_;
	uint32_t grabObjectHandle_;
	WorldTransform grabObjectTransform_;

	OBB testStageCollision_;

	std::unique_ptr<Model> backObject_;
	uint32_t backObjectHandle_;
	WorldTransform backObjectTransform_;

	std::unique_ptr<Sprite> object1_;
	uint32_t object1Handle_;
	Vector2 object1Transform_;

	std::unique_ptr<Model> surfaceBack_;
	uint32_t surfaceBackHandle_;
	WorldTransform surfaceBackTransform_;

	std::unique_ptr<Model> moveWall_;
	uint32_t moveWallHandle_;
	WorldTransform moveWallTransform_;

	std::unique_ptr<Model> pushBackWall_;
	uint32_t pushBackWallHandle_;
	WorldTransform pushBackWallTransform_;

	std::unique_ptr<Model> pushBackWall2_;
	uint32_t pushBackWallHandle2_;
	WorldTransform pushBackWallTransform2_;

	std::unique_ptr<Model> bottonBottom_;
	uint32_t bottonBottomHandle_;
	WorldTransform bottonBottomTransform_;

	std::unique_ptr<Model> bottonTop_;
	uint32_t bottonTopHandle_;
	WorldTransform bottonTopTransform_;

	bool isMoveWall_ = false;
};