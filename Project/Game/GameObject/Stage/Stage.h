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

	std::unique_ptr<Model> testStage2_;
	uint32_t testStageHandle2_;
	WorldTransform testStageTransform2_;

	std::unique_ptr<Model> testStage3_;
	uint32_t testStageHandle3_;
	WorldTransform testStageTransform3_;

	OBB testStageCollision_;
};