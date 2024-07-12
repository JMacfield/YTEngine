#pragma once

#include "GameManager/GameManager.h"
#include "GameManager/IGameScene.h"

#include "Input.h"
#include "Sprite.h"

#include "TextureManager.h"

#include <memory>

class GameManager;

class TitleScene : public IGameScene
{
public:

	void Initialize() override;

	void Update(GameManager* gameManager) override;
	
	void Draw() override;

private:

	std::unique_ptr<Sprite> titleSprite_;
	uint32_t titleSpriteHandle_;

	Vector2 titleSpriteTransform_;
};