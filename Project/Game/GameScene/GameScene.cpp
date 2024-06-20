#include "GameScene/GameScene.h"
#include <imgui.h>
#include <Input.h>
#include "GlobalVariables.h"

#include "ModelManager.h"
#include "AnimationManager.h"

/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene() {

}

/// <summary>
/// 初期化
/// </summary>
void GameScene::Initialize() {
	
	modelHandle = ModelManager::GetInstance()->LoadModelFile("Resources/AssignmentModel/simpleSkin", "simpleSkin.gltf");
	
	for (int i = 0; i < SIMPLE_SKIN_AMOUNT_; ++i) {
		skeleton_[i].Create(ModelManager::GetInstance()->GetModelData(modelHandle).rootNode);
		skinCluster_[i].Create(skeleton_[i], ModelManager::GetInstance()->GetModelData(modelHandle));
		animationHande_ = AnimationManager::GetInstance()->LoadFile("Resources/AssignmentModel/simpleSkin", "simpleSkin.gltf");

		simpleModel_[i].reset(AnimationModel::Create(modelHandle));
		worldTransform_[i].Initialize();
	}

	worldTransform_[0].translate_.x=0.0f;
	worldTransform_[0].translate_.y = 0.5f;
	worldTransform_[0].translate_.z = 0.0f;
	worldTransform_[1].translate_.y=-1.0f;
	worldTransform_[1].translate_.y = -1.0f;
	worldTransform_[1].translate_.z = -1.0f;

	//sneakWalk
	//Walk
	humanModelHandle = ModelManager::GetInstance()->LoadModelFile("Resources/AssignmentModel/human", "walk.gltf");
	humanAnimationModel_ = AnimationManager::GetInstance()->LoadFile("Resources/AssignmentModel/human", "walk.gltf");

	for (int i = 0; i < WALK_HUMAN_AMOUNT_; ++i) {
		human_[i].reset(AnimationModel::Create(humanModelHandle));
		humanWorldTransform_[i].Initialize();
		humanAnimationTime_[i] = 0;
		humanSkeleton_[i].Create(ModelManager::GetInstance()->GetModelData(humanModelHandle).rootNode);
		humanSkinCluster_[i].Create(humanSkeleton_[i], ModelManager::GetInstance()->GetModelData(humanModelHandle));
		humanWorldTransform_[i].translate_.x = 2.0f;

	}

	humanWorldTransform_[0].translate_.y = 0.5f;
	humanWorldTransform_[1].translate_.y = -2.0f;

	camera_.Initialize();

	for (int i = 0; i < SIMPLE_SKIN_AMOUNT_; ++i) {
		worldTransform_[i].rotate_.y = 3.1415f;
	}

	uint32_t skyBoxTextureHandle = TextureManager::GetInstance()->LoadTexture("Resources/AssignmentTexture/rostock_laage_airport_4k.dds");
	skyBox_ = std::make_unique<SkyBox>();
	skyBox_->Create(skyBoxTextureHandle);
	skyBoxWorldTransform_.Initialize();
	skyBoxWorldTransform_.scale_ = { 20.0f,20.0f,20.0f };
}

/// <summary>
/// 更新
/// </summary>
void GameScene::Update(GameManager* gameManager) {
	gameManager;

	XINPUT_STATE joyState;

	camera_.Update();
	skyBoxWorldTransform_.Update();

	animationTime_[0] += 1.0f / 60.0f;
	animationTime_[1] += 2.0f / 60.0f;
	
	humanAnimationTime_[0] += 1.0f / 60.0f;
	humanAnimationTime_[1] += 3.0f / 60.0f;

	AnimationManager::GetInstance()->ApplyAnimation(humanSkeleton_[0], humanAnimationModel_, humanModelHandle, humanAnimationTime_[0]);
	
	if (!Input::GetInstance()->GetJoystickState(joyState)) {
		return;
	}

	Vector3 move = { (float)joyState.Gamepad.sThumbLX / SHRT_MAX,0.0f,0.0f };
	move.x = move.x * 0.5f;

	humanWorldTransform_->translate_ = Add(humanWorldTransform_[0].translate_, move);

	if (move.x > 0.1f) {
		humanWorldTransform_->rotate_.y = 1.4f;
	}
	else if (move.x < -0.1f) {
		humanWorldTransform_->rotate_.y = -1.4f;
	}

	if (humanWorldTransform_->translate_.x < -3.36f) {
		humanWorldTransform_->translate_.x = -3.3599999f;
	}
	else if (humanWorldTransform_->translate_.x > 3.36f) {
		humanWorldTransform_->translate_.x = 3.3599999f;
	}
	
	for (int i = 0; i < SIMPLE_SKIN_AMOUNT_; ++i) {
		skeleton_[i].Update();
	}
	for (int i = 0; i < WALK_HUMAN_AMOUNT_; ++i) {
		humanSkeleton_[i].Update();
	}
	
	for (int i = 0; i < SIMPLE_SKIN_AMOUNT_; ++i) {
		skinCluster_[i].Update(skeleton_[i]);
	}
	for (int i = 0; i < WALK_HUMAN_AMOUNT_; ++i) {
		humanSkinCluster_[i].Update(humanSkeleton_[i]);
	}

#ifdef _DEBUG
	ImGui::Begin("DebugWindow");
	ImGui::DragFloat3("CameraTranslate", &camera_.translate_.x, 0.1f);
	ImGui::DragFloat3("CameraRotate", &camera_.rotate_.x, 0.1f);
	ImGui::End();
#endif

	for (int i = 0; i < WALK_HUMAN_AMOUNT_; ++i) {
		humanWorldTransform_[i].Update();
	}
}

void GameScene::Draw() {
	human_[0]->Draw(humanWorldTransform_[0], camera_, humanSkinCluster_[0]);

	skyBox_->Draw(skyBoxWorldTransform_, camera_);
}

GameScene::~GameScene() {
	
}