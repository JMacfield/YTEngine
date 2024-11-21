#pragma once

#include "Collision.h"

#include "GameManager/IGameScene.h"

#include "Sprite.h"
#include "GameManager/GameManager.h"
#include "Model.h"
#include "AnimationModel.h"
#include "TextureManager.h"
#include "Camera.h"

#include "GameObject/Player/Player.h"
/// テストシーン

#include "GameObject/Stage/Stage.h"

#include <memory>
#include <Particle3D.h>
#include "SkinCluster.h"

#include "Input.h"

using namespace YTEngine;

class GameManager;

class TestScene : public IGameScene {
public:

	void Initialize()override;

	void Update(GameManager* gameManager)override;

	void Draw()override;

private:

	Camera camera_ = {};

	std::unique_ptr<Sprite> white_;
	Vector2 whiteTransform_;
	uint32_t whiteHandle_;
};