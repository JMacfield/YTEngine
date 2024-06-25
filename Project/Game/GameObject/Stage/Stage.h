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

class Stage
{
public:

	void Initialize();
	void Update();
	void Draw(Camera& camera);

private:

	std::unique_ptr<Model> testStage_;
	uint32_t testStageHandle_;
	WorldTransform testStageTransform_;
};