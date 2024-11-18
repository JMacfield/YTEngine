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

class NewPlayer
{

public:

	// 基本関数
	void Initialize();
	void Update();
	void Draw(Camera& camera);

	void MoveControl();

private:

	// プレイヤー関連
	std::unique_ptr<Model> character_;
	uint32_t characterModelHandle_;
	WorldTransform characterTransform_;

	OBB collision_;

	const float kCharacterSpeed_;
};