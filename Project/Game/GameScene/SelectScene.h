/// セレクトシーン

#pragma once

#include "GameManager/GameManager.h"
#include "GameManager/IGameScene.h"

#include "Input.h"
#include "Sprite.h"

#include "TextureManager.h"

#include <memory>

using namespace YTEngine;

class GameManager;

class SelectScene : public IGameScene
{
public:

	void Initialize() override;

	void Update(GameManager* gameManager) override;

	void Draw() override;

private:

	std::unique_ptr<Sprite> selectSprite_[4];
	uint32_t selectSpriteHandle_[4];

	Vector2 selectSpriteTransform_[4];

	bool isSpriteMovingLeft_;
	bool isSpriteMovingRight_;

	float moveNumLeft_ = 1280.0f;
	float moveNumRight_ = 0.0f;

	bool isCanControl_ = true;
};