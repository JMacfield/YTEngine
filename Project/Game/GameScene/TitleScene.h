/// タイトルシーン

#pragma once

#include "GameManager/GameManager.h"
#include "GameManager/IGameScene.h"

#include "Audio.h"
#include "DeltaTime.h"
#include "Input.h"
#include "Sprite.h"

#include "TextureManager.h"

#include <memory>
#include <math.h>

#include "GameObject/FollowCamera/FollowCamera.h"

class GameManager;

class TitleScene : public IGameScene
{
public:

	virtual ~TitleScene();

	// タイトルベース //
	void Initialize() override;

	void Update(GameManager* gameManager) override;

	void Draw() override;

	// アニメーション //
	void AnimationInitialize();

	void AnimationUpdate();

	void AnimationDraw();

	// グラウンド //
	void SurfaceInitialize();

	void SurfaceUpdate();

	void SurfaceDraw();

	void TestInitialize();
	void TestUpdate();
	void TestDraw();

private:

	// タイトル画像 //
	std::unique_ptr<Sprite> titleSprite_;
	uint32_t titleSpriteHandle_;

	Vector2 titleSpriteTransform_;

	// タイトルプレイヤーキャラクター //
	std::unique_ptr<AnimationModel> player_[4];
	WorldTransform playerTransform_[4];
	uint32_t playerModelHandle_;

	uint32_t playerGrabWalkingAnimation_;

	Skeleton playerSkeleton_[4] = {};
	float playerAnimationTime_[4];
	SkinCluster playerSkinCluster_[4] = {};

	// カメラ //
	Camera camera_ = {};

	// タイトルアニメーション用 //
	int repeatCount_ = 0;
	bool isRepeat_ = true;
	int repeatTimer_ = 0;

	// タイトル サーフェイス //
	std::unique_ptr<Model> surfaceGround_;
	uint32_t surfaceGroundHandle_;
	WorldTransform surfaceGroundTransform_;

	std::unique_ptr<Model> surfaceBack_;
	uint32_t surfaceBackHandle_;
	WorldTransform surfaceBackTransform_;

	Vector2 playerIconTransform_[4];
	std::unique_ptr<Sprite> playerIcon_[4];
	uint32_t playerIconHandle_[4];

	Vector2 titleIconTransform_;
	std::unique_ptr<Sprite> titleIcon_;
	uint32_t titleIconHandle_;

	uint32_t titleBGMHandle_;

	std::unique_ptr<Model> titleSign_;
	uint32_t titleSignHandle_;
	WorldTransform titleSignTransform_;
};