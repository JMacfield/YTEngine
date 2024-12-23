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
#include "GameObject/Stage/Stage.h"

#include <memory>
#include <Particle3D.h>
#include "SkinCluster.h"

#include "Input.h"

#include "JsonLoader.h"

class GameManager;

class GameScene : public IGameScene {
public:

	void Initialize()override;

	void Update(GameManager* gameManager)override;

	void Draw()override;
	
private:
	
	Camera camera_ = {};

	std::unique_ptr<Player> player_;

	std::unique_ptr<Stage> stage_;

	JsonLoader* jsonLoader_ = nullptr;
};