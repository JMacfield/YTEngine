#include "Stage.h"

void Stage::Initialize() 
{
	testStageHandle_ = ModelManager::LoadModelFile("Resources/StageObject", "TestObject.obj");

	testStage_.reset(Model::Create(testStageHandle_));

	testStageTransform_.Initialize();
	testStageTransform_.translate_ = { 0.0f,-2.7f,0.0f };
	testStageTransform_.scale_ = { 8.0f,3.0f,3.0f };
}

void Stage::Update()
{
	ImGui::Begin("Stage");
	ImGui::DragFloat3("Rotate", &testStageTransform_.translate_.x, 0.01f);
	ImGui::End();

	testStageTransform_.Update();
}

void Stage::Draw(Camera& camera)
{
	testStage_->Draw(testStageTransform_, camera);
}