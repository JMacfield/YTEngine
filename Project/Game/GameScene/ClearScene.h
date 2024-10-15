/// クリアシーン

#pragma once

#include "GameManager/GameManager.h"
#include "GameManager/IGameScene.h"

#include "Input.h"
#include "Sprite.h"

#include "TextureManager.h"

#include <memory>

class GameManager;

class ClearScene : public IGameScene
{
public:

	void Initialize() override;

	void Update(GameManager* gameManager) override;

	void Draw() override;

private:


};