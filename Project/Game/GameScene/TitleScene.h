#pragma once

#include "GameManager/GameManager.h"
#include "GameManager/IGameScene.h"

#include "JsonLoader/JsonLoader.h"

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

	Camera camera_ = {};

	JsonLoader* jsonLoader_ = nullptr;

	std::unique_ptr<Model> testModel_;
	uint32_t testModelHandle_;
	WorldTransform testModelTransform_;
};